#ifndef CLIENTDB_H
#define CLIENTDB_H

#include <vector>
#include <string>
#include "Client.h"

class ClientDB {
private:
    std::vector<Client> clients;
    std::string filename;
    int nextId; // автоматическая генерация ID

    void loadFromFile(); // Загружает данные при создании объекта
    void saveToFile();   // Сохраняет все изменения в файл

public:
    ClientDB();
    ~ClientDB();
    void addClient(const std::string& name, const std::string& email);
    bool removeClient(int id);
    bool updateClient(int id, const std::string& name, const std::string& email);
    bool clientExists(int id) const;
    Client getClientById(int id) const;
    std::vector<Client> getAllClients() const;
};
#endif
