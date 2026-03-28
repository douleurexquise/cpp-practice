/*
**************************************************************************
* Нижегородский государственный технический университет *
* Лабораторная работа №1 . Задание 4. *
* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович *
**************************************************************************
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Не удалось найти файл!" << endl;
        return 0;
    }
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл '" << endl;
        return 0;
    }
    cout << "Файл: " << argv[1] << endl;
    string line;
    while (getline(file, line)) {
        if (line.length() > 80) {
            line = line.substr(0, 80);
        }
        cout << line << std::endl;
    }
    file.close();
    return 0;
}
