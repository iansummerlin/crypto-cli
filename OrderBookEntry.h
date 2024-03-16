#include <string>

enum class OrderBookType{bid, ask};

class OrderBookEntry {
	private:
		double price;
		double amount;
		string timestamp;
		string product;
		OrderBookType orderType;
	public:
		OrderBookEntry(
			double price,
			double amount,
			string timestamp,
			string product,
			OrderBookType orderType
		);
		double getPrice() const { return price; }
		double getAmount() const { return amount; }
		string getTimestamp() const { return timestamp; }
		string getProduct() const { return product; }
		OrderBookType getOrderType() const { return orderType; }
};