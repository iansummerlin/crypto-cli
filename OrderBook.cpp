#include <iostream>
#include <map>
#include <algorithm>
#include "OrderBook.h"
#include "CSVReader.h"

using namespace std;

OrderBook::OrderBook(string filename)
{
    orders = CSVReader::readCSV(filename);
}

vector<string> OrderBook::getKnownProducts()
{
    vector<string> products;
    map<string, bool> productMap;
    for (auto const &order : orders)
    {
        productMap[order.getProduct()] = true;
    }

    // Flatten map to vector
    for (auto const &product : productMap)
    {
        products.push_back(product.first);
    }

    return products;
}

vector<OrderBookEntry> OrderBook::getOrders(
    OrderBookType type,
    string product,
    string timestamp)
{
    vector<OrderBookEntry> _orders;
    for (auto const &order : orders)
    {
        if (order.getOrderType() == type &&
            order.getProduct() == product &&
            order.getTimestamp() == timestamp)
        {
            _orders.push_back(order);
        }
    }

    return _orders;
}

/**
 * Get all orders for a given product between two timestamps
 * @param type The type of order (bid or ask)
 * @param product The product to get orders for
 * @param startTime The start of the time period
 * @param endTime The end of the time period
 * @returns A vector of orders
 */
vector<OrderBookEntry> OrderBook::getOrdersForTimePeriod(
    OrderBookType type,
    string product,
    string startTime,
    string endTime)
{
    vector<OrderBookEntry> _orders;
    for (auto const &order : orders)
    {
        if (order.getOrderType() == type &&
            order.getProduct() == product &&
            order.getTimestamp() >= startTime &&
            order.getTimestamp() <= endTime)
        {
            _orders.push_back(order);
        }
    }

    return _orders;
}

string OrderBook::getEarliestTime()
{
    return orders[0].getTimestamp();
}

string OrderBook::getNextTime(string timestamp)
{
    string _timestamp = "";
    for (auto const &order : orders)
    {
        if (order.getTimestamp() > timestamp)
        {
            _timestamp = order.getTimestamp();
            break;
        }
        if (_timestamp == "")
        {
            _timestamp = getEarliestTime();
        }
    }

    return _timestamp;
}

void OrderBook::insertOrder(OrderBookEntry &order)
{
    orders.push_back(order);
    sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

vector<OrderBookEntry> OrderBook::matchAsksToBids(string product, string timestamp)
{
    cout << "Matching asks to bids for " << product << " at " << timestamp << endl;

    vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    vector<OrderBookEntry> sales;

    cout << "Max ask: " << OrderBook::getHighPrice(asks) << endl;
    cout << "Min ask: " << OrderBook::getLowPrice(asks) << endl;
    cout << "Max bid: " << OrderBook::getHighPrice(bids) << endl;
    cout << "Min bid: " << OrderBook::getLowPrice(bids) << endl;

    sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    for (auto &ask : asks)
    {
        for (auto &bid : bids)
        {
            if (bid.getPrice() >= ask.getPrice())
            {
                OrderBookEntry sale{
                    ask.getPrice(),
                    0,
                    timestamp,
                    product,
                    OrderBookType::sale};

                if (bid.getAmount() == ask.getAmount())
                {
                    sale.setAmount(ask.getAmount());
                    sales.push_back(sale);
                    bid.setAmount(0);
                    break;
                }
                else if (bid.getAmount() > ask.getAmount())
                {
                    sale.setAmount(ask.getAmount());
                    sales.push_back(sale);
                    bid.setAmount(bid.getAmount() - ask.getAmount());
                    break;
                }
                else if (bid.getAmount() < ask.getAmount())
                {
                    sale.setAmount(bid.getAmount());
                    sales.push_back(sale);
                    ask.setAmount(ask.getAmount() - bid.getAmount());
                    bid.setAmount(0);
                    continue;
                }
            }
        }
    }

    cout << "Sales: " << sales.size() << endl;
    for (auto &sale : sales)
    {
        cout << "Sale price: " << sale.getPrice() << " amount: " << sale.getAmount() << endl;
    }

    return sales;
}

double OrderBook::getHighPrice(vector<OrderBookEntry> &orders)
{
    double highPrice = 0;
    for (auto const &order : orders)
    {
        if (order.getPrice() > highPrice)
        {
            highPrice = order.getPrice();
        }
    }

    return highPrice;
}

double OrderBook::getLowPrice(vector<OrderBookEntry> &orders)
{
    double lowPrice = 0;
    for (size_t i = 0; i < orders.size(); i++)
    {
        if (i == 0)
        {
            lowPrice = orders[i].getPrice();
        }
        else if (orders[i].getPrice() < lowPrice)
        {
            lowPrice = orders[i].getPrice();
        }
    }

    return lowPrice;
}

double OrderBook::getPriceSpread(vector<OrderBookEntry> &orders)
{
    double highPrice = getHighPrice(orders);
    double lowPrice = getLowPrice(orders);

    return highPrice - lowPrice;
}

double OrderBook::getPriceSpread(double min, double max)
{
    return max - min;
}

double OrderBook::getVolume(vector<OrderBookEntry> &orders)
{
    double volume = 0;
    for (auto const &order : orders)
    {
        volume += order.getAmount();
    }

    return volume;
}