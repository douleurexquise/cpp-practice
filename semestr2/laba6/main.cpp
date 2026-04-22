/*
**************************************************************************
* Нижегородский государственный технический университет *
* Лабораторная работа №6. Задание 1. *
* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович *
**************************************************************************
*/
#include "Elevator.h"
#include <iostream>
#define INPUT "<< INPUT >>"
#define OUTPUT "<< OUTPUT >> "
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

    // --- Режим конфигурации ---
    if (argc == 3) {
        string user = argv[1];
        string password = argv[2];
        if (user != "admin" || password != "_SuperUser5422") {
            cout << "Неверный логин или пароль\n";
            return 1;
        }
        int floors, lockedFloor;
        string code;
        cout << "Введите количество этажей: ";
        cin >> floors;
        cout << "Введите закрытый этаж (-1 если нет): ";
        cin >> lockedFloor;
        if (lockedFloor != -1) {
            cout << "Введите код доступа: ";
            cin >> code;
        }
        elevator.setConfig(floors, lockedFloor, code);
        elevator.saveConfig(configFile);
        cout << "Конфигурация сохранена\n";
        return 0;
    }
    // --- Рабочий режим ---
    elevator.loadConfig(configFile);
    int command;
    while (true) {
        cout << INPUT;
        cin >> command;
        if (command == 0) break;
        if (command == -1) {
            cout << "Выход\n";
            break;
        }
        if (!elevator.checkAccess(command, "")) {
            string code;
            cout << "Введите код: ";
            cin >> code;
            if (!elevator.checkAccess(command, code)) {
                cout << OUTPUT << "Доступ запрещен\n";
                continue;
            }
        }
        elevator.moveToFloor(command);
    }
    return 0;
}
