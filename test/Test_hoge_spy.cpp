#include "gtest/gtest.h"

// include the api headers for "hoge"
#include "hoge.h"

// include spy headers for "hoge"
#include "spy_hoge.h"

// Test Class

class Test_hoge_spy: public ::testing::Test {
protected:
    virtual void SetUp() {
        hoge = spy_hoge_new();
    }
    virtual void TearDown() {
        hoge_destroy(hoge);
    }

    void *hoge;
};

TEST_F(Test_hoge_spy, inc_x)
{
    for (int i = 0; i < 10; i++) {
        hoge_inc(hoge, 1);
    }
    ASSERT_TRUE(hoge_ge(hoge, 10));
    ASSERT_FALSE(hoge_ge(hoge, 11));

    ASSERT_EQ(10, spy_hoge_count_inc_x(hoge));
    ASSERT_EQ(0, spy_hoge_count_inc_10(hoge));
    ASSERT_EQ(2, spy_hoge_count_ge(hoge));
}

TEST_F(Test_hoge_spy, inc_10)
{
    hoge_inc10(hoge);
    ASSERT_TRUE(hoge_ge(hoge, 10));
    ASSERT_FALSE(hoge_ge(hoge, 11));

    ASSERT_EQ(0, spy_hoge_count_inc_x(hoge));
    ASSERT_EQ(1, spy_hoge_count_inc_10(hoge));
    ASSERT_EQ(2, spy_hoge_count_ge(hoge));
}
