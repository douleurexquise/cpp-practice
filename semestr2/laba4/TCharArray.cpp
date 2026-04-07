#include "TCharArray.h"
#include <cstring>
#include <stdexcept>

TCharArray::TCharArray() : buf(nullptr), len(0) {}

TCharArray::TCharArray(const char* str) {
    len = strlen(str);
    buf = new char[len + 1];
    strcpy(buf, str);
}

TCharArray::TCharArray(const TCharArray& other) {
    len = other.len;
    buf = new char[len + 1];
    strcpy(buf, other.buf);
}

TCharArray::~TCharArray() {
    delete[] buf;
}

void TCharArray::set(const char* str) {
    delete[] buf;
    len = strlen(str);
    buf = new char[len + 1];
    strcpy(buf, str);
}

char* TCharArray::get() {
    return buf;
}

char& TCharArray::operator[](int index) {
    return buf[index];
}

char& TCharArray::at(int index) {
    if (index < 0 || index >= (int)len) {
        throw std::out_of_range("Index out of range");
    }
    return buf[index];
}

size_t TCharArray::size() const {
    return len;
}
