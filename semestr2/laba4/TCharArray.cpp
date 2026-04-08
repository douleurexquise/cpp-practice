#include "TCharArray.h"
#include <cstring>
#include <cassert>

TCharArray::TCharArray(){
    length = 0;
    buffer = nullptr;
};
TCharArray::TCharArray(const char* str) {
    length = strlen(str);
    buffer = new char[len+1]; // +1 для символа '\0'
    strcpy(buffer, str);
}
TCharArray::TCharArray(const TCharArray& other){
    length = other.len;
    buffer = new char[len];
    strcpy(buffer, other.buffer);
}
TCharArray::~TCharArray() {
    delete[] buffer;
}
void TCharArray::set(const char* str) {
    delete[] buf;
    len = strlen(str);
    buf = new char[len + 1];
    strcpy(buf, str);
}
char* TCharArray::get() {
    return buffer;
}
char& TCharArray::operator[](int index) {
    return buffer[index];
}
char& TCharArray::at(int index) {
    assert(index >= 0 && index < (int)length);
    return buffer[index];
}
size_t TCharArray::size() const {
    return length;
}
