#include "String.h"
#include <cstring>

String::String() : TCharArray() {}

String::String(const char* str) : TCharArray(str) {}

String::String(const String& other) : TCharArray(other) {}

String String::operator+(const String& other) {
    size_t newLen = len + other.len;
    char* temp = new char[newLen + 1];

    strcpy(temp, buf);
    strcat(temp, other.buf);

    String result(temp);
    delete[] temp;
    return result;
}

bool String::operator==(const String& other) {
    return strcmp(buf, other.buf) == 0;
}

bool String::operator!=(const String& other) {
    return !(*this == other);
}

bool String::operator>(const String& other) {
    return strcmp(buf, other.buf) > 0;
}

bool String::operator<(const String& other) {
    return strcmp(buf, other.buf) < 0;
}
