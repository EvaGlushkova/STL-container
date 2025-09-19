#include <gtest/gtest.h>

TEST(Test, Multi) {
    EXPECT_EQ(5 * 2, 10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}