#include "Elevator.h"
#include <iostream>
#include <fstream>
using namespace std;
Elevator::Elevator() {
    floors = 0;
    currentFloor = 1;
    lockedFloor = -1;
    accessCode = "";
}

void Elevator::setConfig(int f,bool hasLF, int lf, const string& code) {
    floors = f;
    hasLockedFloor = hasLF;
    lockedFloor = lf;
    accessCode = code;
}

void Elevator::saveConfig(const string& filename) {
    ofstream file(filename);
    file << floors << endl;
    if(hasLockedFloor){
        file << "YES" << endl;
        file << lockedFloor << endl;
        file << accessCode << endl;
    }
    else{
        file << "NO" << endl;
    }
    file.close();
}

int Elevator::loadConfig(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Ошибка загрузки конфигурации\n";
        return -1;
    }
    file >> floors;
    string str;
    file >> str;
    if(str == "YES"){
        hasLockedFloor = true;
    }
    else if(str == "NO"){
        hasLockedFloor = false;
    }
    else{
        cout << "Ошибка, ожидается YES или NO\n";
        file.close();
        floors = 0;
        return -1;
    }
    if(hasLockedFloor){
        file >> lockedFloor;
        file >> accessCode;
    }
    file.close();
    return 0;
}

bool Elevator::checkAccess(int floor, const string& code) {
    if (hasLockedFloor && floor == lockedFloor) {
        return code == accessCode;
    }
    return true;
}

void Elevator::moveToFloor(int targetFloor) {
    if (targetFloor < 1 || targetFloor > floors) {
        cout  <<  "Неверный этаж\n";
        return;
    }

    if (targetFloor > currentFloor) {
        for (int i = currentFloor + 1; i <= targetFloor; i++) {
            cout << "Текущий этаж: " << i << endl;
        }
    } else if (targetFloor < currentFloor) {
        for (int i = currentFloor - 1; i >= targetFloor; i--) {
            cout << "Текущий этаж: " << i << endl;
        }
    }
    currentFloor = targetFloor;
}
