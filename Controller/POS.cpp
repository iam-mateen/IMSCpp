#include <iostream>
#include <windows.h>
#include <string>
#include "DatabaseManager.cpp"
#include "../Model/Item.cpp"
#include "../Model/Customer.cpp"
#include "../Model/Sales.cpp"

using namespace std;

class POS
{
private:
	Item **items;
	Customer **customers;
	Sales **sales;
	Receipt **receipts;

	int totalItems;
	int totalCustomers;
	int totalSales;
	int totalReceipts;

	DatabaseManager *db;
	Util *utils;

public:
	POS()
	{
		initPointers();
		db = new DatabaseManager();
		utils = new Util();
		
		items = db->loadItems(totalItems);
		customers = db->loadCustomers(totalCustomers);
		sales = db->loadSales(totalSales);
		receipts = db->loadReceipts(totalReceipts);
	}

	~POS()
	{
		if (items != nullptr)
			delete[] items;

		if (customers != nullptr)
			delete[] customers;

		if (sales != nullptr)
			delete[] sales;

		if (receipts != nullptr)
			delete[] receipts;

		if (db != nullptr)
			delete db;

		if (utils != nullptr)
			delete utils;
	}

	void initPointers()
	{
		items = nullptr;
		customers = nullptr;
		sales = nullptr;
		receipts = nullptr;
		db = nullptr;
		utils = nullptr;
		totalItems = 0;
		totalReceipts = 0;
		totalCustomers = 0;
		totalSales = 0;
	}

	void addNewItem()
	{
		char itemSKU[100], itemDescription[1000];
		string creationDate;
		int price, availableQuantity;
		cin.ignore();
		cout << "Item SKU: ";
		cin.getline(itemSKU, '`');
		cout << "Item Description: ";
		cin.getline(itemDescription, '`');
		cout << "Item Price: ";
		cin >> price;
		cout << "Item Quantatiy: ";
		cin >> availableQuantity;
		creationDate = utils->getCurrentDate();

		bool alreadyExists = false;
		for (int i = 0; i < totalItems; i++)
		{
			if (items[i]->getItemSku().compare(itemSKU) == 0)
			{
				alreadyExists = true;
				i = totalItems + 10;
			}
		}

		if (!alreadyExists)
		{
			Item *item = new Item(itemSKU, itemDescription, price, availableQuantity, creationDate);
			bool isInserted = db->insertItem(item);
			if (isInserted)
			{
				delete[] items;
				items = db->loadItems(totalItems);
				cout << "Item Inserted Successfully!" << endl;
			}
			else
				cout << "Item Insertion Failed!" << endl;
			delete item;
		}
		else
			cout << "Item with this SKU already exists!" << endl;

		system("pause");
	}

	void updateItem()
	{
		string itemSku;
		cin.ignore();
		cout << "Item SKU: ";
		getline(cin, itemSku);
		bool found = false;
		for (int i = 0; i < totalItems; i++)
		{
			if (items[i]->getItemSku().compare(itemSku) == 0)
			{
				cout << "Item found! Leave blank to not change that info." << endl;
				found = true;

				cout << "----------- Item Details -----------" << endl;
				cout << "Sku: " << itemSku << ", Description: " << items[i]->getDescription() << ", Price: " << items[i]->getPrice() << ", Quantity: " << items[i]->getQuantity() << endl;

				cout << "----------- Enter New Details --------------" << endl;
				char *description = new char[500];
				string date;
				int price, quantity;
				cout << "Item Description: ";
				cin.getline(description, '`');
				cout << "Item Price: ";
				cin >> price;
				cout << "Item Quantity: ";
				cin >> quantity;
				date = utils->getCurrentDate();
				if (strlen(description) == 0)
				{
					strcpy(description, items[i]->getDescription().c_str());
				}
				if (price <= 0)
				{
					price = items[i]->getPrice();
				}
				if (quantity <= 0)
				{
					quantity = items[i]->getQuantity();
				}
				cout << "Are you sure you want to modiy (y,n)";
				char confirm;
				cin >> confirm;
				if (confirm == 'y' || confirm == 'Y')
				{
					delete items[i];
					items[i] = new Item(itemSku, description, price, quantity, date);
					bool isUpdated = db->updateItem(items, totalItems);
					if (isUpdated)
						cout << "Item Updated Successfully!" << endl;
					else
						cout << "Error Updating Item!" << endl;
					i = totalItems + 10; //To break the loop
				}
				else
					cout << "Item not modified!" << endl;
			}
		}
		if (!found)
			cout << "Item not found!" << endl;

		system("pause");
	}

