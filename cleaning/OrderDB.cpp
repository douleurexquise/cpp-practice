#include "OrderDB.h"
#include <fstream>
#include <iostream>
#include <algorithm>

OrderDB::OrderDB() : filename("orders.txt"), nextId(1) {
    loadFromFile();
}

OrderDB::~OrderDB() {
    saveToFile();
}

void OrderDB::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        orders.push_back(Order::fromString(line));
        int curId = orders.back().getId();
        if (curId >= nextId) nextId = curId + 1;
    }
    file.close();
}

void OrderDB::saveToFile() {
    std::ofstream file(filename, std::ios::trunc);
    for (size_t i = 0; i < orders.size(); ++i) {
        file << orders[i].toString() << "\n";
    }
    file.close();
}

void OrderDB::addOrder(int clientId, int days, OrderStatus status, bool isEmergency, const std::vector<std::string>& items) {
    orders.emplace_back(nextId, clientId, days, status, isEmergency, items);
    nextId++;
    saveToFile();
}

bool OrderDB::removeOrder(int id) {
    for (size_t i = 0; i < orders.size(); ++i) {
        if (orders[i].getId() == id) {
            orders.erase(orders.begin() + static_cast<std::ptrdiff_t>(i));
            saveToFile();
            return true;
        }
    }
    return false;
}

bool OrderDB::updateOrder(int id, int days, OrderStatus status, bool isEmergency, const std::vector<std::string>& items) {
    for (size_t i = 0; i < orders.size(); ++i) {
        if (orders[i].getId() == id) {
            orders[i].setDays(days);
            orders[i].setStatus(status);
            orders[i].setIsEmergency(isEmergency);
            orders[i].setItems(items);
            saveToFile();
            return true;
        }
    }
    return false;
}

bool OrderDB::updateOrderStatus(int id, OrderStatus newStatus) {
    for (size_t i = 0; i < orders.size(); ++i) {
        if (orders[i].getId() == id) {
            orders[i].setStatus(newStatus);
            saveToFile();
            return true;
        }
    }
    return false;
}

Order OrderDB::getOrderById(int id) const {
    for (size_t i = 0; i < orders.size(); ++i) {
        if (orders[i].getId() == id) {
            return orders[i];
        }
    }
    return Order();
}

std::vector<Order> OrderDB::getAllOrders() const {
    return orders;
}

std::vector<Order> OrderDB::getOrdersByClientId(int clientId) const {
    std::vector<Order> result;
    for (size_t i = 0; i < orders.size(); ++i) {
        if (orders[i].getClientId() == clientId) {
            result.push_back(orders[i]);
        }
    }
    return result;
}
void OrderDB::closeShift(){
    size_t i = 0;
    while (i < orders.size()) {
        if (orders[i].getStatus() == OrderStatus::Cancelled) {
            orders.erase(orders.begin() + static_cast<std::ptrdiff_t>(i));
        } else {
            orders[i].setDays(orders[i].getDays() + 1);
            ++i;
        }
    }
    saveToFile();
}
