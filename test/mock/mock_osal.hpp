#ifndef HOGELIB_MOCK_OSAL_HPP
#define HOGELIB_MOCK_OSAL_HPP
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "hoge_osal.h"

class MockOsal {
public:
    MOCK_METHOD1(osal_free, void(void *ptr));
    MOCK_METHOD2(osal_calloc, void *(size_t nmemb, size_t size));
};

void MockOsal_set(MockOsal *obj);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif //HOGELIB_MOCK_OSAL_HPP
