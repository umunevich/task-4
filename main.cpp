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
    prepare_input_files();
#endif

#ifndef GENERATE_FILE
    auto* concurrent_ds = new ConcurrentDS();


    {
        std::jthread t1([&concurrent_ds](){concurrent_ds->read1();});
        std::jthread t2([&concurrent_ds](){concurrent_ds->read1();});
    }
#endif
}

void read_files(const int& num_files, std::ifstream& input_file...) {
    
}