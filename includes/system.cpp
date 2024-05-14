#include "System.h"


const string InventorySystem::DEFAULT_STORE_NAME = "My Store";
const int InventorySystem::DEFAULT_PRODUCT_COUNT = 0;
const int InventorySystem::DEFAULT_ARRAY_SIZE = 512;
const string InventorySystem::DEFAULT_INPUT_FILE_NAME = "default";
const string InventorySystem::DEFAULT_OUTPUT_FILE_NAME = "data";

InventorySystem::InventorySystem() {
	this->store_name = InventorySystem::DEFAULT_STORE_NAME;
	this->product_count = InventorySystem::DEFAULT_PRODUCT_COUNT;
	this->product_list = new InventoryItem* [InventorySystem::DEFAULT_ARRAY_SIZE];
	for (auto i = 0; i < InventorySystem::DEFAULT_ARRAY_SIZE; i++) {
		product_list[i] = nullptr;
	}
	BuildInventory();
};

InventorySystem::InventorySystem(string store_name) {
	this->store_name = store_name;
	this->product_count = InventorySystem::DEFAULT_PRODUCT_COUNT;
	this->product_list = new InventoryItem* [InventorySystem::DEFAULT_ARRAY_SIZE];
	for (auto i = 0; i < InventorySystem::DEFAULT_ARRAY_SIZE; i++) {
		*product_list = nullptr;
		product_list++;
	}
	BuildInventory();
};

InventorySystem::~InventorySystem() {
	for (auto i = 0; i < product_count; i++) {
		delete product_list[i];
	}
	delete[] product_list;
};


void InventorySystem::BuildInventory() {
	ifstream InFile(DEFAULT_INPUT_FILE_NAME + ".txt");
	if (!InFile) {
		cout << "ERROR: Failed to open input file\n";
		return;
	}
	ReadFile(InFile);
	InFile.close();
};

void InventorySystem::ShowInventory() {
	cout << "Store Name: " << store_name <<"         Total product number: "<< product_count << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << "       ID               Name                   Quantity   Price" << endl;
	cout << "------------------------------------------------------------------------" << endl;
	Product* p_product;
	for (auto i = 0; i < product_count; i++) {
		p_product = static_cast<Product*>(product_list[i]);
		p_product->DisplayRow();
		cout << endl;
	}
	cout << "------------------------------------------------------------------------" << endl;
};

void InventorySystem::UpdateInventory() {
	int id, qty;

	cout << "Enter item ID: ";
	cin >> id;

	InventoryItem* item = FindInventoryItem(id);
	if (item == nullptr) {
		cout << "Item not found." << endl;
		return;
	}

	cout << "Enter quantity: ";
	cin >> qty;

	Product* product = static_cast<Product*>(item);
	double totalCost = product->Cost(qty);
	cout << "Total cost: $" << fixed << setprecision(2) << totalCost<< endl;

	if (product->get_quantity() < qty) {
		cout << "we have no more product, please wait for next time" << endl;
	}else
		product->set_quantity(product->get_quantity() - qty);
	if (product->get_quantity() == 0) {
		product->set_restocking(true);
	}
};

void InventorySystem::Terminate() {
	fstream OutFile(DEFAULT_OUTPUT_FILE_NAME + ".txt");
	if (!OutFile) {
		cout << "ERROR: Failed to open output file\n";
	
	}
	WriteFile(OutFile);
	OutFile.close();

};

void InventorySystem::Discontinue(int item_id) {

	InventoryItem* p_item = FindInventoryItem(item_id);
	if (!p_item) {
		return;
	}

	for (auto i = 0; i < DEFAULT_ARRAY_SIZE; i++) {
		if (product_list[i] == p_item) {
			for (auto j = i; j < product_count -1; j++) {
				product_list[j] = product_list[j +1];
			}
			break;
		}
	}
	product_count--;
	product_list[product_count] = nullptr;
};

InventoryItem* InventorySystem::FindInventoryItem(int item_id) {
	for (int i = 0; i < DEFAULT_ARRAY_SIZE; i++) {
		if (product_list[i]->get_item_id() == item_id) {
			return product_list[i];
		}
	}
	return nullptr;
};




void InventorySystem::ReadFile(ifstream& File) {
	string buffer;
	string name;
	int id;
	int qty;
	double price;
	bool restock;

	product_count = 0; //reset count number is IMPORTANT, prevent be calling by furture update.

	while (getline(File, buffer, ';')&&(product_count+1 < DEFAULT_ARRAY_SIZE)) {

		id = stoi(buffer);

		getline(File, buffer, ';');
		name = buffer;

		getline(File, buffer, ';');

		qty = stoi(buffer);
		if (qty == 0) {
			restock = true;
		}
		else {
			restock = false;
		}

		getline(File, buffer, '\n');
		price = stod(buffer.c_str());

		product_list[product_count] = new Product(id, restock, name, qty, price);
		product_count++;
	}
}

void InventorySystem::WriteFile(fstream& File) {
	Product* p_product;
	for (auto i = 0; i < product_count; i++) {
		p_product = static_cast<Product*>(product_list[i]);
		File << to_string(p_product->get_item_id()) + ";" +
			p_product->get_name() + ";" +
			to_string(p_product->get_quantity()) + ";" +
			to_string(p_product->get_price()) + "\n";
	}
}



