#include "ClearingCenter.h"
#include <iostream>
#include <iomanip>
using namespace std;

ClearingCenter::ClearingCenter() {}

void ClearingCenter::addClient(const Client& c){
    if(findClient(c.getClearingId())){
        cout << "[!] Клиент " << c.getClearingId() << " уже существует.\n"; return;
    }
    clients.push_back(c);
}
Client* ClearingCenter::findClient(string id){
    for(auto& c : clients) if(c.getClearingId() == id) return &c;
    return nullptr;
}

void ClearingCenter::addOperation(string clientID, string type, int amount, string date){
    if(!findClient(clientID)){ cout << "[!] Клиент не найден.\n"; return; }
    if(amount <= 0){ cout << "[!] Сумма должна быть > 0.\n"; return; }
    currentSession.push_back(Operation(clientID, type, amount, date));
    history.push_back(currentSession.back());
    cout << "[+] Операция добавлена: " << type << " " << amount << " для " << clientID << "\n";
}

void ClearingCenter::endSession(){
    cout << "\n=== ЗАКРЫТИЕ СУТОЧНОЙ СЕССИИ ===\n";
    if(currentSession.empty()){ cout << "Нет операций. Сессия пропущена.\n\n"; return; }

    // 1. Применяем операции к балансам
    for(const auto& op : currentSession){
        Client* c = findClient(op.getClientID());
        if(c){
            if(op.getType() == "IN") c->changeBalance(op.getAmount());
            else if(op.getType() == "OUT") c->changeBalance(-op.getAmount());
        }
    }

    // 2. Проверка дефицита
    cout << "📊 Итоги по клиентам:\n";
    for(const auto& c : clients){
        int total = c.getBalance() + c.totalPledgeValue();
        cout << "• " << c.getFirmName() << " | Баланс: " << c.getBalance()
             << " | Залог: " << c.totalPledgeValue() << " | Итого: " << total << "\n";
        if(c.deficit()){
            cout << "  ⚠️ ПРЕДПИСАНИЕ: Дефицит " << (-total) << ". Требуется пополнение счёта!\n";
        }
    }

    // 3. Очищаем текущую сессию, готовимся к новому дню
    currentSession.clear();
    cout << "✅ Сессия завершена. Данные сохранены.\n\n";
    saveData();
}

void ClearingCenter::generateReport(string startDate, string endDate){
    cout << "\n📄 ОТЧЁТ ЗА ПЕРИОД: " << startDate << " — " << endDate << "\n";
    int found = 0;
    for(const auto& op : history){
        // Простое строковое сравнение дат в формате DD.MM.YYYY работает, если формат одинаковый
        if(op.getDate() >= startDate && op.getDate() <= endDate){
            cout << left << setw(12) << op.getClientID() << setw(6) << op.getType()
                 << setw(8) << op.getAmount() << setw(12) << op.getDate() << "\n";
            found++;
        }
    }
    if(found == 0) cout << "Операций за указанный период не найдено.\n";
    cout << "\n";
}

void ClearingCenter::saveData(){
    FileManager::saveClients(clients, "clients.csv");
    FileManager::saveOperations(history, "operations.csv");
}
void ClearingCenter::loadData(){
    clients = FileManager::loadClients("clients.csv");
    history = FileManager::loadOperations("operations.csv");
}
const vector<Client>& ClearingCenter::getClients() const { return clients; }
const vector<Operation>& ClearingCenter::getHistory() const { return history; }
