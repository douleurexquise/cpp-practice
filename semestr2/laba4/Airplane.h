#ifndef AIRPLANE_H
#define AIRPLANE_H
#include "String.h"
class Airplane {
private:
    String type;
    String constructor;
    int year;
    int seats;
    double capacity;
public:
    Airplane();
    Airplane(const char*, const char*, int, int, double);
    ~Airplane();
    const char* get_type();
    const char* get_constructor();
    int get_year();
    int get_seats();
    double get_capacity();
    void set_type(const char*);
    void set_constructor(const char*);
    void set_year(int);
    void set_seats(int);
    void set_capacity(double);
};

#endif
