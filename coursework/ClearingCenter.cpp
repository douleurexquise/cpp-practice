#include "ClearingCenter.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

ClearingCenter::ClearingCenter() {}

// Преобразует "DD.MM.YYYY" в целое YYYYMMDD для корректного сравнения дат
static int dateToInt(const string& date) {
    if (date.size() != 10) return 0;
    return stoi(date.substr(6, 4)) * 10000
         + stoi(date.substr(3, 2)) * 100
         + stoi(date.substr(0, 2));
}

void ClearingCenter::addClient(const Client& c) {
    if (findClient(c.getClearingId())) {
        cout << "Ошибка: клиент " << c.getClearingId() << " уже существует.\n";
        return;
    }
    clients.push_back(c);
    cout << "Клиент добавлен: " << c.getFirmName() << "\n";
}

Client* ClearingCenter::findClient(const string& id) {
    for (auto& c : clients) {
        if (c.getClearingId() == id) return &c;
    }
    return nullptr;
}

void ClearingCenter::addOperation(const string& clientID, const string& type, int amount, const string& date) {
    if (!findClient(clientID)) {
        cout << "Ошибка: клиент " << clientID << " не найден.\n";
        return;
    }
    if (type != "IN" && type != "OUT") {
        cout << "Ошибка: тип операции должен быть IN или OUT.\n";
        return;
    }
    if (amount <= 0) {
        cout << "Ошибка: сумма операции должна быть больше 0.\n";
        return;
    }

    Operation op(clientID, type, amount, date);
    currentSession.push_back(op);
    history.push_back(op);
    cout << "Операция принята: " << type << " | " << amount << " | " << date << "\n";
}

void ClearingCenter::endSession() {
    cout << "\n=== ЗАВЕРШЕНИЕ СУТОЧНОЙ СЕССИИ ===\n";
    if (currentSession.empty()) {
        cout << "Нет новых операций. Сессия пропущена.\n\n";
        return;
    }

    for (const Operation& op : currentSession) {
        Client* c = findClient(op.getClientID());
        if (!c) continue;
        if (op.getType() == "IN")  c->changeBalance(op.getAmount());
        if (op.getType() == "OUT") c->changeBalance(-op.getAmount());
    }

    cout << "\nИТОГИ ПО СЧЕТАМ:\n";
    for (const Client& c : clients) {
        int total = c.getBalance() + c.totalPledgeValue();
        cout << "  " << c.getFirmName()
             << " | Баланс: " << c.getBalance()
             << " | Залог: " << c.totalPledgeValue()
             << " | Итого: " << total << "\n";

        if (c.deficit()) {
            cout << "ПРЕДПИСАНИЕ: дефицит " << (-total) << ", требуется пополнение.\n";
        }
    }

    currentSession.clear();
    saveData();
    cout << "\nСессия закрыта. Данные сохранены.\n";
}

void ClearingCenter::generateReport(const string& startDate, const string& endDate) {
    int from = dateToInt(startDate);
    int to   = dateToInt(endDate);

    cout << "\nОТЧЁТ ЗА ПЕРИОД: " << startDate << " - " << endDate << "\n";
    cout << "Счёт\t   Тип\t Сумма\t\tДата\n";
    cout << string(40, '-') << "\n";

    int found = 0;
    for (const Operation& op : history) {
        int d = dateToInt(op.getDate());
        if (d >= from && d <= to) {
            cout << left << setw(12) << op.getClientID()
                         << setw(6)  << op.getType()
                         << setw(10) << op.getAmount()
                         << setw(12) << op.getDate() << "\n";
            found++;
        }
    }
    if (found == 0)
        cout << "Операций за указанный период не найдено.\n";
    cout << "\n";
}

void ClearingCenter::saveData() {
    ofstream outClients("clients");
    if (outClients.is_open()) {
        for (const Client& c : clients)
            outClients << c.toCSV() << "\n";
    } else {
        cerr << "Ошибка: не удалось открыть clients.csv для записи.\n";
    }

    ofstream outOps("operations");
    if (outOps.is_open()) {
        for (const auto& op : history)
            outOps << op.toCSV() << "\n";
    } else {
        cerr << "Ошибка: не удалось открыть operations.csv для записи.\n";
    }
}

void ClearingCenter::loadData() {
    ifstream inClients("clients.csv");
    if (inClients.is_open()) {
        string line;
        while (getline(inClients, line)) {
            if (!line.empty())
                clients.push_back(Client::fromCSV(line));
        }
    }

    ifstream inOps("operations.csv");
    if (inOps.is_open()) {
        string line;
        while (getline(inOps, line)) {
            if (!line.empty())
                history.push_back(Operation::fromCSV(line));
        }
    }
}

const vector<Client>&    ClearingCenter::getClients() const { return clients; }
const vector<Operation>& ClearingCenter::getHistory() const { return history; }
