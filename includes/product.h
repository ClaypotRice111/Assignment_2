#ifndef PRODUCT_H
#define PRODUCT_H


#include <iostream>
#include <string>
#include <iomanip>
//#include <map>
//#include <vector>
// vector<map<int,Produce>> 

using namespace std;

// Display Trash Message
const bool g_debug = true;

class InventoryItem {
public:
	// Public static data:
	static const int DEFAULT_ITEM_ID;							// 9999
	static const bool DEFAULT_RESTOCKING;						// false

	// Constructors
	InventoryItem();										
	InventoryItem(int new_id, bool new_status);
	~InventoryItem();

	//Public member functions:
	void Display();												// show InventoryItem item id and restocking (true/false)	
	void DisplayRow();											// show InventoryItem item id and restocking (true/false)
	
	void set_item_id(int item_id);
	void set_restocking(bool is_restocking);
	int get_item_id() const;
	bool get_restocking() const;

protected:
	// Protected member data: item id (integer) and restocking (bool).
	int item_id;
	bool restocking;

private:
	//nothing...  
};

class Product :public InventoryItem {
public:
	// Public static data:
	static const string DEAFAULT_NAME;
	static const int DEAFAULT_QUANTITY;
	static const double DEAFAULT_PRICE;

	//Constructors (use member initializer syntax)
	Product();
	Product(int item_id, bool is_restocking, string name, int quantity, double price);
	~Product();

	//Public member functions:
	void set_name(string name);
	void set_quantity(int quantity);
	void set_price(double price);
	string get_name() const;
	int get_quantity() const;
	double get_price() const;

	void Display();
	void DisplayRow();
	double Cost(int qty);
	bool is_restocking();


private:
	//Private member data: name (string), quantity (integer) and price (double).
	string name;
	int quantity;
	double price;

	// prevent the string 
	string TruncateName(string name, int limit_size);
};



#endif // !PRODUCT_H

