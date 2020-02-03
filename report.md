<h1 align="center"> Project Report </h1> <br>


## Table of Contents

- [Table of Contents](#table-of-contents)
- [Build Process](#build-process)
- [DBFile.cc](#dbfilecc)
  - [DBFile::Create](#dbfilecreate)
  - [DBFile::Open](#dbfileopen)
  - [DBFile::Close](#dbfileclose)
  - [DBFile::Load](#dbfileload)
  - [DBFile::Add](#dbfileadd)
  - [DBFile::WriteToFile](#dbfilewritetofile)
  - [DBFile::MoveFirst](#dbfilemovefirst)
  - [DBFile::GetNext(Record)](#dbfilegetnextrecord)
  - [DBFile::GetNext(Record, CNF, Record)](#dbfilegetnextrecord-cnf-record)
- [Test Results](#test-results)

## Build Process

- unzip the compressed file using `unzip filename.zip`
- `cd src` to change to source directory
- `make test.out` to compile test.out
- `./test.out` to run the compiled binary
- `make gtest` to compile google test cases
- `./gtest` to run test cases
- `make clean` to clean the compiled binaries

## DBFile.cc

### DBFile::Create

In order to create a file, we make use of exiting `File::Open()` method to create file. Once a file is created we initialize other parameters such as `read_index` & `write_index` that points to the number of records it has read or writen respectively. Apart from this we have boolean `has_record_to_write` & `is_end_of_file`. `has_record_to_write` would be set to true if there's any write done. `is_end_of_file` denotes we have reached at the end of a file.

### DBFile::Open

To open a file, `File::Open()` is used with argument `1`(Since we want to open a file) & f_path.

### DBFile::Close

Before closing a file, we check if there's any record left to be written. If there is we write it out to file before closing it

### DBFile::Load

In order to load, all the records from schema, we've used `SuckNextRecord` method that reads the next record from a pointer to a text file and then add it to page buffer.

### DBFile::Add

Check if the size doesn't exceed the current page size. If it exceeds then write it to file before and then add record. Else add the record to the page buffer.

### DBFile::WriteToFile

Write the current page records to file and empties the page buffer.

### DBFile::MoveFirst

Get the first page and move to the first record of that page.

### DBFile::GetNext(Record)

### DBFile::GetNext(Record, CNF, Record)

## Test Results