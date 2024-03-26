#pragma once

#include <vector>
#include <string>
#include "OrderBookEntry.h"

using namespace std;

class CSVReader
{
public:
    CSVReader();
    static vector<OrderBookEntry> readCSV(string csvFile);
    static vector<string> tokenise(string line, char separator);
    static OrderBookEntry stringsToOBE(
        string price,
        string amount,
        string timestamp,
        string product,
        OrderBookType orderType);

private:
    static OrderBookEntry stringsToOBE(vector<string> tokens);
};