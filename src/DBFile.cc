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
    this->read_page = new Page();
    this->write_page = new Page();
    this->head = new Record();
    this->comparisonEngine = new ComparisonEngine();
}

DBFile::~DBFile() {
    delete(this->file);
    delete(this->read_page);
    delete(this->write_page);
    delete(this->head);
    delete(this->comparisonEngine);
}

int DBFile::Create(const char *f_path, fType f_type, void *startup) {
    if (f_path == NULL || f_path[0] == '\0' || f_type < heap || f_type > tree) {
        return 0;
    }

    this->file->Open(0, f_path);

    current_page_index = 1;
    write_index = 1;
    is_dirty_write = 0;
    is_end_of_file = 1;

    return 1;
}

int DBFile::Open(const char *f_path) {
    if (f_path == NULL || f_path[0] == '\0') {
        std::cerr << "DBFile::Open - Invalid file path: " << f_path << std::endl;
        return 0;
    }
    this->file->Open(1, f_path);

    current_page_index = 1;
    is_end_of_file = 0;

    return 1;
}

int DBFile::Close() {
    if(this->is_dirty_write) {
        this->WriteToFile();
    }

    is_end_of_file = 1;
    return this->file->Close();
}

void DBFile::Load(Schema &schema, const char *tbl_file_path) {
    FILE *f = NULL;
    f = fopen(tbl_file_path, "r");
    if(f != NULL) {
        Record *temp_rec = new Record();
        while(temp_rec->SuckNextRecord(&schema, f)) {
            this->Add(*(temp_rec));
        }
        delete temp_rec;
        fclose(f);
    } else {
        std::cerr << "DBFile::Load - Unable to open the file: " << tbl_file_path << std::endl;
    }
}

void DBFile::Add(Record &record_to_add) {
    this->is_dirty_write = 1;

    if(this->write_page->GetCurrentSize() + record_to_add.GetSize() > PAGE_SIZE) {
        this->WriteToFile();
    }

    if(!this->write_page->Append(&record_to_add)) {
        std::cerr << "DBFile::AppendToPage - Error appending new record to the page." << std::endl;
    }
}

void DBFile::WriteToFile() {
    this->file->AddPage(this->write_page, write_index++);
    this->write_page->EmptyItOut();
}

void DBFile::MoveFirst() {
    this->file->GetPage(this->read_page, 1);
    this->read_page->GetFirst(this->head);
}

int DBFile::GetNext(Record &record_to_fetch) {
    if(!is_end_of_file) {
        record_to_fetch.Copy(this->head);
        if (this->read_page->GetFirst(&record_to_fetch)){
            return 1;
        }

        if (++current_page_index < this->file->GetLength () - 1) {
            this->file->GetPage(this->read_page, current_page_index);
            this->read_page->GetFirst(this->head);
            return 1;
        } else {
            is_end_of_file = 1;
        }
    }
    return 0; // Couldn't find record and has reached EOF
}

int DBFile::GetNext(Record &record_to_fetch, CNF &cnf, Record &literal) {
    while (true) {
        int res = this->GetNext(record_to_fetch);
        if(!res) return 0;

        // Returns 0 when all records matching CNF has been found.
        res = this->comparisonEngine->Compare(&record_to_fetch, &literal, &cnf);
        if(res) break;
    }
    return 1;
}
