#include <iostream>
#include <limits>
#include "ClearingCenter.h"
using namespace std;

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    ClearingCenter center;
    center.loadData(); // Загружаем прошлые сессии, если файлы есть

    int choice = 0;
    while(true){
        cout << "\n=== КЛИРИНГОВЫЙ ЦЕНТР ===\n";
        cout << "1. Добавить клиента\n";
        cout << "2. Добавить операцию\n";
        cout << "3. Завершить сессию (расчёт + предписания)\n";
        cout << "4. Отчёт за период\n";
        cout << "5. Выход\n";
        cout << "Выбор: ";
        if(!(cin >> choice)){ cin.clear(); cin.ignore(10000, '\n'); continue; }

        if(choice == 1){
            string id, name, addr; int bankCount;
            cout << "ID счёта: "; cin >> id;
            cout << "Название фирмы: "; cin >> name;
            cout << "Адрес: "; cin >> addr;
            Client c(id, name, addr);
            cout << "Кол-во банковских счетов: "; cin >> bankCount;
            for(int i=0; i<bankCount; ++i){ string b; cout << "Счёт " << i+1 << ": "; cin >> b; c.addBankID(b); }
            cout << "Кол-во активов: "; cin >> bankCount;
            for(int i=0; i<bankCount; ++i){ string n; int v; cout << "Название: "; cin >> n; cout << "Залог: "; cin >> v; c.addAsset(n, v); }
            center.addClient(c);
        }
        else if(choice == 2){
            string id, type, date; int amount;
            cout << "ID клиента: "; cin >> id;
            cout << "Тип (IN/OUT): "; cin >> type;
            cout << "Сумма: "; cin >> amount;
            cout << "Дата (DD.MM.YYYY): "; cin >> date;
            center.addOperation(id, type, amount, date);
        }
        else if(choice == 3){
            center.endSession();
        }
        else if(choice == 4){
            string s, e;
            cout << "Начало периода: "; cin >> s;
            cout << "Конец периода: "; cin >> e;
            center.generateReport(s, e);
        }
        else if(choice == 5){
            cout << "Сохранение перед выходом...\n";
            center.saveData();
            break;
        }
    }
    return 0;
}
