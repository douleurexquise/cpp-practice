/*
**************************************************************************
* Нижегородский государственный технический университет *
* Лабораторная работа №6. Задание 1. *
* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович *
**************************************************************************
*/
#include "Elevator.h"
#include <iostream>
#include <limits>
using namespace std;
int main(int argc, char* argv[]) {
        char logo[]=
 "**************************************************************************\n"
 "* Нижегородский государственный технический университет *\n"
 "* Лабораторная работа №6. Задание 1. *\n"
 "* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович*\n"
 "**************************************************************************\n";
	cout << logo;
    Elevator elevator;
    string configFile = "config.txt";
    // config mode
    if (argc == 3) {
        string user = argv[1];
        string password = argv[2];
        if (user != "admin" || password != "adm111") {
            cout << "Неверный логин или пароль\n";
            return 1;
        }
        int floors, lockedFloor = -1;
        string strLF, code = "";
        bool hasLocked = false;
        cout << "Введите количество этажей: ";
        if (!(cin >> floors)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout  << "Ошибка: введите число\n";
            return 0;
        }
        if(floors > 25){
            cout << "Должно быть не более 25 этажей\n";
            floors = 0;
            return 0;
        }
        cout << "Есть закрытый этаж(YES/NO): ";
        cin >> strLF;
        if(strLF == "YES"){
            hasLocked = true;
            cout << "Введите номер закрытого этажа: ";
            cin >> lockedFloor;
            cout << "Введите код доступа: ";
            cin >> code;
        }
        else if(strLF == "NO"){
            hasLocked = false;
        }
        else{
            cout << "Ошибка, введите YES или NO\n";
            return 1;
        }
        elevator.setConfig(floors, hasLocked, lockedFloor, code);
        elevator.saveConfig(configFile);
        cout << "Конфигурация сохранена\n";
        return 0;
    }
    // work mode
    int confStatus = elevator.loadConfig(configFile);
    if(confStatus == -1){
        return 0;
    }
    int command;
    while (true) {
        cout << "Введите номер этажа\n";
        if (!(cin >> command)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout  << "Ошибка: введите число\n";
            continue;
        }
        if (command == 0) {
            cout <<"Выход\n";
            break;
        }
        if (!elevator.checkAccess(command, "")) {
            string code;
            cout << "Введите код: ";
            cin >> code;
            if (!elevator.checkAccess(command, code)) {
                cout  << "Доступ запрещен\n";
                continue;
            }
        }
        elevator.moveToFloor(command);
    }
    return 0;
    }
