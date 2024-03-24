#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "CryptoMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"

using namespace std;

void CryptoMain::init()
{
	running = true;
	loadOrderBook();
	int input;

	while (running == true)
	{
		printMenu();
		input = getInput();
		processInput(input);
	}
}

void CryptoMain::loadOrderBook()
{
	orders = CSVReader::readCSV("order_book.csv");
}

void CryptoMain::printMenu()
{
	// 1 print help
	cout << "1: Help" << endl;

	// 2 print exchange stats
	cout << "2: Print exchange stats" << endl;

	// 3 make an offer
	cout << "3: Make an offer" << endl;

	// 4 make a bid
	cout << "4: Make a bid" << endl;

	// 5 print wallet
	cout << "5: Print wallet" << endl;

	// 6 continue
	cout << "6: Continue" << endl;

	// 7 exit
	cout << "7: Exit" << endl;

	cout << "================" << endl;
	cout << "Type in 1-7" << endl;
}

int CryptoMain::getInput()
{
	int input;
	cin >> input;
	cout << "You chose: " << input << endl;

	return input;
}

void CryptoMain::printHelp()
{
	cout << "Make money, analyse the market, make bids and offers." << endl;
	cout << "Choose options from the menu and follow the on screen instructions." << endl;
}

void CryptoMain::printExchangeStats()
{
	cout << "Exchange stats: " << endl;
	cout << "There are currently " << orders.size() << " orders in the system." << endl;

	unsigned int bids = 0;
	unsigned int asks = 0;

	for (auto &order : orders)
	{
		if (order.getOrderType() == OrderBookType::bid)
		{
			bids++;
		}
		else
		{
			asks++;
		}
	}

	cout << "There are " << bids << " bids and " << asks << " asks." << endl;
}

void CryptoMain::makeOffer()
{
	cout << "Make an offer." << endl;
}

void CryptoMain::makeBid()
{
	cout << "Make a bid." << endl;
}

void CryptoMain::printWallet()
{
	cout << "Print wallet." << endl;
}

void CryptoMain::handleContinue()
{
	cout << "Continue." << endl;
}

void CryptoMain::handleExit()
{
	cout << "Exiting..." << endl;
	running = false;
}

void CryptoMain::handleInvalidInput()
{
	cout << "Invalid choice. Choose 1-7." << endl;
}

void CryptoMain::processInput(int &input)
{
	// Map from ints to function pointers
	map<int, void (CryptoMain::*)()> menu;
	menu[1] = &CryptoMain::printHelp;
	menu[2] = &CryptoMain::printExchangeStats;
	menu[3] = &CryptoMain::makeOffer;
	menu[4] = &CryptoMain::makeBid;
	menu[5] = &CryptoMain::printWallet;
	menu[6] = &CryptoMain::handleContinue;
	menu[7] = &CryptoMain::handleExit;

	auto it = menu.find(input);
	if (it != menu.end())
	{
		// Call the member function
		(this->*(it->second))();
	}
	else
	{
		handleInvalidInput();
	}
}

// double CryptoMain::computeAveragePrice(vector<OrderBookEntry> &orders)
// {
// 	double sum = 0;
// 	for (auto &order : orders)
// 	{
// 		sum += order.getPrice();
// 	}

// 	return sum / orders.size();
// }

// double CryptoMain::computeLowPrice(vector<OrderBookEntry> &orders)
// {
// 	double low = 0;
// 	for (size_t i = 0; i < orders.size(); ++i)
// 	{
// 		if (i == 0)
// 		{
// 			low = orders[i].getPrice();
// 		}
// 		else
// 		{
// 			if (orders[i].getPrice() < low)
// 			{
// 				low = orders[i].getPrice();
// 			}
// 		}
// 	}

// 	return low;
// }

// double CryptoMain::computeHighPrice(vector<OrderBookEntry> &orders)
// {
// 	double high = 0;
// 	for (size_t i = 0; i < orders.size(); ++i)
// 	{
// 		if (i == 0)
// 		{
// 			high = orders[i].getPrice();
// 		}
// 		else
// 		{
// 			if (orders[i].getPrice() > high)
// 			{
// 				high = orders[i].getPrice();
// 			}
// 		}
// 	}

// 	return high;
// }

// double CryptoMain::computePriceSpread(vector<OrderBookEntry> &orders)
// {
// 	double low = computeLowPrice(orders);
// 	double high = computeHighPrice(orders);

// 	return high - low;
// }
