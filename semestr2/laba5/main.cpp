/*
**************************************************************************
* Нижегородский государственный технический университет *
* Лабораторная работа №5. Задание 1. *
* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович *
**************************************************************************
*/
#include <iostream>
#include <fstream>
#include <string>
#include "Notification.h"
#include "Warning.h"
#include "Error.h"
using namespace std;
int main() {
    char logo[]=
 "**************************************************************************\n"
 "* Нижегородский государственный технический университет *\n"
 "* Лабораторная работа №5. Задание 1. *\n"
 "* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович*\n"
 "**************************************************************************\n";
	cout << logo;
    Event* events[100];
    int count = 0;
    ifstream file("test");
    if (!file.is_open()) {
        cout << "Ошибка: файл не найден\n";
        return 1;
    }
    while (!file.eof()) {
        if (count >= 100) {
            cout << "Ошибка: слишком много событий (макс 100)\n";
            return 1;
        }
        int type;
        string message;
        file >> type;
        file.ignore();
        getline(file, message);
        if (type == 1) {
            events[count] = new Notification(message);
        }
        else if (type == 2) {
            events[count] = new Warning(message);
        }
        else if (type == 3) {
            events[count] = new Error(message);
        }
        else {
            cout << "Ошибка: неверный тип события в файле\n";
            return 1;
        }
        count++;
    }
    file.close();
    if (count == 0) {
        cout << "Ошибка: файл пуст или некорректен\n";
        return 1;
    }
    cout << "События:\n";
    for (int i = 0; i < count - 1; i++) {
        cout << i + 1 << ". ";
        events[i]->print();
    }
    for(int i = 0; i < count;i++){
        delete events[i];
    }
    return 0;
}
