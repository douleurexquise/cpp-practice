/*
**************************************************************************
* Нижегородский государственный технический университет *
* Лабораторная работа №1 . Задание 1. *
* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович *
**************************************************************************
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Неверное имя файла" << endl;
        return 0;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "Не получается открыть файл" << endl;
        return 0;
    }
    int lines = 30;
    string line;
    int count = 0;
    while (getline(file, line)) {
        cout << line << endl;
        count++;
        if (count == lines) {
            cout << "\nEnter - далее, q - выйти";
            char ch = cin.get();
            if (ch == 'q') {
                break;
            }
            count = 0;
        }
    }
    file.close();
    return 0;
}
