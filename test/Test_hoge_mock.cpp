#include "gtest/gtest.h"
#include "gmock/gmock.h"

// include the api headers for "hoge"
#include "hoge.h"

// include mock headers for "hoge"
#include "mock_osal.hpp"

// Test Class

class Test_hoge_mock: public ::testing::Test {
protected:
    virtual void SetUp() {
        mock_osal = new MockOsal();
        MockOsal_set(mock_osal);
    }
    virtual void TearDown() {
        if (mock_osal) {
            delete mock_osal;
            mock_osal = nullptr;
        }
    }

    MockOsal *mock_osal;
};

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;

TEST_F(Test_hoge_mock, new_error)
{
    EXPECT_CALL(*mock_osal, osal_calloc(_, _))
        .Times(1)
        .WillOnce(Return(nullptr))
        .RetiresOnSaturation();

    void *hoge = hoge_new();
    ASSERT_FALSE(hoge);
}

TEST_F(Test_hoge_mock, new_success)
{
    EXPECT_CALL(*mock_osal, osal_calloc(_, _))
        .Times(1)
        .WillOnce(Invoke(calloc))
        .RetiresOnSaturation();
    EXPECT_CALL(*mock_osal, osal_free(_))
        .Times(1)
        .RetiresOnSaturation();

    void *hoge = hoge_new();
    ASSERT_TRUE(hoge);

    hoge_destroy(hoge);
}
