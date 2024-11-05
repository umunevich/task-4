// generate_file.h
// Created by Yana Utochkina

#ifndef GENERATE_FILE_H
#define GENERATE_FILE_H

#include <string>
#include <vector>
#include <random>
#include <thread>

enum Distribution {
    REQUIREMENT,
    EQUAL,
    OPPOSITE
};

enum Operation {
    READ,
    WRITE,
    STRING
};

void prepare_input_files();
void generate_file(const std::string&&, const int&&, const Distribution&&);

// probabilities
const std::vector<int> required = {10, 10, 10, 10, 40, 5, 15};
const std::vector<int> equal = {1, 1, 1, 1, 1, 1, 1};
const std::vector<int> opposite = {90, 90, 90, 90, 60, 95, 85};

// operations
const std::vector<int> numbers = {10 + READ, 10 + WRITE, 20 + READ, 20 + WRITE, 30 + READ, 30 + WRITE, STRING}; // {10, 11, 20, 21, 30, 31, 2 }

class Random {
    std::mt19937 generator;
    std::discrete_distribution<> distribution;
    std::vector<int> numbers;
public:
    Random();
    void set_distribution(const std::vector<int>& probabilities);
    void set_numbers(const std::vector<int>& numbers);
    int operator()();
};

#endif //GENERATE_FILE_H
