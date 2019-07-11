#include <stdlib.h>

void
osal_free(void *ptr)
{
    free(ptr);
}

void *
osal_calloc(size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

