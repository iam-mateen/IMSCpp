#pragma once
#include <iostream>
#include "Customer.cpp"
#include "Item.cpp"

using namespace std;

class SalesLineItem;
class Receipt;

class Sales
{
private:
	int salesId;
	string cnic;
	SalesLineItem **sales;
	int totalItems;
	string date;
	string status;

public:
	Sales(int salesId, string cnic, SalesLineItem **sales, int totalItems, string date, string status)
	{
		this->salesId = salesId;
		this->cnic = cnic;
		this->sales = sales;
		this->totalItems = totalItems;
		this->date = date;
		this->status = status;
	}

	string toString()
	{
		string line = "";
		line += to_string(salesId) + ";" + cnic + ";" + to_string(totalItems) + ";" + date + ";" + status + ";\n";
		return line;
		//<SaleID><Customer><SalesLineItem><date><status>
	}

	int getSalesId()
	{
		return salesId;
	}

	string getCnic()
	{
		return cnic;
	}

	SalesLineItem **&getSalesLineItems()
	{
		return sales;
	}

	int getTotalItems()
	{
		return totalItems;
	}

	string getDate()
	{
		return date;
	}

	string getStatus()
	{
		return status;
	}

	void setSalesId(int id)
	{
		this->salesId = id;
	}

	void setCnic(string cnic)
	{
		this->cnic = cnic;
	}

	void setSalesLineItems(SalesLineItem **&lines)
	{
		this->sales = lines;
	}

	void setTotalItems(int total)
	{
		this->totalItems = total;
	}

	void setDate(string date)
	{
		this->date = date;
	}

	void setStatus(string status)
	{
		this->status = status;
	}

	~Sales()
	{
		cnic.clear();
		if (sales != nullptr)
			delete[] sales;
		date.clear();
		status.clear();
	}
};

class SalesLineItem
{
private:
	int lineNo;
	int salesID;
	Item *item;
	int quantity;

public:
	SalesLineItem(int lineNo, int salesID, Item *item, int quantity)
	{
		this->lineNo = lineNo;
		this->salesID = salesID;
		this->item = item;
		this->quantity = quantity;
	}

	string toString()
	{
		string line = "";
		line += to_string(lineNo) + ";" + to_string(salesID) + ";" + item->getItemSku() + ";" + to_string(quantity) + ";\n";
		return line;
	}

	int getLineNo()
	{
		return lineNo;
	}

	int getSalesID()
	{
		return salesID;
	}

	Item *&getItem()
	{
		return item;
	}

	int getQuantity()
	{
		return quantity;
	}

	void setLineNo(int line)
	{
		this->lineNo = line;
	}

	void setSalesID(int id)
	{
		this->salesID = id;
	}

	void setItem(Item *&item)
	{
		this->item = item;
	}

	void setQuantity(int quantity)
	{
		this->quantity = quantity;
	}

	~SalesLineItem()
	{
		if (item != nullptr)
			delete item;
	}
};

class Receipt
{
private:
	int receiptNo;
	string receiptDate;
	Sales *sales;
	int amount;

public:
	Receipt(int receiptNo, string receiptDate, Sales *sales, int amount)
	{
		this->receiptNo = receiptNo;
		this->receiptDate = receiptDate;
		this->sales = sales;
		this->amount = amount;
	}

	string toString()
	{
		string line = "";
		line += to_string(receiptNo) + ";" + receiptDate + ";" + to_string(sales->getSalesId()) + ";" + to_string(amount) + ";\n";
		return line;
	}

	int getReceiptNo()
	{
		return receiptNo;
	}

	string getReceiptDate()
	{
		return receiptDate;
	}

	Sales *&getSales()
	{
		return sales;
	}

	int getAmount()
	{
		return amount;
	}

	void setReceiptNo(int no)
	{
		this->receiptNo = no;
	}

	void setReceiptDate(string date)
	{
		this->receiptDate = date;
	}

	void setSales(Sales *&sales)
	{
		this->sales = sales;
	}

	void setAmount(int amount)
	{
		this->amount = amount;
	}

	~Receipt()
	{
		receiptDate.clear();
		if (sales != nullptr)
			delete sales;
	}
};