// ConcurrentDS.h
// Created by Yana Utochkina

#ifndef CONCURRENTDS_H
#define CONCURRENTDS_H

#include <mutex>
#include <string>
#include <shared_mutex>

class ConcurrentDS {
private:
    const int size = 3;
    int* data;
    mutable std::mutex m1;
    mutable std::mutex m2;
    mutable std::shared_mutex m3;
public:
    ConcurrentDS() : data(new int[size] {0, 0, 0}) {}
    ~ConcurrentDS() { delete[] data; }

    void write1(int); // 10%
    void write2(int); // 10%
    void write3(int); // 5%
    int read1(); // 10%
    int read2(); // 10%
    int read3(); // 40%
    explicit operator std::string(); // 15%
};

#endif //CONCURRENTDS_H
