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
    prog_name << " -r [N] [file_name] - чтение файла file_name, вывод на экран N записей\n" <<
    prog_name << " -a [N] [file_name] - добавление N записей в конец файла\n" <<
    prog_name << " -e [N] [file_name] - редактирование N записи\n";
}
bool read_string(const char* request,String& buffer){
    cout << request;
    char temp[30];
    if (!(cin >> temp)) {
        cout << "Ошибка чтения строки" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    buffer.set(temp);
    return true;
}
bool read_int(const char* request, int& buffer){
    cout << request;
    if (!(cin >> buffer)) {
        cout << "Ошибка: введите целое число" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}
bool read_double(const char* request, double& buffer){
    cout << request;
    if (!(cin >> buffer)) {
        cout << "Ошибка: введите число" << endl;
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
void print_row(Airplane& a) {
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
    file << size << "\n"; // 1я строка файла - количество записей
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
    int totalCount;
    if (!(file >> totalCount) || totalCount <= 0) {
        cout << "Файл '" << filename << "' пуст или содержит некорректные данные.\n";
        file.close();
        arr = nullptr;
        return -1;
    }
    int arrSize;
    if(n > totalCount){
        arrSize = totalCount;
    }
    else{
        arrSize = n;
    }
    arr = new Airplane[arrSize];
    char type[30];
    char constructor[30];
    int year;
    int seats;
    double capacity;
    int count = 0; // счетчик
    while (count < arrSize &&
           file >> type >> constructor >> year >> seats >> capacity)
    {
        arr[count].set_type(type);
        arr[count].set_constructor(constructor);
        arr[count].set_year(year);
        arr[count].set_seats(seats);
        arr[count].set_capacity(capacity);
        count++;
    }
    file.close();
    return count;
}
int countRecords(const char* filename){
    ifstream file(filename);
    if(!file.is_open()){
        cout << "Ошибка чтения из файла\n";
        return -1;
    }
    int count;
    file >> count;
    return count;
}
int create(int n, const char* filename){
    Airplane* arr = new Airplane[n];
    cout << "Режим создания. Введите " << n << " записей:\n";
    bool valid = true;
    for (int i = 0; i < n && valid; i++) {
        String type;
        String constructor;
        int year;
        int seats;
        double capacity;
        cout << "\nЗапись №" << i + 1 << endl;
        if (!read_string("Введите тип самолета: ", type)){
            valid = false;
            break;
        }
        if (!read_string("Введите фамилию конструктора: ", constructor)){
            valid = false;
            break;
        }
        if (!read_int("Введите год выпуска: ", year)){
            valid = false;
            break;
        }
        if (!read_int("Введите количество кресел: ", seats)){
            valid = false;
            break;
        }
        if (!read_double("Введите грузоподъемность в т.: ", capacity)){
            valid = false;
            break;
        }
        arr[i] = Airplane(type.get(), constructor.get(), year, seats, capacity);
    }

    if (!valid) {
        delete[] arr;
        return 0;
    }
    int result = save_row(filename, arr, n);
    delete[] arr;
    if(result != 0){
        cout << "Ошибка создания файла\n";
    }
    return 0;
}
int read(int n, const char* filename){
    ifstream file(filename);
    if(!file.is_open()){
        cout << "Ошибка чтения файла\n";
        return -1;
    }
    Airplane* arr = new Airplane[n];
    cout << "Режим чтения. Файл: '" << filename
         << "', запрос: " << n << " записей\n";
    int countRecords;
    file >> countRecords;
    int count = load_row(filename, arr, n);
    if (count < 0) {
            delete[] arr;
            return -1;
        }
    if (count > 0) {
        print_header();
        for (int i = 0; i < count; i++) {
                print_row(arr[i]);
        }
        cout << "\nВыведено записей: " << count;
            if (count < n) {
                cout << " (в файле было меньше " << n << ")";
            }
            cout << "\n";
        }
        file.close();
        delete[] arr;
        return 0;
    }
int append(int n, const char* filename){
    ofstream file(filename);
    Airplane* arr = new Airplane[n];
    if(!file.is_open()){
        delete[] arr;
        return -1;
    }
    int count = countRecords(filename);
    int oldCount = load_row(filename, arr, count);
    int newLength = oldCount + n;
    Airplane* newArr = new Airplane[newLength];
    file << newLength;
    for(int i = 0; i < oldCount; i++){
        newArr[i] = arr[i];
    }
    delete[] arr;
    cout << "Режим добавления в файл '" << filename << "'\n";
    for(int i = oldCount; i < newLength; i++){
        Airplane& plane = arr[i];
        file << plane.get_type() << " "
             << plane.get_constructor() << " "
             << plane.get_year() << " "
             << plane.get_seats() << " "
             << plane.get_capacity() << endl;
    }
    cout << "Записи добавлены\n";
    delete[] newArr;
    return 0;
}

int edit(int index, const char* filename){
    ofstream file(filename);
    if(!file.is_open()){
        cout << "Ошибка записи в файл\n";
        return -1;
    }
    Airplane* arr = new Airplane[index];
    int count = load_row(filename, arr, index);
    if (count < 0) {
        cout << "Данные повреждены\n";
        return -1;
    }
    if (count == 0) {
        cout << "Файл пуст\n";
        return -1;
    }
    if (index < 0 || index >= count) {
        cout << "Нет такой записи\n";
        return -1;
    }
    cout << "\nРедактирование записи №" << index + 1 << endl;
    String type, constructor;
    int year, seats;
    double capacity;
    if (!read_string("Введите тип самолета: ", type)){
        return -1;
    }
    if (!read_string("Введите фамилию конструктора: ", constructor)) {
        return -1;
    }
    if (!read_int("Введите год выпуска: ", year)) {
        return -1;
    }
    if (!read_int("Введите количество кресел: ", seats)) {
        return -1;
    }
    if (!read_double("Введите грузоподъемность: ", capacity)) {
        return -1;
    }
    arr[index] = Airplane(type.get(), constructor.get(), year, seats, capacity);
    return save_row(filename, arr, count);
}
