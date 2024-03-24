#include <iostream>
#include <string>
#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(
    double price,
    double amount,
    string timestamp,
    string product,
    OrderBookType orderType)
    : price(price),
      amount(amount),
      timestamp(timestamp),
      product(product),
      orderType(orderType) {}

double OrderBookEntry::getPrice()
{
    return price;
}

double OrderBookEntry::getAmount()
{
    return amount;
}

string OrderBookEntry::getTimestamp()
{
    return timestamp;
}

string OrderBookEntry::getProduct()
{
    return product;
}

OrderBookType OrderBookEntry::getOrderType()
{
    return orderType;
}

OrderBookType OrderBookEntry::stringToOrderBookType(string s)
{
    if (s == "bid")
    {
        return OrderBookType::bid;
    }
    if (s == "ask")
    {
        return OrderBookType::ask;
    }

    return OrderBookType::unknown;
}