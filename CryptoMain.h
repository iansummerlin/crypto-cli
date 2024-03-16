#include <vector>
#include "OrderBookEntry.h"

class CryptoMain
{
public:
    CryptoMain() = default;
    void init();

private:
    bool running;
    vector<OrderBookEntry> orders;

    void loadOrderBook();
    void printMenu();
    int getInput();
    void printHelp();
    void printExchangeStats();
    void makeOffer();
    void makeBid();
    void printWallet();
    void handleContinue();
    void handleExit();
    void handleInvalidInput();
    void processInput(int &input);

    // double computeAveragePrice(vector<OrderBookEntry> &orders);
    // double computeLowPrice(vector<OrderBookEntry> &orders);
    // double computeHighPrice(vector<OrderBookEntry> &orders);
    // double computePriceSpread(vector<OrderBookEntry> &orders);
};
