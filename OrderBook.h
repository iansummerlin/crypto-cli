#pragma once
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"

using namespace std;

class OrderBook
{
public:
	OrderBook(string filename);
	vector<string> getKnownProducts();
	vector<OrderBookEntry> getOrders(
		OrderBookType type,
		string product,
		string timestamp);
	vector<OrderBookEntry> getOrdersForTimePeriod(
		OrderBookType type,
		string product,
		string startTime,
		string endTime);
	string getEarliestTime();
	string getNextTime(string timestamp);
	void insertOrder(OrderBookEntry &order);
	vector<OrderBookEntry> matchAsksToBids(string product, string timestamp);
	static double getHighPrice(vector<OrderBookEntry> &orders);
	static double getLowPrice(vector<OrderBookEntry> &orders);
	static double getPriceSpread(vector<OrderBookEntry> &orders);
	static double getPriceSpread(double min, double max);
	static double getVolume(vector<OrderBookEntry> &orders);

private:
	vector<OrderBookEntry> orders;
};
