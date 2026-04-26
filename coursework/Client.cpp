#include <Client.h>
#include <iostream>

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

