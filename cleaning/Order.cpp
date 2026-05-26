#include "Order.h"
#include <sstream>
#include <algorithm>
#include <cctype>

// Каталог допустимых вещей
static const std::vector<std::string> CATALOG = {
    "Куртка", "Пальто", "Брюки", "Рубашка", "Платье", "Обувь", "Аксессуар"
};

const std::vector<std::string>& Order::getCatalog() {
    return CATALOG;
}

bool Order::isValidItem(const std::string& item) {
    // Приводим ввод к нижнему регистру для нечувствительного сравнения
    std::string lowerItem = item;
    for (size_t k = 0; k < lowerItem.length(); ++k) {
        lowerItem[k] = std::tolower(static_cast<unsigned char>(lowerItem[k]));
    }

    for (size_t i = 0; i < CATALOG.size(); ++i) {
        std::string lowerCat = CATALOG[i];
        for (size_t k = 0; k < lowerCat.length(); ++k) {
            lowerCat[k] = std::tolower(static_cast<unsigned char>(lowerCat[k]));
        }
        if (lowerItem == lowerCat) {
            return true;
        }
    }
    return false;
}

std::string Order::statusToString(OrderStatus status) {
    switch(status) {
        case OrderStatus::Accepted:   return "Принят";
        case OrderStatus::InProgress: return "В работе";
        case OrderStatus::Ready:      return "Готов";
        case OrderStatus::Issued:     return "Выдан";
        case OrderStatus::Cancelled:  return "Отменён";
        default: return "Неизвестно";
    }
}

OrderStatus Order::statusFromString(const std::string& str) {
    if (str == "Принят")    return OrderStatus::Accepted;
    if (str == "В работе")  return OrderStatus::InProgress;
    if (str == "Готов")     return OrderStatus::Ready;
    if (str == "Выдан")     return OrderStatus::Issued;
    if (str == "Отменён")   return OrderStatus::Cancelled;
    return OrderStatus::Accepted;
}

Order::Order()
    : id(0), clientId(0), days(0), status(OrderStatus::Accepted), isEmergency(false) {}

Order::Order(int id, int clientId, int days, OrderStatus status, bool isEmergency, const std::vector<std::string>& items)
    : id(id), clientId(clientId), days(days), status(status), isEmergency(isEmergency), items(items) {}

// Геттеры
int Order::getId() const { return id; }
int Order::getClientId() const { return clientId; }
int Order::getDays() const { return days; }
OrderStatus Order::getStatus() const { return status; }
bool Order::getIsEmergency() const { return isEmergency; }
std::vector<std::string> Order::getItems() const { return items; }

// Сеттеры
void Order::setId(int id) { this->id = id; }
void Order::setClientId(int id) { this->clientId = id; }
void Order::setDays(int days) { this->days = days; }
void Order::setStatus(OrderStatus status) { this->status = status; }
void Order::setIsEmergency(bool emergency) { this->isEmergency = emergency; }
void Order::setItems(const std::vector<std::string>& items) { this->items = items; }

// Сериализация: id;clientId;days;status;isEmergency(0/1);item1,item2
std::string Order::toString() const {
    std::ostringstream oss;
    oss << id << ";" << clientId << ";" << days << ";"
        << statusToString(status) << ";" << (isEmergency ? 1 : 0) << ";";

    for (size_t i = 0; i < items.size(); ++i) {
        oss << items[i];
        if (i < items.size() - 1) {
            oss << ",";
        }
    }
    return oss.str();
}

Order Order::fromString(const std::string& line) {
    std::istringstream iss(line);
    std::string token;

    int id = 0, clientId = 0, days = 0, emergencyInt = 0;
    std::string statusStr, itemsStr;

    std::getline(iss, token, ';'); id = std::stoi(token);
    std::getline(iss, token, ';'); clientId = std::stoi(token);
    std::getline(iss, token, ';'); days = std::stoi(token);
    std::getline(iss, statusStr, ';');
    std::getline(iss, token, ';'); emergencyInt = std::stoi(token);
    std::getline(iss, itemsStr);

    OrderStatus status = statusFromString(statusStr);
    bool isEmergency = (emergencyInt != 0);

    std::vector<std::string> items;
    if (!itemsStr.empty()) {
        std::istringstream itemsStream(itemsStr);
        std::string item;
        while (std::getline(itemsStream, item, ',')) {
            items.push_back(item);
        }
    }

    return Order(id, clientId, days, status, isEmergency, items);
}
