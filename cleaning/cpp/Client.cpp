#include "Client.h"
#include <sstream>

Client::Client() : id(0) {}
Client::Client(int id, const std::string& name, const std::string& email)
    :id(id), name(name), email(email){}
int Client::getId() const {
    return id;}
std::string Client::getName() const {
    return name;}
std::string Client::getEmail() const {
    return email;}

void Client::setId(int id) {
    this->id = id;}
void Client::setName(const std::string& name) {
    this->name = name;}
void Client::setEmail(const std::string& email) {
    this->email = email;}

std::string Client::toString() const {
    std::ostringstream ost; // поток вывода в строку
    ost << id << ";" << name << ";" << email;
    return ost.str();
}

Client Client::fromString(const std::string& line) {
    std::istringstream ist(line);
    int id = 0;
    std::string name, email, token;
    if (std::getline(ist, token, ';')) {
        id = std::stoi(token);}
    if (std::getline(ist, name, ';')) {}
    if (std::getline(ist, email)) {}

    return Client(id, name, email);
}
