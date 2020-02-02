#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "DBFile.h"
#include "Defs.h"
#include <string.h>
#include <iostream>

DBFile::DBFile () {
    // Added to stop the program execution, so that we can debug using CLion's attach to process option.
    std::getchar();

    this->file = new File();
    this->page = new Page();
    this->current_page = 0;
    this->head = NULL;
}

DBFile::~DBFile () {
    delete(this->file);
}

int DBFile::Create (const char *f_path, fType f_type, void *startup) {
    if (f_path == NULL || f_path[0] == '\0' || f_type < heap || f_type > tree) {
        return 0;
    }

    this->file->Open(0, f_path);
    return 1;
}

void DBFile::Load (Schema &f_schema, const char *load_path) {
}

int DBFile::Open (const char *f_path) {
    if (f_path == NULL || f_path[0] == '\0') return 0;
    this->file->Open(1, f_path);
    return 1;
}

void DBFile::MoveFirst () {
}

int DBFile::Close () {
}

void DBFile::Add (Record &rec) {
}

int DBFile::GetNext (Record &fetchme) {
}

int DBFile::GetNext (Record &fetchme, CNF &cnf, Record &literal) {
}
