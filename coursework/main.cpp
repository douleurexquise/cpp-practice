#include <iostream>
#include <limits>
#include <string>
#include "ClearingCenter.h"
using namespace std;

static int readInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка: введите целое число.\n";
    }
}

static int readPositiveInt(const string& prompt) {
    while (true) {
        int val = readInt(prompt);
        if (val > 0) return val;
        cout << "Ошибка: значение должно быть больше 0.\n";
    }
}

static string readString(const string& prompt) {
    string s;
    cout << prompt;
    cin >> s;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return s;
}

int main() {
    ClearingCenter center;
    center.loadData();

    int choice = 0;
    while (true) {
        cout << "\n=== КЛИРИНГОВЫЙ ЦЕНТР ===\n"
             << "1. Добавить клиента\n"
             << "2. Добавить операцию\n"
             << "3. Завершить сессию\n"
             << "4. Отчёт за период\n"
             << "5. Выход\n"
             << "Выбор: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string id   = readString("ID счёта: ");
            string name = readString("Название фирмы: ");
            string addr = readString("Адрес: ");
            Client c(id, name, addr);

            int bankCount = readInt("Кол-во банковских счетов: ");
            for (int i = 0; i < bankCount; ++i)
                c.addBankID(readString("Счёт " + to_string(i + 1) + ": "));

            int assetCount = readInt("Кол-во активов: ");
            for (int i = 0; i < assetCount; ++i) {
                string n = readString("Название актива: ");
                int v    = readPositiveInt("Залоговая стоимость: ");
                c.addAsset(n, v);
            }

            center.addClient(c);
        }
        else if (choice == 2) {
            string id   = readString("ID клиента: ");
            string type = readString("Тип (IN/OUT): ");
            int amount  = readPositiveInt("Сумма: ");
            string date = readString("Дата (DD.MM.YYYY): ");
            center.addOperation(id, type, amount, date);
        }
        else if (choice == 3) {
            center.endSession();
        }
        else if (choice == 4) {
            string start = readString("Начало периода (DD.MM.YYYY): ");
            string end   = readString("Конец периода  (DD.MM.YYYY): ");
            center.generateReport(start, end);
        }
        else if (choice == 5) {
            cout << "Сохранение...\n";
            center.saveData();
            break;
        }
    }
    return 0;
}
