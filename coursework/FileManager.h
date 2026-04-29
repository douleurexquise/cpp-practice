#pragma once
#include <string>
#include <vector>
#include "Client.h"
#include "Operation.h"
using namespace std;

class FileManager {
public:
    static void saveClients(const vector<Client>& clients, string filename);
    static vector<Client> loadClients(string filename);
    static void saveOperations(const vector<Operation>& ops, string filename);
    static vector<Operation> loadOperations(string filename);
};
