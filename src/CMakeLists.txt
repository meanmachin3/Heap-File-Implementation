cmake_minimum_required(VERSION 3.15)
project(src)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(src
    Comparison.cc
    Comparison.h
    ComparisonEngine.cc
    ComparisonEngine.h
    DBFile.cc
    DBFile.h
    Defs.h
    File.cc
    File.h
    lex.yy.c
    main.cc
    ParseTree.h
    Record.cc
    Record.h
    Schema.cc
    Schema.h
    test.cc
    test.h
    TwoWayList.cc
    TwoWayList.h
    y.tab.c
    y.tab.h)
