#ifndef MYLIB_H
#define MYLIB_H

#include <cstdio>
#include <string>
using namespace std;
struct Airplane {
    string type;      // Наименование типа
    string constructor;    // Фамилия конструктора
    int year;               // Год выпуска
    int seats;              // Количество кресел
    double capacity;     // Грузоподъёмность, т
};


#endif
