// main.cpp
// Created by Yana Utochkina

//#define GENERATE_FILE;

#ifdef GENERATE_FILE
#include "file_generator/generate_file.h"
#endif

#ifndef GENERATE_FILE
#include "ConcurrentDS.h"
#include <functional>
typedef std::vector<std::function<void()>> VectorFunctions;
VectorFunctions& read_file(VectorFunctions& operations, ConcurrentDS& concurrent_ds, std::ifstream& ifile);
std::function<void()> get_function(ConcurrentDS& concurrentDS, const std::vector<std::string>& line);
void do_actions_in_one_thread(const std::string&& file_name, ConcurrentDS& concurrentDS);
void do_actions_in_two_threads(const std::string&& file_name1, const std::string&& file_name2, ConcurrentDS& concurrentDS);
void do_actions_in_three_threads(const std::string&& file_name1, const std::string&& file_name2, const std::string&& file_name3, ConcurrentDS& concurrentDS);
#endif

#include <fstream>
#include <thread>
#include <sstream>
#include <chrono>
#include <barrier>
#include <iostream>


int main() {

#ifdef GENERATE_FILE
    prepare_input_files();
#endif

#ifndef GENERATE_FILE
    auto concurrentDS = std::make_unique<ConcurrentDS>();
    // In 1 thread:
    //      a) with required probabilities:
    do_actions_in_one_thread("required.txt", *concurrentDS);
    //      b) with equal probabilities:
    do_actions_in_one_thread("equal.txt", *concurrentDS);
    //      c) with opposite probabilities:
    do_actions_in_one_thread("opposite.txt", *concurrentDS);

    // In 2 threads:
    //      a) with required probabilities:
    do_actions_in_two_threads("required/1.txt", "required/2.txt", *concurrentDS);
    //      b) with equal probabilities:
    do_actions_in_two_threads("equal/1.txt", "equal/2.txt", *concurrentDS);
    //      c) with opposite probabilities:
    do_actions_in_two_threads("opposite/1.txt", "opposite/2.txt", *concurrentDS);

    // In 3 threads:
    //      a) with required probabilities:
    do_actions_in_three_threads("required/1.txt", "required/2.txt", "required/3.txt", *concurrentDS);
    //      b) with equal probabilities:
    do_actions_in_three_threads("equal/1.txt", "equal/2.txt", "equal/3.txt", *concurrentDS);
    //      c) with opposite probabilities:
    do_actions_in_three_threads("opposite/1.txt", "opposite/2.txt", "opposite/3.txt", *concurrentDS);
#endif
}

#ifndef GENERATE_FILE
VectorFunctions& read_file(VectorFunctions& operations, ConcurrentDS& concurrent_ds, std::ifstream& ifile) {
    std::string line;
    while(getline(ifile, line)) {
            std::istringstream iss(line);
            std::vector<std::string> words;
            std::string token;
            while(std::getline(iss, token, ' ')) {
                words.push_back(token);
            }
        operations.push_back(get_function(concurrent_ds, words));
    }
    return operations;
}

std::function<void()> get_function(ConcurrentDS& concurrentDS, const std::vector<std::string>& line) {
    if (line.size() == 1) {
        return [&concurrentDS](){concurrentDS.ConcurrentDS::string();};
    }
    else if (line.size() == 2) {
        int pos = std::stoi(line[1]);
        switch (pos) {
            case 0:
                return [&concurrentDS](){concurrentDS.ConcurrentDS::read1();};
            case 1:
                return [&concurrentDS](){concurrentDS.ConcurrentDS::read2();};
            case 2:
                return [&concurrentDS](){concurrentDS.ConcurrentDS::read3();};
            default:
                return [&concurrentDS](){};
        }
    }
    else {
        int pos = std::stoi(line[1]);
        int num = std::stoi(line[2]);
        switch (pos) {
            case 0:
                return [&concurrentDS, num]() {concurrentDS.ConcurrentDS::write1(num);};
            case 1:
                return [&concurrentDS, num](){concurrentDS.ConcurrentDS::write2(num);};
            case 2:
                return [&concurrentDS, num](){concurrentDS.ConcurrentDS::write3(num);};
            default:
                return [&concurrentDS](){};
        }
    }
}

void do_actions_in_one_thread(const std::string&& file_name, ConcurrentDS& concurrentDS) {
    std::ifstream ifile("../test_files/one/" + file_name);
    VectorFunctions operations;
    operations = read_file(operations, concurrentDS, ifile);
    ifile.close();

    {
        std::jthread t([&operations]() {
            auto start = std::chrono::system_clock::now();
            for (auto& function : operations) {
                function();
            }
            auto end = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            std::cout  << "1. " << duration.count() << "ns" << std::endl;
        });
    }
}

void do_actions_in_two_threads(const std::string&& file_name1, const std::string&& file_name2, ConcurrentDS& concurrentDS) {
    std::ifstream ifile1("../test_files/two/" + file_name1);
    std::ifstream ifile2("../test_files/two/" + file_name2);
    VectorFunctions operations1;
    VectorFunctions operations2;
    operations1 = read_file(operations1, concurrentDS, ifile1);
    operations2 = read_file(operations2, concurrentDS, ifile2);
    ifile1.close();
    ifile2.close();

    std::barrier barrier(2);
    {
        std::jthread t1([&operations1, &barrier]() {
            barrier.arrive_and_wait();

            auto start = std::chrono::system_clock::now();
            for (auto& function : operations1) {
                function();
            }
            barrier.arrive_and_wait();
            auto end = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            std::cout << "2. " << duration.count() << "ns" << std::endl;
        });
        std::jthread t2([&operations2, &barrier]() {
            barrier.arrive_and_wait();

            for (auto& function : operations2) {
                function();
            }
            barrier.arrive_and_wait();
        });
    }
}

void do_actions_in_three_threads(const std::string&& file_name1, const std::string&& file_name2, const std::string&& file_name3, ConcurrentDS& concurrentDS) {
    std::ifstream ifile1("../test_files/three/" + file_name1);
    std::ifstream ifile2("../test_files/three/" + file_name2);
    std::ifstream ifile3("../test_files/three/" + file_name3);
    VectorFunctions operations1;
    VectorFunctions operations2;
    VectorFunctions operations3;
    operations1 = read_file(operations1, concurrentDS, ifile1);
    operations2 = read_file(operations2, concurrentDS, ifile2);
    operations3 = read_file(operations3, concurrentDS, ifile3);
    ifile1.close();
    ifile2.close();
    ifile3.close();

    std::barrier barrier(3);
    {
        std::jthread t1([&operations1, &barrier]() {
            barrier.arrive_and_wait();

            auto start = std::chrono::system_clock::now();
            for (auto& function : operations1) {
                function();
            }
            barrier.arrive_and_wait();
            auto end = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            std::cout << "3. " << duration.count() << "ns" << std::endl;
        });

        std::jthread t2([&operations2, &barrier]() {
            barrier.arrive_and_wait();

            for (auto& function : operations2) {
                function();
            }
            barrier.arrive_and_wait();
        });
        std::jthread t3([&operations3, &barrier]() {
            barrier.arrive_and_wait();
            for (auto& function : operations3) {
                function();
            }
            barrier.arrive_and_wait();
        });
    }
}
#endif