	void deleteItem()
	{
		char itemSku[30];
		cin.ignore();
		cout << "Item Sku: ";
		cin.getline(itemSku, '`');
		bool isFound = false;
		for (int i = 0; i < totalItems; i++)
		{
			if (items[i]->getItemSku().compare(itemSku) == 0)
			{
				isFound = true;
				cout << "Are you sure you want to delete (y,n)";
				char confirm;
				cin >> confirm;
				if (confirm == 'y' || confirm == 'Y')
				{
					bool isDeleted = db->deleteItem(items, totalItems, i);
					if (isDeleted)
					{
						delete[] items;
						items = db->loadItems(totalItems);
						cout << "Item deleted successfully!" << endl;
					}
					else
						cout << "Item is not deleted!" << endl;
				}
				else
					cout << "Item not deleted! :)" << endl;
			}
		}
		if (!isFound)
			cout << "Item not found!" << endl;

		system("pause");
	}

	void findItem()
	{
		cout << "-------Enter Atleast one info --------" << endl;
		char itemSku[30] = "";
		char description[500] = "";
		char date[10] = "";
		int price = -1;
		int quantity = -1;
		cin.ignore();
		cout << "Item SKU: ";
		cin.getline(itemSku, '`');
		cout << "Description: ";
		cin.getline(description, '`');
		cout << "Date: ";
		cin.getline(date, '`');
		cout << "Price: ";
		cin >> price;
		cout << "Quantity: ";
		cin >> quantity;

		cout << "------------------------------------------------------------" << endl;
		cout << "Item SKU\tDescription\tPrice\tQuantity\tDate" << endl;
		cout << "------------------------------------------------------------" << endl;

		for (int i = 0; i < totalItems; i++)
		{
			if ((items[i]->getItemSku().compare(itemSku) == 0) || (items[i]->getDescription().compare(description) == 0) || (items[i]->getDate().compare(date) == 0) || items[i]->getPrice() == price || items[i]->getQuantity() == quantity)
			{
				cout << items[i]->getItemSku() << "\t" << items[i]->getDescription() << "\t" << items[i]->getPrice() << "\t" << items[i]->getQuantity() << "\t" << items[i]->getDate() << endl;
				cout << "------------------------------------------------------------" << endl;
			}
		}

		system("pause");
	}

	void addNewCustomer()
	{
		char cnic[100], name[100], address[100], phone[100], email[100];
		int type = 0;
		cin.ignore();
		cout << "Enter CNIC: ";
		cin.getline(cnic, '`');
		cout << "Enter Name: ";
		cin.getline(name, '`');
		cout << "Enter Address: ";
		cin.getline(address, '`');
		cout << "Enter Phone: ";
		cin.getline(phone, '`');
		cout << "Enter Email: ";
		cin.getline(email, '`');
		cout << "Enter type: " << endl;
		cout << "1 for Silver Customer: " << endl;
		cout << "2 for Gold Customer: " << endl;
		cout << "3 for Platinum Customer: " << endl;
		cin >> type;
		Customer *customer;
		switch (type)
		{
		case 1:
			customer = new SilverCustomer(cnic, name, address, phone, email, 0);
			break;
		case 2:
			customer = new GoldCustomer(cnic, name, address, phone, email, 0);
			break;
		case 3:
			customer = new PlatinumCustomer(cnic, name, address, phone, email, 0);
			break;
		default:
			customer = new SilverCustomer(cnic, name, address, phone, email, 0);
		}
		bool isInserted = db->insertCustomer(customer);
		if (isInserted)
		{
			if (customers != nullptr)
				delete[] customers;
			customers = db->loadCustomers(totalCustomers);
			cout << "Customer created successfully!" << endl;
		}
		else
			cout << "Customer created failed!" << endl;
		delete customer;
		system("pause");
	}

