#ifndef ORDERDB_H
#define ORDERDB_H

#include <vector>
#include <string>
#include "Order.h"

class OrderDB {
private:
    std::vector<Order> orders;
    std::string filename;
    int nextId;

    void loadFromFile();
    void saveToFile();

public:
    OrderDB();
    ~OrderDB();
    void addOrder(int clientId, int daysAgo, OrderStatus status, bool isUrgent, const std::vector<std::string>& items);
    bool removeOrder(int id);
    bool updateOrder(int id, int daysAgo, OrderStatus status, bool isUrgent, const std::vector<std::string>& items);
    bool updateOrderStatus(int id, OrderStatus newStatus);
    Order getOrderById(int id) const;
    std::vector<Order> getAllOrders() const;
    std::vector<Order> getOrdersByClientId(int clientId) const;
    void closeShift();
};

#endif
