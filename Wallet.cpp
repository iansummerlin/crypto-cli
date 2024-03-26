#include <iostream>
#include "Wallet.h"
#include "CSVReader.h"

using namespace std;

Wallet::Wallet()
{
    insertCurrency("BTC", 10);
    insertCurrency("USDT", 50000);
}

string Wallet::toString()
{
    string string = "";
    for (auto const &x : wallet)
    {
        string += x.first + ": " + to_string(x.second) + "\n";
    }

    return string;
}

void Wallet::insertCurrency(string type, double amount)
{
    if (amount < 0)
    {
        cout << "Cannot insert negative amount" << endl;
        throw exception();
    }
    if (wallet.find(type) == wallet.end())
    {
        wallet[type] = amount;
    }
    else
    {
        wallet[type] += amount;
    }
}

bool Wallet::removeCurrency(string type, double amount)
{
    if (amount < 0)
    {
        cout << "Cannot remove negative amount" << endl;
        throw exception();
    }
    if (wallet.find(type) == wallet.end())
    {
        return false;
    }
    if (checkCurrencyAmount(type, amount) == false)
    {
        return false;
    }

    wallet[type] -= amount;

    return true;
}

bool Wallet::checkCurrencyAmount(string type, double amount) const
{
    if (wallet.find(type)->second < amount)
    {
        return false;
    }

    return true;
}

bool Wallet::canFulfillOrder(const OrderBookEntry &order) const
{
    vector<string> currencyPairs = CSVReader::tokenise(order.getProduct(), '/');
    if (currencyPairs.size() != 2)
    {
        cout << "Invalid currency pair" << endl;
        return false;
    }
    if (order.getOrderType() == OrderBookType::ask)
    {
        double amount = order.getAmount();
        string currency = currencyPairs[0];

        return checkCurrencyAmount(currency, amount);
    }
    if (order.getOrderType() == OrderBookType::bid)
    {
        double amount = order.getAmount() * order.getPrice();
        string currency = currencyPairs[1];

        return checkCurrencyAmount(currency, amount);
    }

    return false;
}

void Wallet::processSale(OrderBookEntry &sale)
{
    cout << "Processing sale..." << endl;
    vector<string> currencyPairs = CSVReader::tokenise(sale.getProduct(), '/');
    if (currencyPairs.size() != 2)
    {
        cout << "Invalid currency pair" << endl;
        throw exception();
    }

    if (sale.getOrderType() == OrderBookType::asksale)
    {
        double outgoingAmount = sale.getAmount();
        string outgoingCurrency = currencyPairs[0];
        double incomingAmount = sale.getAmount() * sale.getPrice();
        string incomingCurrency = currencyPairs[1];

        wallet[incomingCurrency] += incomingAmount;
        wallet[outgoingCurrency] -= outgoingAmount;
    }
    else if (sale.getOrderType() == OrderBookType::bidsale)
    {
        double outgoingAmount = sale.getAmount() * sale.getPrice();
        string outgoingCurrency = currencyPairs[1];
        double incomingAmount = sale.getAmount();
        string incomingCurrency = currencyPairs[0];

        wallet[incomingCurrency] += incomingAmount;
        wallet[outgoingCurrency] -= outgoingAmount;
    }
}