	void updateCustomer()
	{
		char cnic[30];
		cin.ignore();
		cout << "Enter CNIC: ";
		cin.getline(cnic, '`');
		bool isFound = false;
		for (int i = 0; i < totalCustomers; i++)
		{
			if (customers[i]->getCnic().compare(cnic) == 0)
			{
				isFound = true;
				char name[50], address[100], phone[20], email[100];
				int type;
				cout << "Name: ";
				cin.getline(name, '`');
				cout << "Address: ";
				cin.getline(address, '`');
				cout << "Phone: ";
				cin.getline(phone, '`');
				cout << "Email: ";
				cin.getline(email, '`');
				cout << "Enter type: " << endl;
				cout << "1 for Silver Customer: " << endl;
				cout << "2 for Gold Customer: " << endl;
				cout << "3 for Platinum Customer: " << endl;
				cin >> type;

				if (strlen(name) == 0)
					strcpy(name, customers[i]->getName().c_str());
				if (strlen(address) == 0)
					strcpy(address, customers[i]->getAddress().c_str());
				if (strlen(phone) == 0)
					strcpy(phone, customers[i]->getPhone().c_str());
				if (strlen(email) == 0)
					strcpy(email, customers[i]->getEmail().c_str());
				cout << "Are you sure you want to update (y,n)";
				char confirm;
				cin >> confirm;
				if (confirm == 'y' || confirm == 'Y')
				{
					delete customers[i];
					switch (type)
					{
					case 1:
						customers[i] = new SilverCustomer(cnic, name, address, phone, email, 0);
						break;
					case 2:
						customers[i] = new GoldCustomer(cnic, name, address, phone, email, 0);
						break;
					case 3:
						customers[i] = new PlatinumCustomer(cnic, name, address, phone, email, 0);
						break;
					default:
						customers[i] = new SilverCustomer(cnic, name, address, phone, email, 0);
						break;
					}

					bool isUpdated = db->updateCustomer(customers, totalCustomers);
					if (isUpdated)
					{
						cout << "Customer Updated Successfully!" << endl;
						break;
					}
					else
					{
						cout << "Failed to Update Customer!" << endl;
						break;
					}
				}
				else
					cout << "Customer is not updated :)" << endl;
			}
		}

		if (!isFound)
			cout << "Customer not found!" << endl;

		system("pause");
	}

	void findCustomer()
	{
		char cnic[20], name[30], address[100], phone[20], email[100];
		cin.ignore();
		cout << "Enter CNIC: ";
		cin.getline(cnic, '`');
		cout << "Enter Name: ";
		cin.getline(name, '`');
		cout << "Enter Address";
		cin.getline(address, '`');
		cout << "Enter Phone: ";
		cin.getline(phone, '`');
		cout << "Enter Email: ";
		cin.getline(email, '`');
		bool isFound = false;
		cout << "------------------------------------------------------------" << endl;
		cout << "CNIC\tName\tEmail\tPhone\tSales Limit" << endl;
		cout << "------------------------------------------------------------" << endl;
		for (int i = 0; i < totalCustomers; i++)
		{
			if (customers[i]->getCnic().compare(cnic) == 0 || customers[i]->getName().compare(name) == 0 || customers[i]->getPhone().compare(phone) == 0 || customers[i]->getEmail().compare(email) == 0)
			{
				isFound = true;
				cout << customers[i]->getCnic() << "\t" << customers[i]->getName() << "\t" << customers[i]->getEmail() << "\t" << customers[i]->getPhone() << "\t" << customers[i]->getSalesLimit() << endl;
				cout << "------------------------------------------------------------" << endl;
			}
		}
		if (!isFound)
			cout << "No Customer Found!" << endl;

		system("pause");
	}

	void deleteCustomer()
	{
		char cnic[30];
		cin.ignore();
		cout << "Enter CNIC: ";
		cin.getline(cnic, '`');
		bool isFound = false;
		for (int i = 0; i < totalCustomers; i++)
		{
			if (customers[i]->getCnic().compare(cnic) == 0)
			{
				isFound = true;
				cout << "Are you sure you want to delete (y,n)";
				char confirm;
				cin >> confirm;
				if (confirm == 'y' || confirm == 'Y')
				{
					bool isDeleted = db->deleteCustomer(customers, totalCustomers, i);
					if (isDeleted)
					{
						delete[] customers;
						customers = db->loadCustomers(totalCustomers);
						cout << "Customer Deleted successfully!" << endl;
					}
					else
						cout << "Error Deleting Customer!" << endl;
				}
			}
		}
		if (!isFound)
			cout << "Customer not found!" << endl;

		system("pause");
	}

