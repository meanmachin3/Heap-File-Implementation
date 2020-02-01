#include "../src/DBFile.h"
#include "../src/test.h"
#include <gtest/gtest.h>


TEST(DBFile, Create) { 
    DBFile dbfile;
    ASSERT_EQ(dbfile.Create(NULL, heap, NULL), 0);
    dbfile.Create("test.bin", heap, NULL);
    FILE* f = fopen("test.bin", "r");
    ASSERT_TRUE(f != NULL);
}

TEST(DBFile, Load) { 
    ASSERT_EQ(0, 0);
    ASSERT_EQ(0, 0);   
}

TEST(DBFile, Open) { 
    ASSERT_EQ(0, 0);
    ASSERT_EQ(0, 0);   
}

TEST(DBFile, MoveFirst) { 
    ASSERT_EQ(0, 0);
    ASSERT_EQ(0, 0);   
}

TEST(DBFile, Close) { 
    ASSERT_EQ(0, 0);
    ASSERT_EQ(0, 0);   
}


TEST(DBFile, Add) { 
    ASSERT_EQ(0, 0);
    ASSERT_EQ(0, 0);   
}


TEST(DBFile, GetNext) { 
    ASSERT_EQ(0, 0);
    ASSERT_EQ(0, 0);   
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}