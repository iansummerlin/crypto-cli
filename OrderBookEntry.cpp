#include <iostream>
#include <string>
#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(
    double price,
    double amount,
    string timestamp,
    string product,
    OrderBookType orderType,
    string username)
    : price(price),
      amount(amount),
      timestamp(timestamp),
      product(product),
      orderType(orderType),
      username(username)
{
}

double OrderBookEntry::getPrice() const
{
    return price;
}

double OrderBookEntry::getAmount() const
{
    return amount;
}

void OrderBookEntry::setAmount(double amount)
{
    this->amount = amount;
}

string OrderBookEntry::getTimestamp() const
{
    return timestamp;
}

string OrderBookEntry::getProduct() const
{
    return product;
}

OrderBookType OrderBookEntry::getOrderType() const
{
    return orderType;
}

void OrderBookEntry::setOrderType(OrderBookType orderType)
{
    this->orderType = orderType;
}

string OrderBookEntry::getUsername() const
{
    return username;
}

void OrderBookEntry::setUsername(string username)
{
    this->username = username;
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

bool OrderBookEntry::compareByTimestamp(OrderBookEntry &a, OrderBookEntry &b)
{
    return a.getTimestamp() < b.getTimestamp();
}

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry &a, OrderBookEntry &b)
{
    return a.getPrice() < b.getPrice();
}

bool OrderBookEntry::compareByPriceDesc(OrderBookEntry &a, OrderBookEntry &b)
{
    return a.getPrice() > b.getPrice();
}