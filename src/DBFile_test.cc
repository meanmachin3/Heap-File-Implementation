#include "../src/DBFile.h"
#include "../src/test.h"
#include <gtest/gtest.h>

TEST(DBFile, Create) { 
    DBFile dbFile;

    ASSERT_EQ(dbFile.Create(NULL, heap, NULL), 0);

    dbFile.Create("test.bin", heap, NULL);
    FILE* f = fopen("test.bin", "r");

    ASSERT_TRUE(f != NULL);
}

TEST(DBFile, Open) {
    DBFile dbFile;

    ASSERT_EQ(dbFile.Open(NULL), 0);
    dbFile.Create("test.bin", heap, NULL);
    ASSERT_EQ(dbFile.Open("test.bin"), 1);
    FILE* f = fopen("test.bin", "r");

    ASSERT_TRUE(f != NULL);
}

TEST(DBFile, Close) {
    DBFile dbFile;
    dbFile.Create("test.bin", heap, NULL);
    dbFile.Open("test.bin");
    ASSERT_EQ(dbFile.Close(), 0);
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}