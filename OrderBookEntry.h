#pragma once

#include <string>

using namespace std;

enum class OrderBookType
{
	ask,
	bid,
	asksale,
	bidsale,
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
		OrderBookType orderType,
		string username = "dataset");
	double getPrice() const;
	double getAmount() const;
	void setAmount(double amount);
	string getTimestamp() const;
	string getProduct() const;
	OrderBookType getOrderType() const;
	void setOrderType(OrderBookType orderType);
	string getUsername() const;
	void setUsername(string username);
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
	string username;
};
