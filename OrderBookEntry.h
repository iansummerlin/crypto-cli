#pragma once

#include <string>

using namespace std;

enum class OrderBookType
{
	bid,
	ask,
	unknown
};

class OrderBookEntry
{

public:
	OrderBookEntry(
		double price,
		double amount,
		string timestamp,
		string product,
		OrderBookType orderType);
	double getPrice() const;
	double getAmount() const;
	string getTimestamp() const;
	string getProduct() const;
	OrderBookType getOrderType() const;
	static OrderBookType stringToOrderBookType(string s);
	static bool compareByTimestamp(OrderBookEntry &a, OrderBookEntry &b);

private:
	double price;
	double amount;
	string timestamp;
	string product;
	OrderBookType orderType;
};