#include "FileManager.h"
#include <fstream>
#include <iostream>
using namespace std;

void FileManager::saveClients(const vector<Client>& clients, string filename){
    ofstream out(filename);
    for(const auto& c : clients) out << c.toCSV() << "\n";
    out.close();
}
vector<Client> FileManager::loadClients(string filename){
    vector<Client> res; ifstream in(filename); string line;
    if(!in.is_open()) return res;
    while(getline(in, line)){
        if(line.size() > 0) res.push_back(Client::fromCSV(line));
    }
    in.close(); return res;
}

void FileManager::saveOperations(const vector<Operation>& ops, string filename){
    ofstream out(filename);
    for(const auto& op : ops) out << op.toCSV() << "\n";
    out.close();
}
vector<Operation> FileManager::loadOperations(string filename){
    vector<Operation> res; ifstream in(filename); string line;
    if(!in.is_open()) return res;
    while(getline(in, line)){
        if(line.size() > 0) res.push_back(Operation::fromCSV(line));
    }
    in.close(); return res;
}
