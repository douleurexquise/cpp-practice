#include "Operation.h"
#include <sstream>
using namespace std;
//TODO: need to refactor
Operation::Operation() : amount(0) {}
Operation::Operation(string clientID, string type, int amount, string date)
    : clientID(clientID), type(type), amount(amount), date(date) {}

string Operation::toCSV() const {
    return clientID + ";" + type + ";" + to_string(amount) + ";" + date;
}

Operation Operation::fromCSV(string line) {
    stringstream ss(line);
    string token;
    vector<string> parts;
    while(getline(ss, token, ';')) parts.push_back(token);
    if(parts.size() == 4) return Operation(parts[0], parts[1], stoi(parts[2]), parts[3]);
    return Operation();
}

string Operation::getClientID() const { return clientID; }
string Operation::getType() const { return type; }
int Operation::getAmount() const { return amount; }
string Operation::getDate() const { return date; }
