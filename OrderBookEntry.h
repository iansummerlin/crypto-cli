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
	double getPrice();
	double getAmount();
	string getTimestamp();
	string getProduct();
	OrderBookType getOrderType();
	static OrderBookType stringToOrderBookType(string s);

private:
	double price;
	double amount;
	string timestamp;
	string product;
	OrderBookType orderType;
};