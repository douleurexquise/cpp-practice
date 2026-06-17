#include "ClientDB.h"
#include <fstream>
#include <iostream>
#include <algorithm>

ClientDB::ClientDB() : filename("clients.txt"), nextId(1) {
    loadFromFile();
}

ClientDB::~ClientDB() {
    saveToFile();
}

void ClientDB::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        clients.push_back(Client::fromString(line));
        int curId = clients.back().getId();
        if (curId >= nextId) nextId = curId + 1;
    }
    file.close();
}

void ClientDB::saveToFile() {
    std::ofstream file(filename, std::ios::trunc);
    for (size_t i = 0; i < clients.size(); ++i) {
        file << clients[i].toString() << "\n";
    }
    file.close();
}

void ClientDB::addClient(const std::string& name, const std::string& email) {
    clients.emplace_back(nextId, name, email);
    nextId++;
    saveToFile();
}

bool ClientDB::updateClient(int id, const std::string& name, const std::string& email) {
    for (size_t i = 0; i < clients.size(); ++i) {
        if (clients[i].getId() == id) {
            clients[i].setName(name);
            clients[i].setEmail(email);
            saveToFile();
            return true;
        }
    }
    return false;
}

Client ClientDB::getClientById(int id) const {
    for (size_t i = 0; i < clients.size(); ++i) {
        if (clients[i].getId() == id) {
            return clients[i];
        }
    }
    return Client();
}

std::vector<Client> ClientDB::getAllClients() const {
    return clients;
}

bool ClientDB::clientExists(int id) const {
    return getClientById(id).getId() != 0;
}
