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
int main(){
    cout << "Введите пароль:" << endl;
    string password;
    cin >> password;
    unsigned long hash = hashPassword(password);
    ofstream output("hashcode.txt");
    if(!output){
        cout << "Не удается открыть файл"<< endl;
        return 0;
    }
    output << hash;
    output.close();
    return 0;
}
