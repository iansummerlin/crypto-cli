#pragma once

#include <string>
#include <map>
#include "OrderBookEntry.h"

using namespace std;

class Wallet
{
public:
    Wallet();
    string toString();
    void insertCurrency(string type, double amount);
    bool removeCurrency(string type, double amount);
    bool checkCurrencyAmount(string type, double amount) const;
    bool canFulfillOrder(const OrderBookEntry &order) const;
    void processSale(OrderBookEntry &sale);

private:
    map<string, double> wallet;
};