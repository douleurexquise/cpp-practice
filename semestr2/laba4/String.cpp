#include "String.h"
#include <cstring>
String::String() : TCharArray() {}
String::String(const char* str) : TCharArray(str) {}
String::String(const String& other) : TCharArray(other) {}
String::~String(){}
String String::operator+(const String& other) {
    size_t newLength = length + other.length;
    char* temp = new char[newLength + 1];
    strcpy(temp, buffer);
    strcat(temp, other.buffer);
    String result(temp);
    delete[] temp;
    return result;
}
bool String::operator==(const String& other) {
    return strcmp(buffer, other.buffer) == 0;
}
bool String::operator!=(const String& other) {
    return strcmp(buffer, other.buffer) != 0;;
}
bool String::operator>(const String& other) {
    return strcmp(buffer, other.buffer) > 0; // если значение различного символа по ASCII больше, то строка тоже будет больше
}
bool String::operator<(const String& other) {
    return strcmp(buffer, other.buffer) < 0;
}
