#include "TCharArray.h"
#include <cstring>
#include <cassert>
TCharArray::TCharArray(){
    length = 0;
    buffer = nullptr;
};
TCharArray::TCharArray(const char* str) {
    length = strlen(str);
    buffer = new char[length+1]; // +1 для символа '\0'
    strcpy(buffer, str);
}
TCharArray::TCharArray(const TCharArray& other){
    length = other.length;
    buffer = new char[length + 1];
    strcpy(buffer, other.buffer);
}
TCharArray::~TCharArray() {
    delete[] buffer;
}
void TCharArray::set(const char* str) {
    delete[] buffer;
    length = strlen(str);
    buffer = new char[length + 1];
    strcpy(buffer, str);
}
char* TCharArray::get() {
    return buffer;
}
char& TCharArray::operator[](int index) {
    return buffer[index];
}
TCharArray& TCharArray::operator=(const TCharArray& other) {
    if (this == &other)
        return *this;
    delete[] buffer;
    length = other.length;
    if (other.buffer != nullptr) {
        buffer = new char[length + 1];
        strcpy(buffer, other.buffer);
    } else {
        buffer = nullptr;
    }
    return *this;
}
char& TCharArray::at(int index) {
    assert(index >= 0 && index < (int)length);
    return buffer[index];
}
size_t TCharArray::size() const {
    return length;
}
