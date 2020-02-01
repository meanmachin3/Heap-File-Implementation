#include "../src/DBFile.h"
#include "../src/test.h"
#include <gtest/gtest.h>


TEST(DBFile, Create) { 
    DBFile dbfile;
    relation *rel;
    ASSERT_EQ(dbfile.Create(NULL, heap, NULL), 0);
    ASSERT_EQ(dbfile.Create(rel->path(), heap, NULL), 1);   
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}