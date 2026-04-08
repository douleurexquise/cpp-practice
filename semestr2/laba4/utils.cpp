#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "Airplane.h"
using namespace std;

void print_help(const char* prog_name) {
    cout << "Справка:\n"
         << prog_name << " --help | -h - вызов справки\n"
         << prog_name << " -c [N] [файл] - создать файл с N записями\n"
         << prog_name << " -r [N] [файл] - прочитать N записей из файла\n"
         << prog_name << " -a [N] [файл] - добавить N записей в файл\n"
         << prog_name << " -e [N] [файл] - редактировать запись N\n";
}
bool read_string(const char* request, String& buffer) {
    cout << request;
    char temp[256];
    if (!(cin >> temp)) {
        cout << "Ошибка ввода\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    buffer.set(temp);
    return true;
}
bool read_int(const char* request, int& buffer) {
    cout << request;
    if (!(cin >> buffer)) {
        cout << "Ошибка: нужно целое число\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}
bool read_double(const char* request, double& buffer) {
    cout << request;
    if (!(cin >> buffer)) {
        cout << "Ошибка: нужно число\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}
void print_header() {
    cout << "\n"
         << left
         << setw(20) << "Тип"
         << setw(20) << "Конструктор"
         << setw(8)  << "Год"
         << setw(10) << "Кресел"
         << setw(20) << "Грузоподъемность(т)"
         << "\n\n";
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
int save_row(const char* filename, Airplane* arr, int size) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл '" << filename << "' для записи\n";
        return -1;
    }
    file << size << "\n";
    for (int i = 0; i < size; i++) {
        file << arr[i].get_type()        << " "
             << arr[i].get_constructor() << " "
             << arr[i].get_year()        << " "
             << arr[i].get_seats()       << " "
             << arr[i].get_capacity()    << "\n";
    }
    file.close();
    return 0;
}
int load_row(const char* filename, Airplane** out_arr, int n) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл '" << filename << "'\n";
        return -1;
    }

    int total;
    if (!(file >> total) || total <= 0) {
        cout << "Файл пуст или повреждён\n";
        *out_arr = nullptr;
        return 0;
    }

    int arrSize = (n < total) ? n : total;
    *out_arr = new Airplane[arrSize];

    char type[256], constructor[256];
    int year, seats;
    double capacity;
    int count = 0;

    while (count < arrSize &&
           file >> type >> constructor >> year >> seats >> capacity) {
        (*out_arr)[count].set_type(type);
        (*out_arr)[count].set_constructor(constructor);
        (*out_arr)[count].set_year(year);
        (*out_arr)[count].set_seats(seats);
        (*out_arr)[count].set_capacity(capacity);
        count++;
    }

    file.close();
    return count;
}

int create(int n, const char* filename) {
    Airplane* arr = new Airplane[n];

    cout << "Создание файла. Введите " << n << " записей:\n";

    for (int i = 0; i < n; i++) {
        String type, constructor;
        int year, seats;
        double capacity;

        cout << "\nЗапись " << i + 1 << ":\n";

        if (!read_string("Тип самолета: ", type) ||
            !read_string("Фамилия конструктора: ", constructor) ||
            !read_int("Год выпуска: ", year) ||
            !read_int("Количество кресел: ", seats) ||
            !read_double("Грузоподъемность (т): ", capacity)) {
            cout << "Ввод прерван\n";
            delete[] arr;
            return -1;
        }

        arr[i] = Airplane(type.get(), constructor.get(), year, seats, capacity);
    }

    int result = save_row(filename, arr, n);
    delete[] arr;
    return result;
}

int read(int n, const char* filename) {
    Airplane* arr = nullptr;

    int count = load_row(filename, &arr, n);
    if (count < 0) return -1;
    if (count == 0) {
        cout << "Нет данных для вывода\n";
        return 0;
    }

    print_header();
    for (int i = 0; i < count; i++)
        print_row(arr[i]);

    cout << "\nВыведено записей: " << count << "\n";

    delete[] arr;
    return 0;
}

int append(int n, const char* filename) {
    Airplane* oldArr = nullptr;
    int oldCount = load_row(filename, &oldArr, 10000);

    if (oldCount < 0) {
        cout << "Файл не найден, создаём новый\n";
        return create(n, filename);
    }

    int newCount = oldCount + n;
    Airplane* newArr = new Airplane[newCount];

    for (int i = 0; i < oldCount; i++)
        newArr[i] = oldArr[i];
    delete[] oldArr;

    cout << "Добавление " << n << " записей:\n";

    for (int i = oldCount; i < newCount; i++) {
        String type, constructor;
        int year, seats;
        double capacity;

        cout << "\nЗапись " << i + 1 << ":\n";

        if (!read_string("Тип самолета: ", type) ||
            !read_string("Фамилия конструктора: ", constructor) ||
            !read_int("Год выпуска: ", year) ||
            !read_int("Количество кресел: ", seats) ||
            !read_double("Грузоподъемность (т): ", capacity)) {
            cout << "Ввод прерван, изменения не сохранены\n";
            delete[] newArr;
            return -1;
        }

        newArr[i] = Airplane(type.get(), constructor.get(), year, seats, capacity);
    }

    int result = save_row(filename, newArr, newCount);
    delete[] newArr;

    if (result == 0)
        cout << "Добавлено " << n << " записей, всего: " << newCount << "\n";

    return result;
}

int edit(int index, const char* filename) {
    Airplane* arr = nullptr;
    int count = load_row(filename, &arr, 10000);

    if (count <= 0) {
        cout << "Файл пуст или не найден\n";
        return -1;
    }

    if (index < 1 || index > count) {
        cout << "Записи " << index << " не существует (всего: " << count << ")\n";
        delete[] arr;
        return -1;
    }

    cout << "\nРедактирование записи " << index << ".\nТекущие данные:\n";
    print_row(arr[index - 1]);

    String type, constructor;
    int year, seats;
    double capacity;

    cout << "\nНовые данные:\n";

    if (!read_string("Тип самолета: ", type) ||
        !read_string("Фамилия конструктора: ", constructor) ||
        !read_int("Год выпуска: ", year) ||
        !read_int("Количество кресел: ", seats) ||
        !read_double("Грузоподъемность (т): ", capacity)) {
        cout << "Ввод прерван, изменения не сохранены\n";
        delete[] arr;
        return -1;
    }

    arr[index - 1] = Airplane(type.get(), constructor.get(), year, seats, capacity);

    int result = save_row(filename, arr, count);
    delete[] arr;

    if (result == 0)
        cout << "Запись " << index << " обновлена\n";

    return result;
}
