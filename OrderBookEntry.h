#pragma once

#include <string>

using namespace std;

enum class OrderBookType
{
	ask,
	bid,
	sale,
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
	void setAmount(double amount);
	string getTimestamp() const;
	string getProduct() const;
	OrderBookType getOrderType() const;
	static OrderBookType stringToOrderBookType(string s);
	static bool compareByTimestamp(OrderBookEntry &a, OrderBookEntry &b);
	static bool compareByPriceAsc(OrderBookEntry &a, OrderBookEntry &b);
	static bool compareByPriceDesc(OrderBookEntry &a, OrderBookEntry &b);

private:
	double price;
	double amount;
	string timestamp;
	string product;
	OrderBookType orderType;
};
