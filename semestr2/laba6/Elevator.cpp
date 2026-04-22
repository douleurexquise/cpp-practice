#include "Elevator.h"
#include <iostream>
#include <fstream>
#define INPUT "<< INPUT >>"
#define OUTPUT "<< OUTPUT >> "
using namespace std;
Elevator::Elevator() {
    floors = 0;
    currentFloor = 1;
    lockedFloor = -1;
    accessCode = "";
}

void Elevator::setConfig(int f, int lf, const string& code) {
    floors = f;
    lockedFloor = lf;
    accessCode = code;
}

void Elevator::saveConfig(const string& filename) {
    ofstream file(filename);
    file << floors << endl;
    file << lockedFloor << endl;
    file << accessCode << endl;
    file.close();
}

void Elevator::loadConfig(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Ошибка загрузки конфигурации\n";
        return;
    }
    file >> floors;
    file >> lockedFloor;
    file >> accessCode;
    file.close();
}

bool Elevator::checkAccess(int floor, const string& code) {
    if (floor == lockedFloor) {
        return code == accessCode;
    }
    return true;
}

void Elevator::moveToFloor(int targetFloor) {
    if (targetFloor < 1 || targetFloor > floors) {
        cout << OUTPUT <<  "Неверный этаж\n";
        return;
    }

    if (targetFloor > currentFloor) {
        for (int i = currentFloor + 1; i <= targetFloor; i++) {
            cout << OUTPUT << i << endl;
        }
    } else if (targetFloor < currentFloor) {
        for (int i = currentFloor - 1; i >= targetFloor; i--) {
            cout << OUTPUT << i << endl;
        }
    }
    currentFloor = targetFloor;
}
