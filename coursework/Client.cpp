#include "Client.h"
#include <sstream>
using namespace std;

Client::Client(){
    clearingID = "";
    firmName = "";
    address = "";
    balance = 0;
}
Client::Client(string clearingID, string firmName, string address){
    this->clearingID = clearingID;
    this->firmName = firmName;
    this->address = address;
    balance = 0;
}
void Client::addBankID(string ID){
    bankID.push_back(ID);
}
void Client::addAsset(string name, int value){
    assets.push_back(name);
    assetsValues.push_back(value);
}
void Client::resetBalance(){
    balance = 0;
}
void Client::changeBalance(int diff){
    balance += diff;
}
void Client::setBalance(int b){
    balance = b;
}

bool Client::deficit() const {
    return (balance + totalPledgeValue()) < 0;
}
int Client::totalPledgeValue() const {
    int sum = 0;
    for(int v : assetsValues) sum += v;
    return sum;
}
string Client::getClearingId() const {
    return clearingID;
}
string Client::getFirmName() const {
    return firmName;
}
string Client::getAddress() const {
    return address;
}
int Client::getBalance() const {
    return balance;
}

const vector<string>& Client::getBankIDs() const {
    return bankID;
}
const vector<string>& Client::getAssets() const {
    return assets;
}
const vector<int>& Client::getAssetValues() const {
    return assetsValues;
}

string Client::toCSV() const {
    string res = clearingID + "," + firmName + "," + address + "," + to_string(balance) + ",";
    for (size_t i = 0; i < bankID.size(); ++i) {
        res += bankID[i];
        if (i + 1 < bankID.size()) res += "|";
    }
    res += ",";
    for (size_t i = 0; i < assets.size(); ++i) {
        res += assets[i];
        if (i + 1 < assets.size()) res += "|";
    }
    res += ",";
    for (size_t i = 0; i < assetsValues.size(); ++i) {
        res += to_string(assetsValues[i]);
        if (i + 1 < assetsValues.size()) res += "|";
    }
    return res;
}

Client Client::fromCSV(string line) {
    vector<string> parts;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        parts.push_back(token);
    }
    if (parts.size() != 7) {
        return Client();
    }
    Client client(parts[0], parts[1], parts[2]);
    client.setBalance(stoi(parts[3]));
    stringstream ssBank(parts[4]);
    string item;
    while (getline(ssBank, item, '|')) {
        client.addBankID(item);
    }
    vector<string> assetNames;
    stringstream ssAssets(parts[5]);
    while (getline(ssAssets, item, '|')) {
        assetNames.push_back(item);
    }
    vector<int> assetVals;
    stringstream ssVals(parts[6]);
    while (getline(ssVals, item, '|')) {
        assetVals.push_back(stoi(item));
    }
    for (size_t i = 0; i < assetNames.size() && i < assetVals.size(); ++i) {
        client.addAsset(assetNames[i], assetVals[i]);
    }
    return client;
}
