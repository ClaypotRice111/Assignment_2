#include "product.h"


/*===================================================================================================
class InventoryItem
====================================================================================================*/

const int InventoryItem::DEFAULT_ITEM_ID = 9999;
const bool InventoryItem::DEFAULT_RESTOCKING = false;


InventoryItem::InventoryItem() {
	this->item_id = InventoryItem::DEFAULT_ITEM_ID;
	this->restocking = InventoryItem::DEFAULT_RESTOCKING;
};

InventoryItem::InventoryItem(int new_id, bool new_status) {
	this->item_id = new_id;
	this->restocking = new_status;
};

InventoryItem::~InventoryItem() {
	if (g_debug)
		cout << "InventoryItem <item id> with <true/false> restocking destroyed ..." << endl;
};

void InventoryItem::Display() {
	cout << "Item ID: " << setfill('0') << setw(4) << item_id << ", Restocking: " << (restocking ? "Yes" : "No");
};

void InventoryItem::DisplayRow() {
	cout << setfill(' ') << setw(6) << (restocking ? "@@@" : " ");
	cout <<' ' <<setfill('0') << setw(4) << right << item_id << setfill(' ') << "       ";
};

void InventoryItem::set_item_id(int item_id) { 
	this->item_id = item_id; 
};

void InventoryItem::set_restocking(bool is_restocking) { 
	this->restocking = is_restocking; 
};

int InventoryItem::get_item_id() const { 
	return item_id; 
};

bool InventoryItem::get_restocking() const { 
	return restocking; 
};




/*===================================================================================================
class Product
====================================================================================================*/



const string Product::DEAFAULT_NAME = "No Product";
const int Product::DEAFAULT_QUANTITY = 0;
const double Product::DEAFAULT_PRICE = 0.99;


Product::Product():InventoryItem() {
	this->name = Product::DEAFAULT_NAME;
	this->quantity = Product::DEAFAULT_QUANTITY;
	this->price = Product::DEAFAULT_PRICE;
};

Product::Product(int item_id, bool is_restocking, string name, int quantity, double price):InventoryItem(item_id, is_restocking) {
	this->name = name;
	this->quantity = quantity;
	this->price = price;
};

Product::~Product() {
	if (g_debug) {
		cout << "Product: " << item_id << ", Name: " << name << ", quantity: " << quantity << ", price " << price << " , restocking: " << (restocking ? "Yes" : "No") << " destroyed ..." << endl;
	}
};

void Product::set_name(string name) { 
	this->name = name; 
};

void Product::set_quantity(int quantity) { 
	this->quantity = quantity; 
};

void Product::set_price(double price) { 
	this->price = price; 
};

string Product::get_name() const { 
	return name; 
};

int Product::get_quantity() const { 
	return quantity; 
};

double Product::get_price() const { 
	return price; 
};

void Product::Display(){
	InventoryItem::Display();
	cout << ", Name: " << name << ", Quantity: " << quantity << ", Price: $" << fixed << setprecision(2) << price << endl;
};

void Product::DisplayRow() {
	InventoryItem::DisplayRow();

	cout << setw(30) << left << TruncateName(name, 30);
	cout << setw(10) << quantity;
	cout << "$" << fixed << setprecision(2) << price;
};


double Product::Cost(int qty) {
	return price * qty;
};

string Product::TruncateName(string name, int limit_size) {
	if (name.length() < limit_size)
		return name;
	return name.substr(0, limit_size - 5) + "...";
}

bool Product::is_restocking() {
	if (quantity == 0)
		return true;
	return false;
};