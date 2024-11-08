// ConcurrentDS.cpp
// Created by Yana Utochkina

#include "ConcurrentDS.h"

#include <iostream>
#include <ostream>

void ConcurrentDS::write1(int x) {
    //std::cout << "write1 " << x << std::endl;
    std::lock_guard lock(m1);
    data[0] = x;
}

void ConcurrentDS::write2(int x) {
    //std::cout << "write2 " << x << std::endl;
    std::lock_guard lock(m2);
    data[1] = x;
}

void ConcurrentDS::write3(int x) {
    //std::cout << "write3 " << x << std::endl;
    std::unique_lock<std::shared_mutex> lock(m3/*, std::defer_lock*/);
    data[2] = x;
}

int ConcurrentDS::read1() {
    int x;
    {
        std::lock_guard lock(m1);
        x = data[0];
        //std::cout << "read1 " << x << std::endl;
    }
    return x;
}

int ConcurrentDS::read2() {
    int x;
    {
        std::lock_guard lock(m2);
        x = data[1];
        //std::cout << "read2 " << x << std::endl;
    }
    return x;
}

int ConcurrentDS::read3() {
    int x;
    {
        std::shared_lock<std::shared_mutex> lock(m3);
        x = data[2];
        //std::cout << "read3 " << x << std::endl;

    }
    return x;
}

std::string ConcurrentDS::string() {
    std::string result;
    {
        std::scoped_lock lock(m1, m2, m3);
        for (int i = 0; i < size; i++) {
            result += std::to_string(data[i]);
        }
    }
    //std::cout << result << std::endl;
    return result;
}