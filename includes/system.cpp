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
		product_list[i] = nullptr;
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
	ifstream in_file(DEFAULT_INPUT_FILE_NAME + ".txt");
	if (!in_file.is_open()) {
		cout << "ERROR: Failed to open input file\n";
		return;
	}
	ReadFile(in_file);
	in_file.close();
};

void InventorySystem::ShowInventory() {
	cout << "Store Name: " << store_name <<"         Total product number: "<< product_count << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << "       ID               Name                   Quantity   Price" << endl;
	cout << "------------------------------------------------------------------------" << endl;
	Product* p_product = nullptr;
	for (auto i = 0; i < product_count; i++) {
		p_product = static_cast<Product*>(product_list[i]);
		p_product->DisplayRow();
		cout << endl;
	}
	cout << "------------------------------------------------------------------------" << endl;
};

void InventorySystem::UpdateInventory() {
	int item_id = 0;
	int number_of_purchase = 0;

	cout << "Enter item ID: ";
	cin >> item_id;

	InventoryItem* item = FindInventoryItem(item_id);
	if (item == nullptr) {
		cout << "Item not found." << endl;
		return;
	}

	cout << "Enter quantity: ";
	cin >> number_of_purchase;

	Product* product = static_cast<Product*>(item);
	double totalCost = product->Cost(number_of_purchase);
	cout << "Total cost: $" << fixed << setprecision(2) << totalCost<< endl;

	if (product->get_quantity() < number_of_purchase) 
		cout << "We have no more product, need to restock" << endl;
	else
		product->set_quantity(product->get_quantity() - number_of_purchase);

	if (product->get_quantity() == 0) {
		if (g_debug)
			cout << "item id: " << item_id << " need to restock" << endl;

		product->set_restocking(true);
	};
}

void InventorySystem::Terminate() {
ofstream out_file(DEFAULT_OUTPUT_FILE_NAME + ".txt");
	if (!out_file.is_open()) {
		cout << "ERROR: Failed to open output file\n";
		out_file.open(DEFAULT_OUTPUT_FILE_NAME + ".txt");
	}
	WriteFile(out_file);
	out_file.close();
};

void InventorySystem::Discontinue() {
	int item_id = 0;
	cout << "Enter item ID: ";
	cin >> item_id;

	InventoryItem* p_item = FindInventoryItem(item_id);
	if (!p_item) {
		return;
	}

	for (auto i = 0; i < product_count; i++) {
		if (product_list[i] == p_item) {
			for (auto j = i; j < product_count -1; j++) {
				product_list[j] = product_list[j +1];
			}
			break;
		}
	}
	product_count--;
	delete p_item;
	product_list[product_count] = nullptr;
};

InventoryItem* InventorySystem::FindInventoryItem(int item_id) {
	for (int i = 0; i < product_count; i++) {
		if (product_list[i]->get_item_id() == item_id) {
			return product_list[i];
		}
	}
	return nullptr;
};




void InventorySystem::ReadFile(ifstream& File) {
	string buffer;
	string name;
	int id = 0;
	int qty = 0;
	double price = 0 ;
	bool restock_status = false;

	product_count = 0; //reset count number is IMPORTANT, prevent be calling by furture update.

	while (getline(File, buffer, ';')&&(product_count+1 < DEFAULT_ARRAY_SIZE)) {
		id = stoi(buffer);

		getline(File, buffer, ';');
		name = buffer;

		getline(File, buffer, ';');
		qty = stoi(buffer);
		if (qty == 0) 
			restock_status = true;
		else 
			restock_status = false;

		getline(File, buffer, '\n');
		price = stod(buffer.c_str());

		product_list[product_count] = new Product(id, restock_status, name, qty, price);
		product_count++;
	}
}

void InventorySystem::WriteFile(ofstream& File) {
	Product* p_product = nullptr;
	for (auto i = 0; i < product_count; i++) {
		p_product = static_cast<Product*>(product_list[i]);
		File << to_string(p_product->get_item_id()) + ";" +
			p_product->get_name() + ";" +
			to_string(p_product->get_quantity()) + ";" +
			to_string(p_product->get_price()) + "\n";
	}
}

void InventorySystem::Run(){

	bool Loop = true;
	while (Loop){
		cout << endl << endl << endl;
		cout << "Enter Option" <<endl;
		cout << "1. Show Inventory" << endl;
		cout << "2. Puchase Product" <<endl;
		cout << "3. Reload Invetory" << endl;
		cout << "4. Save" <<endl;
		cout << "5. Remove product" <<endl;
		cout << "6. Exit System" <<endl;
		int option = getch();
		switch (option)
		{
		case 49: // ascii code 49 = number 1
			ShowInventory();
			break;
		case 50:
			UpdateInventory();
			break;
		case 51:
			BuildInventory();
			break;
		case 52:
			Terminate();
			break;
		case 53:
			Discontinue();
			break;
		case 54:
			Loop = false;
			break;		
		default:
			cout << "Please re-type your option" << endl;
			break;
		}
	}
}


bool is_all_digital(const string value){
	for(auto& letter: value ){
		if (letter > 57 || letter < 48){
			return false;
		}
	}
	return true;
}



bool is_a_number(const string value){
	for(auto& letter: value ){
		if (letter > 57 || letter < 48){
			return false;
		}else{
			if (letter != 46){
				return false;
			}else{
				if (letter > 57 || letter < 48){
					return false;
				}
			}
		}
	}
	return true;
}


bool is_a_word(const string value){
	// it need a stata machine and get token function
	return true;
}