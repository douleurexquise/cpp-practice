/*
**************************************************************************
* Нижегородский государственный технический университет *
* Лабораторная работа №2 . Задание 1. *
* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович *
**************************************************************************
*/
#include <iostream>
#include <string>
#include "mylib.h"
using namespace std;
// Прототипы функций
void print_help(char* prog_name);
void create(Airplane& a, int index);
void print_header();
void print_row(Airplane a);
int  save_row(char* filename, Airplane* arr, int n);
int  load_row(char* filename, Airplane* arr, int n);

int main(int argc, char* argv[]) {
    char logo[]=
 "**************************************************************************\n"
 "* Нижегородский государственный технический университет *\n"
 "* Лабораторная работа №2 . Задание 1. *\n"
 "* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович*\n"
 "**************************************************************************\n";
	cout << logo;
    if (argc < 2) {
        cout << "Не указаны аргументы.\n"
             << "Запустите '" << argv[0] << " --help' для справки.\n";
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
        cout << "Режим создания. Введите " << n << " записей):\n";
        for (int i = 0; i < n; i++) {
            create(arr[i], i);
        }
        for(int i = 0; i < n; i++)
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
