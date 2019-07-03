//
// Created by nmorita on 2019/07/02.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// include the api headers for "hoge"
#include "hoge.h"

// Test Class
class Test_hoge: public ::testing::Test {
protected:
    virtual void SetUp() {
        // nothing
    }
    virtual void TearDown() {
        // nothing
    }

};

using ::testing::Eq;

TEST_F(Test_hoge, new_destroy)
{
    void *hoge = hoge_new();
    ASSERT_TRUE(hoge);

    hoge_destroy(hoge);
}
