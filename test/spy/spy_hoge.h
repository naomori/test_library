#ifndef HOGELIB_SPY_HOGE_H
#define HOGELIB_SPY_HOGE_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void *spy_hoge_new(void);
int spy_hoge_count_inc_x(void *spy);
int spy_hoge_count_inc_10(void *spy);
int spy_hoge_count_ge(void *spy);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif //HOGELIB_SPY_HOGE_H
