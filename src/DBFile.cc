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
    // std::getchar();

    file = new File();
    read_page = new Page();
    write_page = new Page();
    head = new Record();
    comparisonEngine = new ComparisonEngine();
}

DBFile::~DBFile() {
    delete(file);
    delete(read_page);
    delete(write_page);
    delete(head);
    delete(comparisonEngine);
}

int DBFile::Create(const char *f_path, fType f_type, void *startup) {
    if (f_path == NULL || f_path[0] == '\0' || f_type < heap || f_type > tree) {
        return 0;
    }

    file->Open(0, f_path);

    read_index = 1;
    write_index = 1;
    has_record_to_write = false;
    is_end_of_file = true;

    return 1;
}

int DBFile::Open(const char *f_path) {
    if (f_path == NULL || f_path[0] == '\0') {
        // std::cerr << "DBFile::Open - Invalid file path: " << f_path << std::endl;
        return 0;
    }
    file->Open(1, f_path);

    read_index = 1;
    is_end_of_file = false;

    return 1;
}

int DBFile::Close() {
    if(has_record_to_write) {
        WriteToFile();
    }

    is_end_of_file = true;
    return file->Close();
}

void DBFile::Load(Schema &schema, const char *tbl_file_path) {
    FILE *f = NULL;
    f = fopen(tbl_file_path, "r");
    if(f != NULL) {
        Record *temp_rec = new Record();
        while(temp_rec->SuckNextRecord(&schema, f)) {
            Add(*(temp_rec));
        }
        delete temp_rec;
        fclose(f);
    } else {
        std::cerr << "DBFile::Load - Unable to open the file: " << tbl_file_path << std::endl;
    }
}

void DBFile::Add(Record &record_to_add) {
    has_record_to_write = true;

    if(write_page->GetCurrentSize() + record_to_add.GetSize() > PAGE_SIZE) {
        WriteToFile();
    }

    if(!write_page->Append(&record_to_add)) {
        std::cerr << "DBFile::AppendToPage - Error appending new record to the page." << std::endl;
    }
}

void DBFile::WriteToFile() {
    file->AddPage(write_page, write_index++);
    write_page->EmptyItOut();
}

void DBFile::MoveFirst() {
    file->GetPage(read_page, 1);
    read_page->GetFirst(head);
}

int DBFile::GetNext(Record &record_to_fetch) {
    if(!is_end_of_file) {
        record_to_fetch.Copy(head);
        if (!read_page->GetFirst(head)) {
            if (++read_index < file->GetLength () - 1) {
                file->GetPage(read_page, read_index);
                read_page->GetFirst(head);
            } else {
                is_end_of_file = true;
            }
        }
        return 1;
    }
    return 0;
}

int DBFile::GetNext(Record &record_to_fetch, CNF &cnf, Record &literal) {
    while (true) {
        int res = GetNext(record_to_fetch);
        if(!res) return 0;

        res = comparisonEngine->Compare(&record_to_fetch, &literal, &cnf);
        if(res) break;
    }
    return 1;
}
