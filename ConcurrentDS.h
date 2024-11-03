// ConcurrentDS.h
// Created by Yana Utochkina

#ifndef CONCURRENTDS_H
#define CONCURRENTDS_H

#include <mutex>
#include <string>

class ConcurrentDS {
private:
    const int size = 3;
    int* data;
    std::mutex m1;
    std::mutex m2;
    std::mutex m3;
public:
    ConcurrentDS() : data(new int[size] {0, 0, 0}) {}
    ~ConcurrentDS() { delete[] data; }

    void write1(int); // 10%
    void write2(int); // 10%
    void write3(int); // 40%
    int read1(); // 10%
    int read2(); // 10%
    int read3(); // 5%
    //explicit operator std::string() const(ConcurrentDS &); // 15%
};

#endif //CONCURRENTDS_H
