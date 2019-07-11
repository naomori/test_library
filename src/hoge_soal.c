#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>

// prototypes of private functions
static uint16_t checksum(uint16_t *buf, size_t len);
static struct sockaddr *str2sa(const char *ipaddr, const char *port,
                               struct sockaddr *sa);

// public functions
int
soal_open_icmp(void)
{
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
        fprintf(stderr, "failed to socket:%m\n");
        return -1;
    }
    return sock;
}

void
soal_close_icmp(int sock)
{
    if (sock < 0) {
        return;
    }
    close(sock);
}

ssize_t
soal_send_echo_request(int sock, const char *dst_addr)
{
    struct icmphdr hdr;
    memset(&hdr, 0, sizeof(hdr));
    hdr.type = ICMP_ECHO;
    hdr.code = 0;
    hdr.checksum = 0;
    hdr.un.echo.id = 0;
    hdr.un.echo.sequence = 0;
    hdr.checksum = checksum((uint16_t *)&hdr, sizeof(hdr));
    struct sockaddr_in sin;

    ssize_t sent_size;
    sent_size = sendto(sock, &hdr, sizeof(hdr), 0/*flags*/,
                       str2sa(dst_addr, NULL, (struct sockaddr *)&sin),
                       sizeof(sin));
    if (sent_size <= 0) {
        fprintf(stderr, "failed to sento(): %m");
    }
    return sent_size;
}

ssize_t
soal_recv(int sockfd, void *buf, size_t len, int flags)
{
    return recv(sockfd, buf, len, flags);
}

uint8_t
soal_recv_echo(int sock)
{
    char buf[1500];

    ssize_t recv_size;
    recv_size = soal_recv(sock, buf, sizeof(buf), 0/*flags*/);
    if (recv_size <= 0) {
        fprintf(stderr, "failed to recv(): %m");
        return 0xff;
    }

    struct iphdr *iphdr_ptr;
    struct icmphdr *icmphdr_ptr;

    iphdr_ptr = (struct iphdr *)buf;
    icmphdr_ptr = (struct icmphdr *)(buf + (iphdr_ptr->ihl * 4));

    return icmphdr_ptr->type;
}

// private functions

static uint16_t
checksum(uint16_t *buf, size_t len)
{
    uint32_t sum = 0;

    while (len > 1) {
        sum += *buf;
        buf++;
        len -= sizeof(*buf);
    }
    if (len == 1) {
        sum += *(uint8_t *)buf;
    }
    sum = (sum & 0xffff) + (sum >> 16);
    sum += (sum >> 16);
    return (uint16_t)(~sum & 0xffff);
}

static struct sockaddr *
str2sa(const char *ipaddr, const char *port, struct sockaddr *sa)
{
	if (!ipaddr || !sa) {
		return NULL;
	}

	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof(hints));
    hints.ai_flags  = AI_NUMERICHOST;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

	int err = getaddrinfo(ipaddr, port, &hints, &res);
	if (err) {
        fprintf(stderr, "failed to getaddrinfo(%s, %s): %s\n",
                ipaddr, port, gai_strerror(err));
        if (err == EAI_SYSTEM) {
            fprintf(stderr, "system error: %m");
        }
		return NULL;
	}
	if (res->ai_next) {
		fprintf(stderr,
		        "getaddrinfo(%s,%s) resolved to multiple address, "
			    "taking the first one", ipaddr, port);
	}

	memcpy(sa, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);

	return sa;
}
