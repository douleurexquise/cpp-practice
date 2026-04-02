/*
**************************************************************************
* Нижегородский государственный технический университет *
* Лабораторная работа №2 . Задание 1. *
* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович *
**************************************************************************
*/
#include <iostream>
#include <string>
#include "lib.h"
using namespace std;
int main(int argc, char* argv[]) {
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
        return 1;
    }
    int n = stoi(argv[2]);
    string filename = argv[3];
    if (n <= 0) {
        cerr << "Ошибка: N должно быть положительным числом.\n";
        return 1;
    }
    bool is_create = (key == "-c" || key == "--create");
    bool is_read   = (key == "-r" || key == "--read");
    if (!is_create && !is_read) {
        cerr << "Ошибка: неизвестный ключ '" << key << "'.\n"
             << "Допустимые ключи: -c, -r, -h\n";
        return 1;
    }
    Airplane* arr = new Airplane[n];
    if (is_create) {
        cout << "Режим создания. Введите " << n << " запис(и/ей):\n";
        for (int i = 0; i < n; i++) {
            create_airplane(arr[i], i);
        }
        if (save_row(filename, arr, n) != 0) {
            delete[] arr;
            return 1;
        }
    }
    else {
        cout << "Режим чтения. Файл: '" << filename
             << "', запрос: " << n << " запис(и/ей)\n";
        int count = load_row(filename, arr, n);
        if (count < 0) {
            delete[] arr;
            return 1;
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
