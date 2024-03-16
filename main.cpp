#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <string>

using namespace std;

void printMenu();
int getInput();
void printHelp();
void printExchangeStats();
void makeOffer();
void makeBid();
void printWallet();
void handleContinue();
void handleExit(bool &running);
void handleInvalidInput();
void processInput(int &input, bool &running);

double computeAveragePrice(vector<OrderBookEntry> &orders);
double computeLowPrice(vector<OrderBookEntry> &orders);
double computeHighPrice(vector<OrderBookEntry> &orders);
double computePriceSpread(vector<OrderBookEntry> &orders);

int main() {
	// bool running = true;

	// while(running == true) {
	// 	printMenu();
	// 	int input = getInput();
	// 	processInput(input, running);
	// }

	vector<OrderBookEntry> orders;

	OrderBookEntry order1{10000, 1.2, "2020/03/17 10:00:00.984492", "BTC/USDT", OrderBookType::bid};
	OrderBookEntry order2{13022, 1.2, "2020/03/17 10:30:00.984492", "BTC/USDT", OrderBookType::ask};

	orders.push_back(order1);
	orders.push_back(order2);

	for (auto &order: orders) {
		cout << "Price: " << order.getPrice() << endl;
		cout << "Amount: " << order.getAmount() << endl;
		cout << "Timestamp: " << order.getTimestamp() << endl;
		cout << "Product: " << order.getProduct() << endl;
		cout << "Order type: " << (order.getOrderType() == OrderBookType::bid ? "bid" : "ask") << endl;
		cout << "================" << endl;
	}

	cout << "Average price: " << computeAveragePrice(orders) << endl;
	cout << "Low price: " << computeLowPrice(orders) << endl;
	cout << "High price: " << computeHighPrice(orders) << endl;
	cout << "Price spread: " << computePriceSpread(orders) << endl;

	return 0;
}

void printMenu() {
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

int getInput() {
	int input;
	cin >> input;
	cout << "You chose: " << input << endl;

	return input;
}

void printHelp() {
	cout << "Make money, analyse the market, make bids and offers." << endl;
	cout << "Choose options from the menu and follow the on screen instructions." << endl;
}

void printExchangeStats() {
	cout << "Exchange stats: " << endl;
}

void makeOffer() {
	cout << "Make an offer." << endl;
}

void makeBid() {
	cout << "Make a bid." << endl;
}

void printWallet() {
	cout << "Print wallet." << endl;
}

void handleContinue() {
	cout << "Continue." << endl;
}

void handleExit(bool &running) {
	cout << "Exiting..." << endl;
	running = false;
}

void handleInvalidInput() {
	cout << "Invalid choice. Choose 1-7." << endl;
}

void processInput(int &input, bool &running) {
	// Map from ints to function pointers
    map<int, function<void()>> menu;
    menu[1] = printHelp;
    menu[2] = printExchangeStats;
    menu[3] = makeOffer;
    menu[4] = makeBid;
    menu[5] = printWallet;
    menu[6] = handleContinue;
    menu[7] = [&running]() { handleExit(running); };

	if (menu.find(input) != menu.end()) {
		menu[input](); 
	} else {
		handleInvalidInput();
	}
}

double computeAveragePrice(vector<OrderBookEntry> &orders) {
	double sum = 0;
	for (auto &order: orders) {
		sum += order.getPrice();
	}

	return sum / orders.size();
}

double computeLowPrice(vector<OrderBookEntry> &orders) {
	double low = 0;
	for (size_t i = 0; i < orders.size(); ++i) {
		if (i == 0) {
			low = orders[i].getPrice();
		} else {
			if (orders[i].getPrice() < low) {
				low = orders[i].getPrice();
			}
		}
	}

	return low;
}

double computeHighPrice(vector<OrderBookEntry> &orders) {
	double high = 0;
	for (size_t i = 0; i < orders.size(); ++i) {
		if (i == 0) {
			high = orders[i].getPrice();
		} else {
			if (orders[i].getPrice() > high) {
				high = orders[i].getPrice();
			}
		}
	}

	return high;
}

double computePriceSpread(vector<OrderBookEntry> &orders) {
	double low = computeLowPrice(orders);
	double high = computeHighPrice(orders);

	return high - low;
}
