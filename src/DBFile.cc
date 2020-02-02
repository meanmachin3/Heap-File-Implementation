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

DBFile::DBFile() {
    // Added to stop the program execution, so that we can debug using CLion's attach to process option.
    std::getchar();

    this->file = new File();
    this->page = new Page();
    this->current_page = 0;
    this->head = NULL;
}

DBFile::~DBFile() {
    delete(this->page);
    delete(this->file);
}

int DBFile::Create(const char *f_path, fType f_type, void *startup) {
    if (f_path == NULL || f_path[0] == '\0' || f_type < heap || f_type > tree) {
        return 0;
    }

    this->file->Open(0, f_path);
    return 1;
}

int DBFile::Open(const char *f_path) {
    if (f_path == NULL || f_path[0] == '\0') return 0;
    this->file->Open(1, f_path);
    return 1;
}

int DBFile::Close() {
    this->WriteToFile();
    this->file->Close();
    return 1;
}

void DBFile::Load(Schema &schema, const char *tbl_file_path) {
    FILE *f = NULL;
    f = fopen(tbl_file_path, "r");
    if(f != NULL) {
        Record *temp_rec = new Record();
        while(temp_rec->SuckNextRecord(&schema, f)) {
            this->head = temp_rec;
            this->Add(*(temp_rec));
        }

        fclose(f);
    } else {
        cerr << "DBFile::Load - Unable to open the file: " << tbl_file_path << endl;
    }
}

void DBFile::Add(Record &record_to_add) {
    if(this->page->GetCurrentSize() + record_to_add.GetSize() > PAGE_SIZE) {
        this->WriteToFile();
    }

    if(!this->page->Append(&record_to_add)) {
        cerr << "DBFile::AppendToPage - Error appending new record to the page." << endl;
    }
}

void DBFile::WriteToFile() {
    this->file->AddPage(this->page, current_page++);
    this->page->EmptyItOut();
}

void DBFile::MoveFirst() {
}

int DBFile::GetNext(Record &record_to_fetch) {
}

int DBFile::GetNext(Record &record_to_fetch, CNF &cnf, Record &literal) {
}
