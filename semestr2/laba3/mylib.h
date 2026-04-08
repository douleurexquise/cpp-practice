#ifndef MYLIB_H
#define MYLIB_H
#include <cstring>
class Airplane {
    private:
    char type[30];      // Наименование типа
    char constructor[30];    // Фамилия конструктора
    int year;               // Год выпуска
    int seats;              // Количество кресел
    double capacity;     // Грузоподъёмность, т
    public:
    Airplane();
    Airplane(const char*,const char*,int,int,double);
    ~Airplane();
    const char* get_type();
    const char* get_constructor();
    int get_year();
    int get_seats();
    double get_capacity();
    void set_type(const char* _type);
    void set_constructor(const char* _constructor);
    void set_year(int _year);
    void set_seats(int _seats);
    void set_capacity(double _capacity);
};

#endif
