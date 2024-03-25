#include <iostream>
#include <fstream>
#include "CSVReader.h"
#include "OrderBookEntry.h"

using namespace std;

CSVReader::CSVReader()
{
}

vector<OrderBookEntry> CSVReader::readCSV(string csvFilename)
{
    vector<OrderBookEntry> entries;
    ifstream csvFile{csvFilename};
    string line;

    if (csvFile.is_open())
    {
        while (getline(csvFile, line))
        {
            try
            {
                OrderBookEntry order = stringsToOBE(tokenise(line, ','));
                entries.push_back(order);
            }
            catch (const exception &e)
            {
                cout << "CSVReader::readCSV error: Could not read line from file." << endl;
                cout << "Line: " << line << endl;
            }
        }

        csvFile.close();
    }
    else
    {
        cout << "CSVReader::readCSV error: Could not open file " << csvFilename << endl;
        throw exception();
    }

    cout << "CSVReader::readCSV read " << entries.size() << " entries from " << csvFilename << endl;

    return entries;
}

vector<string> CSVReader::tokenise(string csvLine, char seperator)
{
    vector<string> tokens;
    long unsigned int start, end;
    string token;
    start = csvLine.find_first_not_of(seperator, 0);
    do
    {
        end = csvLine.find_first_of(seperator, start);
        if (start == csvLine.length() || start == end)
            break;

        if (end >= 0)
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);

        tokens.push_back(token);
        start = end + 1;
    } while (end != string::npos);

    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(vector<string> tokens)
{
    if (tokens.size() != 5)
    {
        cout << "CSVReader::stringsToOBE error: Expected 5 tokens per line - found " << tokens.size() << endl;
        throw exception();
    }

    double price, amount;
    try
    {
        price = stod(tokens[3]);
        amount = stod(tokens[4]);
    }
    catch (const exception &e)
    {
        cout << "CSVReader::stringsToOBE error: Could not convert price or amount to double." << endl;
        cout << "Price: " << tokens[3] << endl;
        cout << "Amount: " << tokens[4] << endl;
        throw;
    }

    OrderBookEntry order{
        price,
        amount,
        tokens[0],
        tokens[1],
        OrderBookEntry::stringToOrderBookType(tokens[2])};

    return order;
}

OrderBookEntry CSVReader::stringsToOBE(
    string price,
    string amount,
    string timestamp,
    string product,
    OrderBookType orderType)
{
    double _price, _amount;
    try
    {
        _price = stod(price);
        _amount = stod(amount);
    }
    catch (const exception &e)
    {
        cout << "CSVReader::stringsToOBE error: Could not convert price or amount to double." << endl;
        cout << "Price: " << price << endl;
        cout << "Amount: " << amount << endl;
        throw;
    }

    OrderBookEntry order{
        _price,
        _amount,
        timestamp,
        product,
        orderType};

    return order;
}
