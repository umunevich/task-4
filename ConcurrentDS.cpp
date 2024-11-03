// ConcurrentDS.cpp
// Created by Yana Utochkina

#include "ConcurrentDS.h"

void ConcurrentDS::write1(int x) {
    std::lock_guard lock(m1);
    data[0] = x;
}

void ConcurrentDS::write2(int x) {
    std::lock_guard lock(m2);
    data[1] = x;
}

void ConcurrentDS::write3(int x) {
    std::lock_guard lock(m3);
    data[2] = x;
}

int ConcurrentDS::read1() {
    int x;
    {
        std::lock_guard lock(m1);
        x = data[0];
    }
    return x;
}

int ConcurrentDS::read2() {
    int x;
    {
        std::lock_guard lock(m2);
        x = data[1];
    }
    return x;
}

int ConcurrentDS::read3() {
    int x;
    {
        std::lock_guard lock(m3);
        x = data[2];
    }
    return x;
}

/*ConcurrentDS::operator std::string() const(ConcurrentDS) {
    std::string result = "";
    {
        std::scoped_lock lock(m1, m2, m3);
        for (int i = 0; i < size; i++) {
            result += data[i];
        }
    }
    return result;
}*/