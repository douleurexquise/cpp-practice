#pragma once
#include <vector>
#include <string>
#include "Client.h"
#include "Operation.h"
using namespace std;

class ClearingCenter {
private:
    vector<Client> clients;
    vector<Operation> currentSession;
    vector<Operation> history;
public:
    ClearingCenter();

    void addClient(const Client& c);
    Client* findClient(string id);
    void addOperation(string clientID, string type, int amount, string date);
    void endSession();
    void generateReport(string startDate, string endDate);
    void saveData();
    void loadData();

    const vector<Client>& getClients() const;
    const vector<Operation>& getHistory() const;
};
