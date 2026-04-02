#include <iostream>
#include <fstream>
#include <iomanip>
#include "mylib.h"
using namespace std;

void print_help(char* prog_name){
    cout << "Справка по программе:\n" << prog_name <<
    " --help или -h - вызов справки\n" << prog_name <<
    " -c [N] [file_name] - создание файла file_name с N количеством записей\n" <<
    prog_name << " -r [N] [file_name] - чтение файла file_name, вывод на экран N записей" << endl;
}
// TODO : РАЗБИТЬ ФУНКЦИЮ НА ПОСТРОЧНЫЙ ВВОД, ДОБАВИТЬ ПРОВЕРКУ cin
void create(Airplane& a, int index){
    cout << "\nЗапись №" << index + 1 << endl;
    cout << "Введите тип самолета: ";
    cin >> a.type;
    cout << "Введите фамилию конструктора: ";
    cin >> a.constructor;
    cout << "Введите год выпуска: ";
    cin >> a.year;
    if(!cin.good()){
        cout << "Введите целое число" << endl;
        return;
    }
    cout << "Введите количество кресел: ";
    cin >> a.seats;
    if(!cin.good()){
        cout << "Введите целое число" << endl;
        return;
    }
    cout << "Введите грузоподъемность в тоннах: ";
    cin >> a.capacity;
    if(!cin.good()){
        cout << "Введите целое число" << endl;
        return;
    }
}

void print_header() {
    cout << "\n" << left << setw(20) << "Тип"
              << setw(20) << "Конструктор"
              << setw(8)  << "Год"
              << setw(10) << "Кресел"
              << setw(20) << "Грузоподъемность(т)"
              << "\n" << endl;
}

void print_row(Airplane a) {
    cout << left
         << setw(20) << a.type
         << setw(20) << a.constructor
         << setw(8)  << a.year
         << setw(10) << a.seats
         << setw(20) << a.capacity
         << "\n";
}

int save_row(char* filename, Airplane* arr, int size){
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Невозможно открыть файл '" << filename << "' для записи.\n";
        return -1;
    }
    for (int i = 0; i < size; i++) {
        file << arr[i].type << " "
             << arr[i].constructor << " "
             << arr[i].year << " "
             << arr[i].seats << " "
             << arr[i].capacity << "\n";
    }
    file.close();
    return size;
}

int load_row(char* filename, Airplane* arr, int n){
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Невозможно открыть файл '" << filename << "' для чтения.\n";
        return 0;
    }
    int count = 0;
    while (count < n &&
           file >> arr[count].type
                >> arr[count].constructor
                >> arr[count].year
                >> arr[count].seats
                >> arr[count].capacity) {
        count++;
    }
    if (count == 0) {
        cout << "Файл '" << filename << "' пуст или содержит некорректные данные.\n";
    }
    file.close();
    return count;
}
