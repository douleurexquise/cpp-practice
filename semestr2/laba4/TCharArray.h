#ifndef TCHARARRAY_H
#define TCHARARRAY_H
#include <cstddef>
class TCharArray {
private:
    char* buf;
    size_t len;
public:
    TCharArray();
    TCharArray(const char* str);
    TCharArray(const TCharArray& other);
    ~TCharArray();
    void set(const char* str);
    char* get();
    char& operator[](int index);
    char& at(int index);
    size_t size() const;
};

#endif