	void manageSales()
	{
		int lineNo = 0;
		int salesId = db->getSalesID();
		char cnic[30];
		SalesLineItem **salesLineItems = new SalesLineItem *[100];
		string date = utils->getCurrentDate();
		cout << "Sales ID: " << salesId << endl;
		cout << "Sales Date: " << date << endl;
		cout << "Enter CNIC: ";
		cin.ignore();
		cin.getline(cnic, '`');
		int found = false;
		for (int i = 0; i < totalCustomers; i++)
			if (customers[i]->getCnic().compare(cnic) == 0)
				found = true;

		if (found)
		{
			newSale(salesLineItems, salesId, lineNo, cnic);

			bool show = true;

			int total = 0;
			bool exceed = false;
			while (show)
			{
				cout << "Press 1 to enter new item: " << endl;
				cout << "Press 2 to end sale: " << endl;
				cout << "Press 3 to remove existing item from current sale: " << endl;
				cout << "Press 4 to cancel sale: " << endl;
				int choice;
				cin >> choice;
				switch (choice)
				{
				case 1:
					newSale(salesLineItems, salesId, lineNo, cnic);
					//cin.ignore();
					break;
				case 2:
					total = 0;
					for (int i = 0; i < lineNo; i++)
					{
						total += salesLineItems[i]->getItem()->getPrice() * salesLineItems[i]->getQuantity();
					}
					exceed = false;
					for (int i = 0; i < totalCustomers; i++)
						if (customers[i]->getCnic().compare(cnic) == 0)
						{
							switch (customers[i]->getType())
							{
							case 1:
								if (total > 40000)
									exceed = true;
								break;
							case 2:
								if (total > 100000)
									exceed = true;
								break;
							case 3:
								if (total > 250000)
									exceed = true;
								break;
							}
						}
					if (!exceed)
					{
						endSale(salesLineItems, salesId, lineNo, cnic, date);
						if (sales != nullptr)
						{
							delete[] sales;
							sales = db->loadSales(totalSales);
						}
						cout << "Sales Ended Successfully!" << endl;
						system("pause");
						show = false;
					}
					else
					{
						cout << "Your Total Sales exceed the limit!" << endl;
					}
					break;
				case 3:
					removeSaleItem(salesLineItems, lineNo);
					break;
				case 4:
					if (salesLineItems != nullptr)
					{
						delete[] salesLineItems;
						show = false;
					}
					break;
				default:
					show = false;
				}
			}
		}
		else
		{
			cout << "Customer Not Found!" << endl;
			system("pause");
		}
	}

	void endSale(SalesLineItem **&salesLineItems, int salesId, int totalLines, string cnic, string date)
	{
		Sales *sales = new Sales(salesId, cnic, salesLineItems, totalLines, utils->getCurrentDate(), "ACTIVE");
		db->insertSales(sales);

		for (int i = 0; i < totalLines; i++)
		{
			db->insertSaleLines(salesLineItems[i]);
		}
		Customer *customer = nullptr;
		for (int i = 0; i < totalCustomers; i++)
			if (customers[i]->getCnic().compare(cnic) == 0)
				customer = customers[i];

		cout << endl
			 << endl;
		cout << "--------------------------------------------------------------------" << endl;
		cout << "Sales ID: " << salesId << "\tCNIC: " << cnic << endl;
		cout << "Sales Date: " << date << "\tName: " << customer->getName() << endl;
		cout << "Type: ";
		if (customer->getType() == 1)
			cout << "Silver Customer" << endl;
		else if (customer->getType() == 2)
			cout << "Gold Customer" << endl;
		else
			cout << "Platinum Customer" << endl;

		cout << "--------------------------------------------------------------------" << endl;
		cout << "Item SKU\tDescription\tQuantity\tAmount" << endl;
		cout << "--------------------------------------------------------------------" << endl;
		for (int i = 0; i < totalLines; i++)
		{
			cout << salesLineItems[i]->getItem()->getItemSku() << "\t" << salesLineItems[i]->getItem()->getDescription() << "\t" << salesLineItems[i]->getQuantity() << "\t" << salesLineItems[i]->getItem()->getPrice() << endl;
		}
		cout << "--------------------------------------------------------------------" << endl;
		int total = 0;
		for (int i = 0; i < totalLines; i++)
		{
			total += salesLineItems[i]->getItem()->getPrice() * salesLineItems[i]->getQuantity();
		}
		cout << "\t\t\t\tTotal Sales: " << total << endl;
		cout << "--------------------------------------------------------------------" << endl;
		if (receipts != nullptr)
			delete[] receipts;
		receipts = db->loadReceipts(totalReceipts);
	}

