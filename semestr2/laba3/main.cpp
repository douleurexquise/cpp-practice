/*
**************************************************************************
* Нижегородский государственный технический университет *
* Лабораторная работа №3 . Задание 1. *
* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович *
**************************************************************************
*/
#include <iostream>
#include <string>
#include "mylib.h"
using namespace std;
//Прототипы функций
    void print_help(const char* prog_name);
    bool read_string(const char* request, char* buffer);
    bool read_int(const char* request, int& buffer);
    bool read_double(const char* request, double& buffer);
    void print_header();
    void print_row(Airplane a);
    int  save_row(const char* filename, Airplane* arr, int n);
    int  load_row(const char* filename, Airplane* arr, int n);

int main(int argc, char* argv[]) {
    char logo[]=
 "**************************************************************************\n"
 "* Нижегородский государственный технический университет *\n"
 "* Лабораторная работа №3 . Задание 1. *\n"
 "* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович*\n"
 "**************************************************************************\n";
	cout << logo;
    if (argc < 2) {
        cout << "Не указаны аргументы.\n"
             << "Запустите '" << argv[0] << " --help' или '-h' для справки.\n";
        return 0;
    }
    string key = argv[1];
    if (key == "-h" || key == "--help") {
        print_help(argv[0]);
        return 0;
    }
    if (argc != 4) {
        cout << "Ошибка: ожидается 3 аргумента: ключ, N, файл.\n"
             << "Запустите '" << argv[0] << " --help' для справки.\n";
        return 0;
    }
    int n;
    try{
    n = stoi(argv[2]);
    }
    catch(const invalid_argument&){
        cout << "Введите целое число" << endl;
        return 0;
    }
    char* filename = argv[3];
    if (n <= 0) {
        cout << "Ошибка: N должно быть положительным числом.\n";
        return 0;
    }
    bool is_create = (key == "-c" || key == "--create");
    bool is_read   = (key == "-r" || key == "--read");
    if (!is_create && !is_read) {
        cout << "Ошибка: неизвестный ключ '" << key << "'.\n"
             << "Допустимые ключи: -c, -r, -h\n";
        return 0;
    }
    Airplane* arr = new Airplane[n];
    if (is_create) {
    cout << "Режим создания. Введите " << n << " записей:\n";
    bool valid = true;
    for (int i = 0; i < n && valid; i++) {
        char type[30];
        char constructor[30];
        int year;
        int seats;
        double capacity;
        cout << "\nЗапись №" << i + 1 << endl;
        if (!read_string("Введите тип самолета: ", type)){
            valid = false;
            break;
        }
        if (!read_string("Введите фамилию конструктора: ", constructor)){
            valid = false;
            break;
        }
        if (!read_int("Введите год выпуска: ", year)){
            valid = false;
            break;
        }
        if (!read_int("Введите количество кресел: ", seats)){
            valid = false;
            break;
        }
        if (!read_double("Введите грузоподъемность в т.: ", capacity)){
            valid = false;
            break;
        }
        arr[i] = Airplane(type, constructor, year, seats, capacity);
    }

    if (!valid) {
        delete[] arr;
        return 0;
    }
    if (save_row(filename, arr, n) != 0) {
        delete[] arr;
        return 0;
    }
}
    else {
        cout << "Режим чтения. Файл: '" << filename
             << "', запрос: " << n << " записей\n";
        int count = load_row(filename, arr, n);
        if (count < 0) {
            delete[] arr;
            return 0;
        }
        if (count > 0) {
            print_header();
            for (int i = 0; i < count; i++) {
                print_row(arr[i]);
            }
            cout << "\nВыведено записей: " << count;
            if (count < n) {
                cout << " (в файле было меньше " << n << ")";
            }
            cout << "\n";
        }
    }
    delete[] arr;
    return 0;
}
