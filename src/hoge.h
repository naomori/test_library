#ifndef HOGELIB_HOGE_H
#define HOGELIB_HOGE_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdbool.h>

// public functions
void *hoge_new(void);
void hoge_destroy(void *h);

void hoge_inc(void *self, int x);
void hoge_inc10(void *self);
bool hoge_ge(void *self, int x);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif //HOGELIB_HOGE_H
