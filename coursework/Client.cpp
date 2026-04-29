#include "Client.h"
#include <iostream>
#include <sstream>
using namespace std;

Client::Client(){
    clearingID = ""; firmName = ""; address = ""; balance = 0;
}
Client::Client(string clearingID, string firmName, string address){
    this->clearingID = clearingID; this->firmName = firmName; this->address = address;
    balance = 0;
}
void Client::addBankID(string ID){ bankID.push_back(ID); }
void Client::addAsset(string name, int value){ assets.push_back(name); assetsValues.push_back(value); }
void Client::resetBalance(){ balance = 0; }
void Client::changeBalance(int diff){ balance += diff; }
bool Client::deficit(){ return (balance + totalPledgeValue()) < 0; }
int Client::totalPledgeValue(){
    int sum = 0; for(int v : assetsValues) sum += v; return sum;
}
string Client::getClearingId(){ return clearingID; }
string Client::getFirmName(){ return firmName; }
string Client::getAddress(){ return address; }
int Client::getBalance(){ return balance; }
void Client::setBalance(int b){ balance = b; }
const vector<string>& Client::getBankIDs() const { return bankID; }
const vector<string>& Client::getAssets() const { return assets; }
const vector<int>& Client::getAssetValues() const { return assetsValues; }

string Client::toCSV() const {
    // Формат: ID,Name,Address,Balance,Банки(через |),Активы(через |),Залоги(через |)
    string banks="", ast="", val="";
    for(size_t i=0; i<bankID.size(); ++i) banks += bankID[i] + (i==bankID.size()-1?"":"|");
    for(size_t i=0; i<assets.size(); ++i) ast += assets[i] + (i==assets.size()-1?"":"|");
    for(size_t i=0; i<assetsValues.size(); ++i) val += to_string(assetsValues[i]) + (i==assetsValues.size()-1?"":"|");
    return clearingID + "," + firmName + "," + address + "," + to_string(balance) + "," + banks + "," + ast + "," + val;
}

Client Client::fromCSV(string line){
    stringstream ss(line); string token;
    vector<string> parts;
    while(getline(ss, token, ',')) parts.push_back(token);
    if(parts.size() != 7) return Client();

    Client c(parts[0], parts[1], parts[2]);
    c.setBalance(stoi(parts[3]));

    // Парсим разделённые '|' поля
    auto split = [](string s, char delim){
        vector<string> res; stringstream ss(s); string t;
        while(getline(ss, t, delim)) res.push_back(t);
        return res;
    };
    vector<string> b = split(parts[4], '|');
    vector<string> a = split(parts[5], '|');
    vector<string> v = split(parts[6], '|');

    for(auto& id : b) c.addBankID(id);
    for(size_t i=0; i<a.size() && i<v.size(); ++i) c.addAsset(a[i], stoi(v[i]));
    return c;
}
