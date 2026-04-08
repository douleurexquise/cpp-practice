/*
**************************************************************************
* Нижегородский государственный технический университет *
* Лабораторная работа №4 . Задание 1. *
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
    void print_row(Airplane& a);
    int save_row(const char* filename, Airplane* arr, int n);
    int load_row(const char* filename, Airplane* arr, int n);
    int create(int n, const char* filename);
    int read(int n, const char* filename);
    int append(int n, const char* filename);
    int edit(int index, const char* filename);
int main(int argc, char* argv[]) {
    char logo[]=
 "**************************************************************************\n"
 "* Нижегородский государственный технический университет *\n"
 "* Лабораторная работа №4 . Задание 1. *\n"
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
    bool is_read = (key == "-r" || key == "--read");
    bool is_append = (key == "-a" || key == "--append");
    bool is_edit = (key == "-e" || key == "--edit");
    if (!(is_create || is_read || is_append || is_edit)) {
        cout << "Ошибка: неизвестный ключ '" << key << "'.\n"
             << "Допустимые ключи: -h, -c, -r, -a, -e\n";
        return 0;
    }
    if(is_create){
        create(n, filename);
        cout << "Созданы записи\n";
    }
    if(is_read){
        read(n, filename);
    }
    if(is_append){
        append(n, filename);
        cout << "Записи добавлены\n";
    }
    if(is_edit){
        edit(n, filename);
    }
return 0;
}
