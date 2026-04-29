#include "Client.h"
#include <iostream>

Client::Client() {
    clearingID = "";
    firmName = "";
    address = "";
    balance = 0;
}

Client::Client(string clearingID, string firmName, string address) {
    this->clearingID = clearingID;
    this->firmName = firmName;
    this->address = address;
    balance = 0;
}

void Client::addBankID(string ID) {
    bankID.push_back(ID);
}

void Client::addAsset(string name, int value) {
    assets.push_back(name);
    assetsValues.push_back(value);
}

void Client::resetBalance() {
    balance = 0;
}

void Client::changeBalance(int diff) {
    balance += diff;
}

bool Client::deficit() {
    int total = balance + totalPledgeValue();
    return total < 0;
}

int Client::totalPledgeValue() {
    int sum = 0;
    for (int val : assetsValues) {
        sum += val;
    }
    return sum;
}

string Client::getClearingId() {
    return clearingID;
}

string Client::getFirmName() {
    return firmName;
}

string Client::getAddress() {
    return address;
}

int Client::getBalance() {
    return balance;
}
