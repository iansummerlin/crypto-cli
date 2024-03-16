#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(
    double price,
    double amount,
    string timestamp,
    string product,
    OrderBookType orderType
)
: price(price), 
amount(amount), 
timestamp(timestamp), 
product(product), 
orderType(orderType) {}