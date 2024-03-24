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

private:
    static vector<string> tokenise(string line, char separator);
    static OrderBookEntry stringsToOBE(vector<string> tokens);
};