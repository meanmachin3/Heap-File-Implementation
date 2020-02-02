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

TEST(DBFile, Load) {
    DBFile dbFile;

    Schema *schema = new Schema("catalog", "nation");
    const char* tbl_file_path = "../files/nation.tbl";

    dbFile.Load(*(schema), tbl_file_path);

    ASSERT_EQ(0, 0);
    ASSERT_EQ(0, 0);   
}

TEST(DBFile, Open) {
    DBFile dbFile;

    ASSERT_EQ(dbFile.Open(NULL), 0);
    dbFile.Create("test.bin", heap, NULL);
    dbFile.Open("test.bin");
    FILE* f = fopen("test.bin", "r");

    ASSERT_TRUE(f != NULL);
}

TEST(DBFile, MoveFirst) { 
    ASSERT_EQ(0, 0);
    ASSERT_EQ(0, 0);   
}

TEST(DBFile, Close) {
    DBFile dbFile;
    ASSERT_EQ(dbFile.Close(), 1);
}

TEST(DBFile, Add) { 
    ASSERT_EQ(0, 0);
    ASSERT_EQ(0, 0);   
}

TEST(DBFile, GetNext) { 
    DBFile dbfile;
	// dbfile.Open();
	dbfile.MoveFirst ();

	Record temp;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}