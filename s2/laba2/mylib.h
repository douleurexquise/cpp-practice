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

// Прототипы функций
void print_help(char* prog_name);
void create(Airplane& a, int index);
void print_header();
void print_row(Airplane a);
int  save_row(char* filename, Airplane* arr, int n);
int  load_row(char* filename, Airplane* arr, int n);

#endif
