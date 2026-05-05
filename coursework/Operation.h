#pragma once
#include <string>
#include <vector>
using namespace std;

class Operation {
private:
    string clientID;
    string type; // IN - пополнение, OUT - вывод
    int amount;
    string date;
public:
    Operation();
    Operation(string clientID, string type, int amount, string date);
    string toCSV() const;
    static Operation fromCSV(const string& line);
    string getClientID() const;
    string getType() const;
    int getAmount() const;
    string getDate() const;
};
