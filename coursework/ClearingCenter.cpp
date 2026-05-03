#include "ClearingCenter.h"
#include <iostream>
#include <iomanip>
#include <fstream> // Работа с файлами теперь здесь
using namespace std;

ClearingCenter::ClearingCenter() {}

void ClearingCenter::addClient(const Client& c) {
    if (findClient(c.getClearingId())) {
        cout << "[!] Ошибка: клиент " << c.getClearingId() << " уже существует.\n";
        return;
    }
    clients.push_back(c);
    cout << "[+] Клиент добавлен: " << c.getFirmName() << "\n";
}

Client* ClearingCenter::findClient(string id) {
    for (auto& c : clients) {
        if (c.getClearingId() == id) return &c;
    }
    return nullptr;
}

// ─────────── ОПЕРАЦИИ ───────────
void ClearingCenter::addOperation(string clientID, string type, int amount, string date) {
    if (!findClient(clientID)) {
        cout << "[!] Ошибка: клиент " << clientID << " не найден.\n";
        return;
    }
    if (amount <= 0) {
        cout << "[!] Ошибка: сумма операции должна быть > 0.\n";
        return;
    }

    // Операция падает в очередь текущей сессии и в общий архив
    Operation op(clientID, type, amount, date);
    currentSession.push_back(op);
    history.push_back(op);
    cout << "[+] Операция принята: " << type << " | " << amount << " | " << date << "\n";
}

// ─────────── РАСЧЁТ СЕССИИ ───────────
void ClearingCenter::endSession() {
    cout << "\n🔍 === ЗАВЕРШЕНИЕ СУТОЧНОЙ СЕССИИ ===\n";
    if (currentSession.empty()) {
        cout << "Нет новых операций. Сессия пропущена.\n\n";
        return;
    }

    // 1. Применяем накопленные операции к финансовым балансам
    for (const auto& op : currentSession) {
        Client* c = findClient(op.getClientID());
        if (c) {
            if (op.getType() == "IN")  c->changeBalance(op.getAmount());
            if (op.getType() == "OUT") c->changeBalance(-op.getAmount());
        }
    }

    // 2. Выводим итоги и проверяем на дефицит
    cout << "\n📊 ИТОГИ ПО СЧЕТАМ:\n";
    for (const auto& c : clients) {
        int total = c.getBalance() + c.totalPledgeValue();
        cout << "• " << c.getFirmName()
             << " | Финансы: " << c.getBalance()
             << " | Залог: " << c.totalPledgeValue()
             << " | Итого: " << total << "\n";

        if (c.deficit()) {
            cout << "  ⚠️ ПРЕДПИСАНИЕ: Дефицит " << (-total) << ". Требуется срочное пополнение!\n";
        }
    }

    // 3. Очищаем очередь, сохраняем состояние, готовимся к новому дню
    currentSession.clear();
    saveData();
    cout << "\n✅ Сессия закрыта. Данные сохранены.\n";
}

// ─────────── ОТЧЁТЫ ───────────
void ClearingCenter::generateReport(string startDate, string endDate) {
    cout << "\n📄 ОТЧЁТ ЗА ПЕРИОД: " << startDate << " — " << endDate << "\n";
    cout << left << setw(12) << "Счёт" << setw(6) << "Тип" << setw(8) << "Сумма" << setw(12) << "Дата" << "\n";
    cout << string(38, '-') << "\n";

    int found = 0;
    for (const auto& op : history) {
        // Строковое сравнение работает корректно для формата DD.MM.YYYY
        if (op.getDate() >= startDate && op.getDate() <= endDate) {
            cout << left << setw(12) << op.getClientID()
                 << setw(6) << op.getType()
                 << setw(8) << op.getAmount()
                 << setw(12) << op.getDate() << "\n";
            found++;
        }
    }
    if (found == 0) cout << "Операций за указанный период не найдено.\n";
    cout << "\n";
}

// ─────────── ФАЙЛОВЫЙ ВВОД/ВЫВОД ───────────
void ClearingCenter::saveData() {
    // Сохраняем клиентов
    ofstream outClients("clients.csv");
    if (outClients.is_open()) {
        for (const auto& c : clients) outClients << c.toCSV() << "\n";
        outClients.close();
    } else {
        cerr << "[!] Не удалось открыть clients.csv для записи.\n";
    }

    // Сохраняем историю операций
    ofstream outOps("operations.csv");
    if (outOps.is_open()) {
        for (const auto& op : history) outOps << op.toCSV() << "\n";
        outOps.close();
    } else {
        cerr << "[!] Не удалось открыть operations.csv для записи.\n";
    }
}

void ClearingCenter::loadData() {
    // Загружаем клиентов
    ifstream inClients("clients.csv");
    if (inClients.is_open()) {
        string line;
        while (getline(inClients, line)) {
            if (!line.empty()) clients.push_back(Client::fromCSV(line));
        }
        inClients.close();
    }

    // Загружаем историю операций
    ifstream inOps("operations.csv");
    if (inOps.is_open()) {
        string line;
        while (getline(inOps, line)) {
            if (!line.empty()) history.push_back(Operation::fromCSV(line));
        }
        inOps.close();
    }
}

const vector<Client>& ClearingCenter::getClients() const { return clients; }
const vector<Operation>& ClearingCenter::getHistory() const { return history; }
