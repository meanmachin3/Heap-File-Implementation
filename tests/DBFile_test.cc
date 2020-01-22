#include "../src/DBFile.h"
#include <gtest/gtest.h>


TEST(DBFile, Create) { 
ASSERT_EQ(6, 6);
ASSERT_EQ(18.0, 18.0);
ASSERT_EQ(25.4, 25.4);
ASSERT_EQ(0, 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}