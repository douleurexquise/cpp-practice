/*
**************************************************************************
* Нижегородский государственный технический университет *
* Лабораторная работа №1 . Задание 3. *
* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович *
**************************************************************************
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
unsigned long hashPassword(string str) {
    unsigned long hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}
int main(int argc, char* argv[]){
    if(argc < 2){
        cout << "Введите пароль!" << endl;
        return 0;
    }
    ifstream file("hashcode.txt");
    if(!file){
        cout << "Не удается открыть файл"<< endl;
        return 0;
    }
    unsigned long correctHash;
    file >> correctHash;
    file.close();
    string password = argv[1];
    unsigned long hashPass = hashPassword(password);
    if(hashPass == correctHash){
        cout << "Пароль верный!" << endl;
    }
    else{
        cout << "Пароль неверный!" << endl;
    }
    return 0;
}
