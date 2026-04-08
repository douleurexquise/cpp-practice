#ifndef TCHARARRAY_H
#define TCHARARRAY_H
#include <cstddef>
class TCharArray {
protected:
    char* buffer;
    size_t length;
public:
    TCharArray();
    TCharArray(const char* str);
    TCharArray(const TCharArray& other);
    ~TCharArray();
    void set(const char* str);
    char* get();
    char& operator[](int index);
    TCharArray& operator=(const TCharArray& other);
    char& at(int index);
    size_t size() const;
};

#endif
