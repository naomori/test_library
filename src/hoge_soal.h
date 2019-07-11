#ifndef HOGELIB_HOGE_SOAL_H
#define HOGELIB_HOGE_SOAL_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdio.h>
#include <stdint.h>

int soal_open_icmp(void);
void soal_close_icmp(int sock);
ssize_t soal_send_echo_request(int sock, const char *dst_addr);
ssize_t soal_recv(int sockfd, void *buf, size_t len, int flags);
uint8_t soal_recv_echo(int sock);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif //HOGELIB_HOGE_SOAL_H
