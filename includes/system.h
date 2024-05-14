#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "product.h"


using namespace std;



class  InventorySystem{
public:
	// Public static data
	static const string DEFAULT_STORE_NAME;
	static const int DEFAULT_PRODUCT_COUNT;
	static const int DEFAULT_ARRAY_SIZE;
	static const string DEFAULT_INPUT_FILE_NAME;
	static const string DEFAULT_OUTPUT_FILE_NAME;

	//Constructors
	InventorySystem();
	InventorySystem(string store_name);
	~InventorySystem();

	///Public member functions:
	//// read a text file containing electronics products information and dynamically store them in an array of pointers.
	void BuildInventory();
	//// display all inventory items.
	void ShowInventory();
	//// ask for item id and quantity.If found display cost and update Product object info(reduce Product's quantity and potentially update restocking flag).
	void UpdateInventory();
	//// save current inventory to a text file.
	void Terminate();
	//// discontinue a Product from Inventory. 
	void Discontinue(int item_id);


private:
	// Private member data
	string store_name;
	InventoryItem** product_list;
	int product_count;


	// Private member function:
	//// if found return the InventoryItem pointer.Otherwise return nullptr.
	InventoryItem* FindInventoryItem(int item_id);
	//// read a file bu special text format
	void ReadFile(ifstream& File);
	//// write a file by special text format
	void WriteFile(fstream& File);

};


#endif // SYSTEM_H

