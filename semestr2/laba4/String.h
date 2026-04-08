#ifndef STRING_H
#define STRING_H
#include "TCharArray.h"
class String : public TCharArray {
public:
    String();
    String(const char* str);
    String(const String& other);
    ~String();
    String operator+(const String& other);
    bool operator==(const String& other);
    bool operator!=(const String& other);
    bool operator>(const String& other);
    bool operator<(const String& other);
};

#endif
