#ifndef HOGELIB_HOGE_OSAL_H
#define HOGELIB_HOGE_OSAL_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void osal_free(void *ptr);
void *osal_calloc(size_t nmemb, size_t size);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif //HOGELIB_HOGE_OSAL_H
