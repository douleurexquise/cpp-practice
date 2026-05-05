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
    Client* findClient(const string& id);

    void addOperation(const string& clientID, const string& type, int amount, const string& date);
    void endSession();
    void generateReport(const string& startDate, const string& endDate);

    void saveData();
    void loadData();

    const vector<Client>& getClients() const;
    const vector<Operation>& getHistory() const;
};
