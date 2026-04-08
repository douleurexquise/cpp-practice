#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "mylib.h"
using namespace std;
Airplane::Airplane() {
    type[0] = '\0';
    constructor[0] = '\0';
    year = 0;
    seats = 0;
    capacity = 0.0;
}
Airplane::Airplane(const char* _type, const char* _constructor,
                   int _year, int _seats, double _capacity) {
    set_type(_type);
    set_constructor(_constructor);
    set_year(_year);
    set_seats(_seats);
    set_capacity(_capacity);
}
Airplane::~Airplane(){};
    const char* Airplane::get_type(){
        return type;
    }
    const char* Airplane::get_constructor(){
        return constructor;
    }
    int Airplane::get_year(){
        return year;
    }
    int Airplane::get_seats(){
        return seats;
    }
    double Airplane::get_capacity(){
        return capacity;
    }
    void Airplane::set_type(const char* _type){
        strncpy(type, _type, 29);
        type[29] = '\0';
    }
    void Airplane::set_constructor(const char* _constructor){
        strncpy(constructor, _constructor, 29);
        constructor[29] = '\0';
    }
    void Airplane::set_year(int _year){
        year = _year;
    }
    void Airplane::set_seats(int _seats){
        seats = _seats;
    }
    void Airplane::set_capacity(double _capacity){
        capacity = _capacity;
    }
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
// Можно обойтись без функции, тк в main проверяется валидность каждой вводимой строки, затем создается экземляр класса через конструктор
/*void create(Airplane& a, int index){
    char str[30];
    int year, seats;
    double capacity;
    cout << "\nЗапись №" << index + 1 << endl;
    cout << "Введите тип самолета: ";
    cin >> str;
    a.set_type(str);
    cout << "Введите фамилию конструктора: ";
    cin >> str;
    a.set_constructor(str);
    cout << "Введите год выпуска: ";
    cin >> year;
    if(!cin.good()){
        cout << "Введите целое число" << endl;
        return;
    }
    a.set_year(year);
    cout << "Введите количество кресел: ";
    cin >> seats;
    if(!cin.good()){
        cout << "Введите целое число" << endl;
        return;
    }
    a.set_seats(seats);
    cout << "Введите грузоподъемность в тоннах: ";
    cin >> capacity;
    if(!cin.good()){
        cout << "Введите целое число" << endl;
        return;
    }
    a.set_capacity(capacity);
}
*/
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
             << plane.get_capacity() << "\n";
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
