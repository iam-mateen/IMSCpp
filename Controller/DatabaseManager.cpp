#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "../Model/Item.cpp"
#include "../Model/Customer.cpp"
#include "../utils/Utils.cpp"
#include "../Model/Sales.cpp"

using namespace std;

/**
 * Database Manager is a Layer between POS and Database(Files).
 * This file is responsible for all the operations on Database(Files)
 * Its only function is to receive data and perform operatons on database
 * accordingly.
 **/

class DatabaseManager
{
private:
    Util *utils;
    ofstream itemsOut, customerOut, salesOut, salesLineOut, recOut;
    ifstream itemsIn, customerIn, salesIn, salesLineIn, recIn;

public:
    DatabaseManager()
    {
        utils = new Util();
    }

    ~DatabaseManager()
    {
        if (utils != nullptr)
            delete utils;
    }

    bool insertItem(Item *&item)
    {
        itemsOut.open("database/Items.txt", ios::app);
        if (!itemsOut.is_open())
            return false;

        string data = item->toString();
        itemsOut << data.c_str();
        itemsOut.close();
        return true;
    }

    Item **loadItems(int &size)
    {
        itemsIn.open("database/Items.txt");
        if (!itemsIn.is_open())
            return nullptr;

        int totalItem = 0;
        char ch = itemsIn.get();
        while (!itemsIn.eof())
        {
            if (ch == '\n')
                totalItem++;
            ch = itemsIn.get();
        }
        Item **items = new Item *[totalItem];

        itemsIn.clear();
        itemsIn.seekg(0, ios::beg);
        int itemNo = 0;
        for (string line; getline(itemsIn, line); itemNo++)
        {
            string *itemData = utils->splitString(line, ';');
            items[itemNo] = new Item(itemData[0], itemData[1], stoi(itemData[2]), stoi(itemData[3]), itemData[4]);
        }
        size = totalItem;
        itemsIn.close();
        return items;
    };

    bool updateItem(Item **&items, int size)
    {
        itemsOut.open("database/Items.txt");
        if (!itemsOut.is_open())
            return false;
        for (int i = 0; i < size; i++)
        {
            string data = items[i]->toString();
            itemsOut << data.c_str();
        }
        itemsOut.close();
        return true;
    }

    bool deleteItem(Item **&items, int size, int index)
    {
        itemsOut.open("database/Items.txt");
        if (!itemsOut.is_open())
            return false;
        for (int i = 0; i < size; i++)
        {
            if (i != index)
            {
                string data = items[i]->toString();
                itemsOut << data.c_str();
            }
        }
        itemsOut.close();
        return true;
    }

    bool insertCustomer(Customer *&customer)
    {
        customerOut.open("database/Customers.txt", ios::app);
        if (!customerOut.is_open())
            return false;

        string data = customer->toString();
        customerOut << data.c_str();
        customerOut.close();
        return true;
    }

    Customer **loadCustomers(int &size)
    {
        customerIn.open("database/Customers.txt");
        if (!customerIn.is_open())
            return nullptr;

        int totalCustomers = 0;
        char ch = customerIn.get();
        while (!customerIn.eof())
        {
            if (ch == '\n')
                totalCustomers++;
            ch = customerIn.get();
        }

        Customer **customers = new Customer *[totalCustomers];

        customerIn.clear();
        customerIn.seekg(0, ios::beg);
        int customerNo = 0;
        for (string line; getline(customerIn, line);)
        {
            string *customerData = utils->splitString(line, ';');
            int type = stoi(customerData[5]);
            switch (type)
            {
            case 1:
                customers[customerNo] = new SilverCustomer(customerData[0], customerData[1], customerData[2], customerData[3], customerData[4], stoi(customerData[6]));
                break;
            case 2:
                customers[customerNo] = new GoldCustomer(customerData[0], customerData[1], customerData[2], customerData[3], customerData[4], stoi(customerData[6]));
                break;
            case 3:
                customers[customerNo] = new PlatinumCustomer(customerData[0], customerData[1], customerData[2], customerData[3], customerData[4], stoi(customerData[6]));
                break;
            default:
                customers[customerNo] = new SilverCustomer(customerData[0], customerData[1], customerData[2], customerData[3], customerData[4], stoi(customerData[6]));
            }
            customerNo++;
        }
        size = totalCustomers;
        customerIn.close();
        return customers;
    }

    bool updateCustomer(Customer **&customers, int size)
    {
        customerOut.open("database/Customers.txt");
        if (!customerOut.is_open())
            return false;
        for (int i = 0; i < size; i++)
        {
            string data = customers[i]->toString();
            customerOut << data.c_str();
        }
        customerOut.close();
        return true;
    }

    bool deleteCustomer(Customer **&customers, int size, int index)
    {
        customerOut.open("database/Customers.txt");
        if (!customerOut.is_open())
            return false;

        for (int i = 0; i < size; i++)
        {
            if (i != index)
            {
                string data = customers[i]->toString();
                customerOut << data.c_str();
            }
        }
        customerOut.close();
        return true;
    }

    bool insertSales(Sales *&sales)
    {
        salesOut.open("database/Sales.txt", ios::app);
        if (!salesOut.is_open())
            return false;

        string data = sales->toString();
        salesOut << data.c_str();
        salesOut.close();
        return true;
    }

