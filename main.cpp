// main.cpp
// Created by Yana Utochkina

//#define GENERATE_FILE;

#ifdef GENERATE_FILE
#include "file_generator/generate_file.h"
#endif

#ifndef GENERATE_FILE
#include "ConcurrentDS.h"
#include <functional>
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

/*void& read_file(std::ifstream& ifile) {
    std::string line;
    while (!ifile.eof()) {
        line = ifile.getline(line);
    }
}*/