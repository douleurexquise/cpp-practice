#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <cstdio>
#include <string>
using namespace std;

struct Airplane {
    string type; // тип самолета
    string constructor;// фамилия конструктора
    int year; // год выпуска
    int seats; // количество кресел
    int capacity;// грузоподъёмность
};

// Прототипы функций
void print_help(const string& prog_name); // const для невозможности изменений, & для передачи ссылки
void create_airplane(Airplane& a, int index);
void print_header();
void print_row(const Airplane& a);
int  save_row(const string& filename, Airplane* arr, int n);
int  load_row(const string& filename, Airplane* arr, int n);

#endif
