// generate_file.cpp
// Created by Yana Utochkina

#include "generate_file.h"
#include <fstream>

std::string get_operation(const int& id) {
    switch (id) {
        case Operation::READ: return "read";
        case Operation::WRITE: return "write";
        default: return "unknown";
    }
}

std::string get_action(const int& int_op) {
    std::string str_op;
    if (int_op == 2) return "string";
    else {
        str_op = get_operation(int_op % 10) + " ";
        str_op += std::to_string(int_op / 10 - 1);
        str_op = str_op + " 3";
    }
    return str_op;
}

void generate_file(const std::string&& name, const int&& size, const Distribution&& distribution) {
    std::ofstream ofile(name + ".txt");

    Random random;
    switch (distribution) {
        case REQUIREMENT:
            random.set_distribution(required);
        case EQUAL:
            random.set_distribution(equal);
        case OPPOSITE_REQUIREMENT:
            random.set_distribution(opposite);
    }
    random.set_numbers(numbers);

    for (int i = 0; i < size; i++) {
        ofile << get_action(random()) << std::endl;
    }

    ofile.close();
}


Random::Random() {
    std::random_device rd;
    generator = std::mt19937(rd());
}

void Random::set_distribution(const std::vector<int>& probabilities) {
    distribution = std::discrete_distribution<int>(probabilities.begin(), probabilities.end());
}

void Random::set_numbers(const std::vector<int>& numbers) {
    this->numbers = std::vector<int>(numbers);
}

int Random::operator()() {
    return this->numbers[distribution(generator)];
}


