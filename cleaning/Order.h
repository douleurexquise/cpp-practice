#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>

enum class OrderStatus { // статусы заказа
    Accepted,
    InProgress,
    Ready,
    Issued,
    Cancelled
};

class Order {
private:
    int id;
    int clientId;
    int days;// сколько дней назад сдали вещь
    OrderStatus status;
    bool isEmergency;// срочно/нет
    std::vector<std::string> items; // список вещей

public:
    Order();
    Order(int id, int clientId, int days, OrderStatus status, bool isEmergency, const std::vector<std::string>& items);

    int getId() const;
    int getClientId() const;
    int getDays() const;
    OrderStatus getStatus() const;
    bool getIsEmergency() const;
    std::vector<std::string> getItems() const;
    void setId(int id);
    void setClientId(int id);
    void setDays(int days);
    void setStatus(OrderStatus status);
    void setIsEmergency(bool urgent);
    void setItems(const std::vector<std::string>& items);
    static const std::vector<std::string>& getCatalog();// возвращает ссылку на список допустимых вещей
    // это для защиты от "мусорного" ввода по типу "24фыв"
    static bool isValidItem(const std::string& item);
    static std::string statusToString(OrderStatus status);// ???????
    static OrderStatus statusFromString(const std::string& str);

    std::string toString() const;
    static Order fromString(const std::string& line);
};

#endif
