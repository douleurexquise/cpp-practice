#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "Airplane.h"
using namespace std;
void print_help(const char* prog_name){
    cout << "Справка по программе:\n" << prog_name <<
    " --help или -h - вызов справки\n" << prog_name <<
    " -c [N] [file_name] - создание файла file_name с N количеством записей\n" <<
    prog_name << " -r [N] [file_name] - чтение файла file_name, вывод на экран N записей" << endl;
}
bool read_string(const char* request, char* buffer){
    cout << request;
    if (!(cin >> buffer)) {
        cout << "Ошибка чтения строки." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    buffer[29] = '\0';
    return true;
}
bool read_int(const char* request, int& buffer){
    cout << request;
    if (!(cin >> buffer)) {
        cout << "Ошибка: введите целое число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}
bool read_double(const char* request, double& buffer){
    cout << request;
    if (!(cin >> buffer)) {
        cout << "Ошибка: введите число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
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
         << setw(20) << a.get_type()
         << setw(20) << a.get_constructor()
         << setw(8)  << a.get_year()
         << setw(10) << a.get_seats()
         << setw(20) << a.get_capacity()
         << "\n";
}
int save_row(const char* filename, Airplane* arr, int size){
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Невозможно открыть файл '" << filename << "' для записи.\n";
        return -1;
    }
    for (int i = 0; i < size; i++) {
        Airplane& plane = arr[i];
        file << plane.get_type() << " "
             << plane.get_constructor() << " "
             << plane.get_year() << " "
             << plane.get_seats() << " "
             << plane.get_capacity() << endl;
    }
    file.close();
    cout << "Строка сохранена" << endl;
    return 0;
}
int load_row(const char* filename, Airplane* arr, int n){
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Невозможно открыть файл '" << filename << "' для чтения.\n";
        return -1;
    }
    int count = 0;
    char type[30];
    char constructor[30];
    int year;
    int seats;
    double capacity;
    while (count < n &&
           file >> type >> constructor >> year >> seats >> capacity)
           {
        arr[count].set_type(type);
        arr[count].set_constructor(constructor);
        arr[count].set_year(year);
        arr[count].set_seats(seats);
        arr[count].set_capacity(capacity);
        count++;
    }
    if (count == 0) {
        cout << "Файл '" << filename << "' пуст или содержит некорректные данные.\n";
    }
    file.close();
    return count;
}
