#pragma once
#include <string>
#include <vector>
using namespace std;

class Client{
private:
    string clearingID;
    string firmName;
    string address;
    int balance;
    vector<string> bankID;
    vector<string> assets;
    vector<int> assetsValues;
public:
    Client();
    Client(string clearingID, string firmName, string address);

    void addBankID(string ID);
    void addAsset(string name, int value);
    void resetBalance();
    void changeBalance(int diff);
    bool deficit();
    int totalPledgeValue();

    string getClearingId();
    string getFirmName();
    string getAddress();
    int getBalance();

    // Для сохранения/загрузки
    const vector<string>& getBankIDs() const;
    const vector<string>& getAssets() const;
    const vector<int>& getAssetValues() const;
    void setBalance(int b);
    string toCSV() const;
    static Client fromCSV(string line);
};
