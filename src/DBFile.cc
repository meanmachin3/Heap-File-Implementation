#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "DBFile.h"
#include "Defs.h"
#include <string.h>


// stub file .. replace it with your own DBFile.cc

DBFile::DBFile () {
    this->file = new File();
}

DBFile::~DBFile () {
    delete(this->file);
}

int DBFile::Create (const char *f_path, fType f_type, void *startup) {

    // Check for invalid arguments
    // https://wiki.sei.cmu.edu/confluence/display/cplusplus/INT50-CPP.+Do+not+cast+to+an+out-of-range+enumeration+value
    if (f_path == NULL || f_type < heap || f_type > tree) {
        return 0;
    }
    // https://stackoverflow.com/questions/25549562/how-to-convert-const-char-to-char-in-c
    char *file_path = strdup(f_path);
    this->file->Open(0, file_path);
    return 1;
}

void DBFile::Load (Schema &f_schema, const char *loadpath) {
}

int DBFile::Open (const char *f_path) {
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
