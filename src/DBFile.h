#ifndef DBFILE_H
#define DBFILE_H

#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"

typedef enum {heap, sorted, tree} fType;

class DBFile {
	File* file;
    Page* page;
    off_t current_page;
    Record* head;

private:
    void WriteToFile();

public:
	DBFile();
	~DBFile();

	int Create(const char *f_path, fType file_type, void *startup);

	int Open(const char *f_path);

	int Close();

	void Load(Schema &schema, const char *tbl_file_path);

    void Add(Record &record_to_add);

	void MoveFirst();

	int GetNext(Record &record_to_fetch);

	int GetNext(Record &record_to_fetch, CNF &cnf, Record &literal);
};
#endif