    bool insertReceipt(Receipt *&receipt)
    {
        recOut.open("database/Receipt.txt", ios::app);
        if (!recOut.is_open())
            return false;

        string data = receipt->toString();
        recOut << data.c_str();
        recOut.close();
        return true;
    }

    bool insertSaleLines(SalesLineItem *&line)
    {
        salesLineOut.open("database/SalesLineItem.txt", ios::app);
        if (!salesLineOut.is_open())
            return false;

        string data = line->toString();
        salesLineOut << data.c_str();
        salesLineOut.close();
        return true;
    }

    Sales **loadSales(int &size)
    {
        salesIn.open("database/Sales.txt");
        if (!salesIn.is_open())
            return nullptr;

        int totalItem = 0;
        char ch = salesIn.get();
        while (!salesIn.eof())
        {
            if (ch == '\n')
                totalItem++;
            ch = salesIn.get();
        }
        Sales **items = new Sales *[totalItem];

        salesIn.clear();
        salesIn.seekg(0, ios::beg);
        int itemNo = 0;
        for (string line; getline(salesIn, line);)
        {
            string *itemData = utils->splitString(line, ';');
            int totalLines = 0;
            SalesLineItem **lines = loadLineItems(totalLines, stoi(itemData[0]));
            //cout << "SALES"<<endl;
            items[itemNo] = new Sales(stoi(itemData[0]), itemData[1], lines, totalLines, itemData[3], itemData[4]);
            itemNo++;
        }
        size = totalItem;
        salesIn.close();
        return items;
    }

    SalesLineItem **loadLineItems(int &size, int salesID)
    {
        salesLineIn.open("database/SalesLineItem.txt");
        if (!salesLineIn.is_open())
            return nullptr;

        int totalItem = 0;
        char ch = salesLineIn.get();

        while (!salesLineIn.eof())
        {
            if (ch == '\n')
                totalItem++;
            ch = salesLineIn.get();
        }
        SalesLineItem **items = new SalesLineItem *[totalItem];

        salesLineIn.clear();
        salesLineIn.seekg(0, ios::beg);
        int itemNo = 0;
        int totalLines = 0;
        for (string line; getline(salesLineIn, line);)
        {
            string *itemData = utils->splitString(line, ';');
            if (stoi(itemData[1]) == salesID)
            {
                Item *item = loadSingleItem(itemData[2]);
                //cout << item->toString() <<endl<<endl<<endl;
                items[itemNo] = new SalesLineItem(stoi(itemData[0]), stoi(itemData[1]), item, stoi(itemData[3]));
                totalLines++;
            }
            itemNo++;
        }
        size = totalLines;
        salesLineIn.close();
        return items;
    }

    Item *loadSingleItem(string sku)
    {
        itemsIn.open("database/Items.txt");
        if (!itemsIn.is_open())
            return nullptr;

        int totalItem = 0;
        char ch = itemsIn.get();
        while (!itemsIn.eof())
        {
            if (ch == '\n')
                totalItem++;
            ch = itemsIn.get();
        }
        Item **items = new Item *[totalItem];

        itemsIn.clear();
        itemsIn.seekg(0, ios::beg);
        int itemNo = 0;
        for (string line; getline(itemsIn, line); itemNo++)
        {
            string *itemData = utils->splitString(line, ';');
            items[itemNo] = new Item(itemData[0], itemData[1], stoi(itemData[2]), stoi(itemData[3]), itemData[4]);
        }
        //size = totalItem;
        itemsIn.close();
        Item *item;
        for (int i = 0; i < totalItem; i++)
        {
            if (items[i]->getItemSku().compare(sku) == 0)
            {
                item = items[i];
                break;
            }
        }
        return item;
    }

    int getSalesID()
    {
        salesIn.open("database/Sales.txt");
        if (!salesIn.is_open())
            return 0;

        int totalItem = 0;
        char ch = salesIn.get();
        while (!salesIn.eof())
        {
            if (ch == '\n')
                totalItem++;
            ch = salesIn.get();
        }
        return totalItem;
    }

    int getReceiptNo()
    {
        recIn.open("database/Receipt.txt");
        if (!recIn.is_open())
            return 0;

        int totalItem = 0;
        char ch = recIn.get();
        while (!recIn.eof())
        {
            if (ch == '\n')
                totalItem++;
            ch = recIn.get();
        }
        return totalItem;
    }

    Receipt **loadReceipts(int &size)
    {
        recIn.open("database/Receipt.txt");
        if (!recIn.is_open())
            return nullptr;

        int totalItem = 0;
        char ch = recIn.get();
        while (!recIn.eof())
        {
            if (ch == '\n')
                totalItem++;
            ch = recIn.get();
        }
        Receipt **items = new Receipt *[totalItem];

        recIn.clear();
        recIn.seekg(0, ios::beg);
        int itemNo = 0;
        int totalSales;
        Sales **sales = loadSales(totalSales);
        for (string line; getline(recIn, line);)
        {
            Sales *sale = nullptr;
            string *itemData = utils->splitString(line, ';');
            for (int i = 0; i < totalSales; i++)
            {
                if (sales[i]->getSalesId() == stoi(itemData[2]))
                {
                    sale = sales[i];
                    break;
                }
            }
            items[itemNo] = new Receipt(stoi(itemData[0]), itemData[1], sale, stoi(itemData[3]));
            itemNo++;
        }
        delete[] sales;
        size = totalItem;
        recIn.close();
        return items;
    }
};