// main.cpp
// Created by Yana Utochkina

#define GENERATE_FILE;

#ifdef GENERATE_FILE
#include "file_generator/generate_file.h"
#endif

#ifndef GENERATE_FILE
#include "ConcurrentDS.h"
#endif

#include <fstream>
#include <thread>

int main() {

#ifdef GENERATE_FILE
    {
        std::jthread t1([](){generate_file("../test_files/test1", 30'000, REQUIREMENT);});
        std::jthread t2([](){generate_file("../test_files/test2", 30'000, EQUAL);});
        std::jthread t3([](){generate_file("../test_files/test3", 30'000, OPPOSITE_REQUIREMENT);});
    }

#endif

}