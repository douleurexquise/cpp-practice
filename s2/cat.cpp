/*
**************************************************************************
* Нижегородский государственный технический университет *
* Лабораторная работа №1 . Задание 2. *
* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович *
**************************************************************************
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
    if(argc == 1 || argv[1] == "-"){
        string line;
        while(getline(cin, line)){
            cout << line << endl;
        }
        return 0;
    }
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "Не получается открыть файл" << endl;
        return 0;
    }
    string line;
    while(getline(file, line)){
        cout << line << endl;
    }
    file.close();
    return 0;
}
