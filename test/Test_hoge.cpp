#include "gtest/gtest.h"

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

class Test_hoge_inc: public ::testing::Test {
protected:
    virtual void SetUp() {
        hoge = hoge_new();
    }
    virtual void TearDown() {
        hoge_destroy(hoge);
    }

    void *hoge;
};

TEST_F(Test_hoge, new_destroy)
{
    void *hoge = hoge_new();
    ASSERT_TRUE(hoge);

    hoge_destroy(hoge);
}

TEST_F(Test_hoge_inc, inc_x)
{
    for (int i = 0; i < 10; i++) {
        hoge_inc(hoge, 1);
    }
    ASSERT_TRUE(hoge_ge(hoge, 10));
    ASSERT_FALSE(hoge_ge(hoge, 11));
}

TEST_F(Test_hoge_inc, inc_10)
{
    hoge_inc10(hoge);
    ASSERT_TRUE(hoge_ge(hoge, 10));
    ASSERT_FALSE(hoge_ge(hoge, 11));
}
