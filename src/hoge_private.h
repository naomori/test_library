#ifndef HOGELIB_HOGE_PRIVATE_H
#define HOGELIB_HOGE_PRIVATE_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdbool.h>

typedef struct hoge_struct {
    void (*self_destroy)(struct hoge_struct *self);

    void (*inc_x)(struct hoge_struct *self, int x);
    void (*inc_10)(struct hoge_struct *self);
    bool (*ge_x)(struct hoge_struct *self, int x);

    int total;
} *hoge_ptr;

#ifdef __cplusplus
}
#endif // __cplusplus
#endif //HOGELIB_HOGE_PRIVATE_H
