//
// Created by nmorita on 2019/07/02.
//

#ifndef TEST_LIBRARY_HOGE_PRIVATE_H
#define TEST_LIBRARY_HOGE_PRIVATE_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdbool.h>

typedef struct hoge_struct {
    void (*inc_x)(struct hoge_struct *self, int x);
    void (*inc_10)(struct hoge_struct *self);
    bool (*ge_x)(struct hoge_struct *self, int x);

    int total;
} *hoge_ptr;

#ifdef __cplusplus
}
#endif // __cplusplus
#endif //TEST_LIBRARY_HOGE_PRIVATE_H
