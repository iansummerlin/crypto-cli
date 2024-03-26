#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "CryptoMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "Timestamp.h"

using namespace std;

void CryptoMain::init()
{
	running = true;
	currentTime = orderBook.getEarliestTime();
	int input;

	while (running == true)
	{
		printMenu();
		input = getInput();
		processInput(input);
	}
}

void CryptoMain::printMenu()
{
	// 1 print help
	cout << "1: Help" << endl;

	// 2 print exchange stats
	cout << "2: Print exchange stats" << endl;

	// 3 make an ask
	cout << "3: Make an ask" << endl;

	// 4 make a bid
	cout << "4: Make a bid" << endl;

	// 5 print wallet
	cout << "5: Print wallet" << endl;

	// 6 continue
	cout << "6: Continue" << endl;

	// 7 exit
	cout << "7: Exit" << endl;

	cout << "================" << endl;
	cout << "Current time is: " << currentTime << endl;
	cout << "Type in 1-7" << endl;
}

int CryptoMain::getInput()
{
	string line;
	getline(cin, line);

	int input;
	try
	{
		input = stoi(line);
	}
	catch (const exception &e)
	{
		cout << "CryptoMain::getInput error: Could not convert input to int." << endl;
		input = 0;
	}

	cout << "You chose: " << input << endl;

	return input;
}

void CryptoMain::printHelp()
{
	cout << "Make money, analyse the market, make bids and offers." << endl;
	cout << "Choose options from the menu and follow the on screen instructions." << endl;
}

/**
 * Print exchange stats
 * This function will print the current stats for the exchange for the current timestamp
 * and the stats for the last 24 hours.
 * @returns void
 */
void CryptoMain::printExchangeStats()
{
	for (auto const &product : orderBook.getKnownProducts())
	{
		cout << "================" << endl;
		cout << "Product: " << product << endl;
		cout << "================" << endl;

		// Current stats
		vector<OrderBookEntry> orders = orderBook.getOrders(
			OrderBookType::ask,
			product,
			currentTime);

		cout << "Current timestamp stats: " << endl;
		cout << "Asks for product: " << orders.size() << endl;
		double maxPrice = OrderBook::getHighPrice(orders);
		double minPrice = OrderBook::getLowPrice(orders);
		cout << "Max ask: " << maxPrice << endl;
		cout << "Min ask: " << minPrice << endl;
		cout << "Spread: " << OrderBook::getPriceSpread(minPrice, maxPrice) << endl;

		// 24 Hour stats
		Timestamp ts(currentTime);
		string startTime = ts.getMinTimestamp();
		string endTime = ts.getMaxTimestamp();

		cout << "24 hour stats: " << endl;
		cout << "Between " << startTime << " and " << endTime << endl;

		vector<OrderBookEntry> orders24 = orderBook.getOrdersForTimePeriod(
			OrderBookType::ask,
			product,
			startTime,
			endTime);

		cout << "Asks for product: " << orders24.size() << endl;
		double maxPrice24 = OrderBook::getHighPrice(orders24);
		double minPrice24 = OrderBook::getLowPrice(orders24);
		cout << "Max ask: " << maxPrice24 << endl;
		cout << "Min ask: " << minPrice24 << endl;
		cout << "Spread: " << OrderBook::getPriceSpread(minPrice24, maxPrice24) << endl;
	}

	cout << "================" << endl;
}

void CryptoMain::enterAsk()
{
	cout << "Make an ask in the format: product,price,amount. E.g. ETH/BTC,200,0.5" << endl;
	string input;
	getline(cin, input);

	cout << "You entered: " << input << endl;
	vector<string> tokens = CSVReader::tokenise(input, ',');
	if (tokens.size() != 3)
	{
		cout << "CryptoMain::enterAsk error: invalid input, please enter in the format: product,price,amount" << endl;
	}
	else
	{
		try
		{
			OrderBookEntry order = CSVReader::stringsToOBE(
				tokens[1],
				tokens[2],
				currentTime,
				tokens[0],
				OrderBookType::ask);

			orderBook.insertOrder(order);
		}
		catch (const exception &e)
		{
			cout << "CryptoMain::enterAsk error: Could not convert price or amount to double." << endl;
		}
	}
}

void CryptoMain::enterBid()
{
	cout << "Make a bid in the format: product,price,amount. E.g. ETH/BTC,200,0.5" << endl;
	string input;
	getline(cin, input);

	cout << "You entered: " << input << endl;
	vector<string> tokens = CSVReader::tokenise(input, ',');
	if (tokens.size() != 3)
	{
		cout << "CryptoMain::enterBid error: invalid input, please enter in the format: product,price,amount" << endl;
	}
	else
	{
		try
		{
			OrderBookEntry order = CSVReader::stringsToOBE(
				tokens[1],
				tokens[2],
				currentTime,
				tokens[0],
				OrderBookType::bid);

			orderBook.insertOrder(order);
		}
		catch (const exception &e)
		{
			cout << "CryptoMain::enterBid error: Could not convert price or amount to double." << endl;
		}
	}
}

void CryptoMain::printWallet()
{
	cout << "Print wallet." << endl;
}

void CryptoMain::handleContinue()
{
	cout << "Going to next time frame..." << endl;
	vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);

	currentTime = orderBook.getNextTime(currentTime);
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
	menu[3] = &CryptoMain::enterAsk;
	menu[4] = &CryptoMain::enterBid;
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
