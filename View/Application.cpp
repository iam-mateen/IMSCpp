#include <iostream>
#include <Windows.h>
#include "../Controller/POS.cpp"

using namespace std;
/** 
 * Application is  an abstraction layer between User and POS.
 * This file is responsible to display menus on screen.
 * Bascially this is a user interface and by using this Interface.cpp
 * we get the functionality of Abstraction i.e interface is seperate from 
 * Business Logic.
*/
class Application
{
private:
	bool displaying;
	POS *pos;
	int mainMenu()
	{
		system("cls");
		cout << "<-------------------------------- MAIN MENU --------------------------------------->" << endl
			 << endl;
		cout << "1- Manage Items" << endl;
		cout << "2- Manage Customers" << endl;
		cout << "3- Make New Sale" << endl;
		cout << "4- Make Payment" << endl;
		cout << "5- Exit" << endl;
		int input;
		cin >> input;

		return input;
	}

	int itemsManu()
	{
		bool show = true;
		while (show)
		{
			system("cls");
			cout << "<-------------------------------- MANAGE ITEMS MENU --------------------------------------->" << endl
				 << endl;
			cout << "1- Add new Item" << endl;
			cout << "2- Update Item Details" << endl;
			cout << "3- Find Items" << endl;
			cout << "4- Remove Existing Item" << endl;
			cout << "5- Back to Main Menu" << endl;
			int input;
			cin >> input;
			switch (input)
			{
			case 1:
				pos->addNewItem();
				break;
			case 2:
				pos->updateItem();
				break;
			case 3:
				pos->findItem();
				break;
			case 4:
				pos->deleteItem();
				break;
			case 5:
				show = false;
				break;
			}
		}
		return 0;
	}

	int customersMenu()
	{
		bool show = true;
		while (show)
		{
			system("cls");
			cout << "<-------------------------------- CUSTOMERS MENU --------------------------------------->" << endl
				 << endl;
			cout << "1- Add new Customer" << endl;
			cout << "2- Update Customer Details" << endl;
			cout << "3- Find Customers" << endl;
			cout << "4- Remove Existing Customer" << endl;
			cout << "5- Back to Main Menu" << endl;
			int input;
			cin >> input;
			switch (input)
			{
			case 1:
				pos->addNewCustomer();
				break;
			case 2:
				pos->updateCustomer();
				break;
			case 3:
				pos->findCustomer();
				break;
			case 4:
				pos->deleteCustomer();
				break;
			case 5:
				show = false;
				break;
			}
		}

		return 0;
	}

	int salesMenu()
	{
		system("cls");
		cout << "<-------------------------------- MAKE NEW SALE MENU --------------------------------------->" << endl
			 << endl;
		pos->manageSales();
		return 0;
	}

	int paymentsMenu()
	{
		system("cls");
		cout << "<-------------------------------- MAKE NEW PAYMENT MENU --------------------------------------->" << endl
			 << endl;
		pos->makePayment();
		return 0;
	}

public:
	Application()
	{
		displaying = true;
		pos = new POS();
	}

	void start()
	{
		int input = 0;
		while (displaying == true)
		{
			switch (input)
			{
			case 1:
				input = itemsManu();
				break;
			case 2:
				input = customersMenu();
				break;
			case 3:
				input = salesMenu();
				break;
			case 4:
				input = paymentsMenu();
				break;
			case 5:
				delete pos;
				displaying = false;
				break;
			default:
				input = mainMenu();
			}
		}
	}

	
};