	void newSale(SalesLineItem **&salesLineItems, int &salesId, int &lineNo, string cnic)
	{
		cin.ignore();
		char itemSku[50];
		cout << "Item SKU: ";
		cin.getline(itemSku, '`');
		int quantity;
		bool ItemFound = false;
		for (int j = 0; j < totalItems; j++)
		{
			if (items[j]->getItemSku().compare(itemSku) == 0)
			{
				ItemFound = true;
				cout << "Description: " << items[j]->getDescription() << endl;
				cout << "Price: Rs." << items[j]->getPrice() << endl;
				cout << "Quantity: ";
				cin >> quantity;
				while (quantity > items[j]->getQuantity())
				{
					cout << quantity << " is not available, Available quantity is: " << items[j]->getQuantity() << endl;
					cout << "Quantity: ";
					cin >> quantity;
				}
				cout << "Sub-Total: " << (items[j]->getPrice() * quantity) << endl;
				salesLineItems[lineNo] = new SalesLineItem(lineNo, salesId, new Item(items[j]), quantity);
				lineNo++;
				j = totalItems + 10;
			}
		}
		if (!ItemFound)
		{
			cout << "Item not Found!" << endl;
		}
		system("pause");
	}

	void removeSaleItem(SalesLineItem **&salesLineItems, int &lineNo)
	{
		int line;
		cout << "Line no: ";
		cin >> line;

		if (line < lineNo)
		{
			SalesLineItem **items = new SalesLineItem *[lineNo - 1];
			int index = 0;
			for (int i = 0; i < lineNo; i++)
			{
				if (i != line)
				{
					items[index] = salesLineItems[i];
				}
			}
			delete[] salesLineItems;
			salesLineItems = items;
			lineNo--;
			cout << "Item removed Successfully" << endl;
		}
		else
		{
			cout << "Line No exceed total Items" << endl;
		}
	}

	void makePayment()
	{
		int salesID;
		cout << "Sales ID: ";
		cin >> salesID;
		string name;
		string cnic;
		int amountToBePayed;
		int amountPayable;
		for (int i = 0; i < totalSales; i++)
		{
			if (sales[i]->getSalesId() == salesID)
			{
				//Receipt* receipt = nullptr;
				//for(int j=0; j<totalReceipts; j++) {
				//if(sales[i]->getSalesId() == receipts[j]->getSales()->getSalesId()) {
				//receipt = receipts[j];
				//break;
				//}
				//}
				for (int j = 0; j < totalCustomers; j++)
				{
					if (customers[j]->getCnic().compare(sales[i]->getCnic()) == 0)
					{

						cnic = customers[j]->getCnic();
						name = customers[j]->getName();
						amountPayable = customers[j]->getAmountPayable();
						break;
					}
				}
				int total = 0;

				for (int j = 0; j < sales[i]->getTotalItems(); j++)
				{
					total += (sales[i]->getSalesLineItems()[j]->getItem()->getPrice()) * (sales[i]->getSalesLineItems()[j]->getQuantity());
				}

				cout << "CNIC: " << cnic << endl;
				cout << "Name: " << name << endl;
				cout << "Total Sales Amount: " << total << endl;
				
				cout << "Amount Paid: 0"<<endl;
				cout << "Amount to be paid: " << total<<endl;
				cout << "Enter Amount: ";
				cin >> amountToBePayed;
				int receiptNo = db->getReceiptNo();
				Receipt *receipt = new Receipt(receiptNo, utils->getCurrentDate(), sales[i], total);

				if (db->insertReceipt(receipt))
				{
					cout << "Receipt Generated Successfully!" << endl;
				}
				else
				{
					cout << "Unable to store Receipt to Database!" << endl;
				}
				system("pause");
				break;
			}
		}
	}
};