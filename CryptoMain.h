#include <vector>
#include <string>
#include "OrderBook.h"
#include "OrderBookEntry.h"

class CryptoMain
{
public:
    CryptoMain() = default;
    void init();

private:
    bool running;
    string currentTime;
    OrderBook orderBook{"order_book.csv"};

    void printMenu();
    int getInput();
    void printHelp();
    void printExchangeStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void handleContinue();
    void handleExit();
    void handleInvalidInput();
    void processInput(int &input);
};
