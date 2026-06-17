#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "ClientDB.h"
#include "OrderDB.h"

void clearCin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printClients(const ClientDB& db) {
    std::vector<Client> clients = db.getAllClients();
    if (clients.empty()) {
        std::cout << "База клиентов пуста." << std::endl;
        return;
    }
    std::cout << "\n--- Список клиентов ---" << std::endl;
    for (size_t i = 0; i < clients.size(); ++i) {
        const Client& c = clients[i];
        std::cout << "ID: " << c.getId()
                  << " | Имя: " << c.getName()
                  << " | Email: " << c.getEmail() << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
}

void printOrders(const OrderDB& db) {
    std::vector<Order> orders = db.getAllOrders();
    if (orders.empty()) {
        std::cout << "База заказов пуста." << std::endl;
        return;
    }
    std::cout << "\n--- Список заказов ---" << std::endl;
    for (size_t i = 0; i < orders.size(); ++i) {
        const Order& o = orders[i];
        std::string emergencyMark = o.getIsEmergency() ? "[СРОЧНО] " : "";
        std::string itemsStr;
        std::vector<std::string> items = o.getItems();

        for (size_t j = 0; j < items.size(); ++j) {
            itemsStr += items[j];
            if (j < items.size() - 1) {
                itemsStr += ", ";
            }
        }

        std::cout << "ID: " << o.getId()
                  << " | Клиент ID: " << o.getClientId()
                  << " | Дней назад: " << o.getDays()
                  << " | Статус: " << Order::statusToString(o.getStatus())
                  << " | " << emergencyMark << "Вещи: " << itemsStr << std::endl;
    }
    std::cout << "----------------------" << std::endl;
}

int main() {
    std::cout <<
    "**************************************************************************\n"
    "* Нижегородский государственный технический университет *\n"
    "* Курсовая работа по дисциплине \"Программирование\" *\n"
    "* Система управления заказами в химчистке  *\n"
    "* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович*\n"
    "**************************************************************************\n";
    ClientDB clientDb;
    OrderDB orderDb;
    int choice = 0;
    while (true) {
        std::cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ ЗАКАЗАМИ В ХИМЧИСТКЕ ===" << std::endl;
        std::cout << "1. Добавить клиента" << std::endl;
        std::cout << "2. Посмотреть клиентов" << std::endl;
        std::cout << "3. Создать заказ" << std::endl;
        std::cout << "4. Посмотреть заказы" << std::endl;
        std::cout << "5. Изменить статус заказа" << std::endl;
        std::cout << "6. Закрыть смену" << std::endl;
        std::cout << "7. Выход" << std::endl;
        std::cout << "Выберите действие: ";

        if (!(std::cin >> choice)) {
            std::cout << "Ошибка ввода. Введите число." << std::endl;
            clearCin();
            continue;
        }
        clearCin();

        switch (choice) {
            case 1: {
                std::string name, email;
                std::cout << "Введите имя клиента: ";
                std::getline(std::cin, name);
                std::cout << "Введите email: ";
                std::getline(std::cin, email);
                clientDb.addClient(name, email);
                std::cout << "Клиент успешно добавлен." << std::endl;
                break;
            }
            case 2:
                printClients(clientDb);
                break;
            case 3: {
                printClients(clientDb);
                int clientId = 0;
                std::cout << "Введите ID клиента для заказа: ";
                std::cin >> clientId;
                clearCin();

                if (!clientDb.clientExists(clientId)) {
                    std::cout << "Клиент не найден!" << std::endl;
                    break;
                }

                int days = 0;
                std::cout << "Сколько дней назад сдали вещи? ";
                std::cin >> days;
                clearCin();

                int emergency = 0;
                std::cout << "Заказ срочный? (1 - да, 0 - нет): ";
                std::cin >> emergency;
                clearCin();

                std::cout << "Доступные вещи: ";
                const std::vector<std::string>& catalog = Order::getCatalog();
                for (size_t i = 0; i < catalog.size(); ++i) {
                    std::cout << "[" << catalog[i] << "] ";
                }
                std::cout << std::endl;
                std::cout << "Вводите вещи по одной (для завершения введите 'стоп'):" << std::endl;

                std::vector<std::string> validItems;
                while (true) {
                    std::string input;
                    std::getline(std::cin, input);
                    if (input == "стоп") break;
                    if (input.empty()) continue;

                    if (Order::isValidItem(input)) {
                        validItems.push_back(input);
                        std::cout << "Добавлено: " << input << std::endl;
                    } else {
                        std::cout << "Вещи нет в каталоге. Попробуйте снова." << std::endl;
                    }
                }

                if (validItems.empty()) {
                    std::cout << "Заказ не создан: нет вещей." << std::endl;
                } else {
                    orderDb.addOrder(clientId, days, OrderStatus::Accepted, (emergency != 0), validItems);
                    std::cout << "Заказ успешно создан!" << std::endl;
                }
                break;
            }
            case 4:
                printOrders(orderDb);
                break;
            case 5: {
                printOrders(orderDb);
                int orderId = 0;
                std::cout << "Введите ID заказа для изменения статуса: ";
                std::cin >> orderId;
                clearCin();

                Order currentOrder = orderDb.getOrderById(orderId);
                if (currentOrder.getId() == 0) {
                    std::cout << "Заказ с таким ID не найден!" << std::endl;
                    break;
                }

                std::cout << "Текущий статус: " << Order::statusToString(currentOrder.getStatus()) << std::endl;
                std::cout << "Выберите новый статус:" << std::endl;
                std::cout << "1. Принят" << std::endl;
                std::cout << "2. В работе" << std::endl;
                std::cout << "3. Готов" << std::endl;
                std::cout << "4. Выдан" << std::endl;
                std::cout << "5. Отменён" << std::endl;
                std::cout << "Ваш выбор (1-5): ";

                int statusChoice = 0;
                std::cin >> statusChoice;
                clearCin();

                OrderStatus newStatus = OrderStatus::Accepted;
                bool validChoice = true;
                switch(statusChoice) {
                    case 1: newStatus = OrderStatus::Accepted; break;
                    case 2: newStatus = OrderStatus::InProgress; break;
                    case 3: newStatus = OrderStatus::Ready; break;
                    case 4: newStatus = OrderStatus::Issued; break;
                    case 5: newStatus = OrderStatus::Cancelled; break;
                    default: validChoice = false;
                }

                if (!validChoice) {
                    std::cout << "Неверный пункт меню." << std::endl;
                } else {
                    orderDb.updateOrderStatus(orderId, newStatus);
                    std::cout << "Статус заказа изменён на: " << Order::statusToString(newStatus) << std::endl;
                }
                break;
            }
            case 6:
                orderDb.closeShift();
                std::cout << "Смена закрыта." << std::endl;
                break;
            case 7:
                std::cout << "Выход из программы. Данные сохранены." << std::endl;
                return 0;
            default:
                std::cout << "Неверный пункт меню. Попробуйте снова." << std::endl;
        }
    }
}
