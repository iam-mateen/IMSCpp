#pragma once
#include <iostream>
using namespace std;

class Item
{
private:
	string item_sku;
	string description;
	int price;
	int availableQuanitity;
	string creationDate;
public:
	
	Item(string item_sku, string description, int price, int availableQuanitity, string creationDate)
	{
		this->item_sku = item_sku;
		this->description = description;
		this->price = price;
		this->availableQuanitity = availableQuanitity;
		this->creationDate = creationDate;
	}

	Item(Item *&item)
	{
		this->item_sku = item->item_sku;
		this->description = item->description;
		this->price = item->price;
		this->availableQuanitity = item->availableQuanitity;
		this->creationDate = item->creationDate;
	}

	string toString()
	{
		string dbFormat = "";
		dbFormat += item_sku + ";" + description + ";" + to_string(price) + ";" + to_string(availableQuanitity) + ";" + creationDate + ";" + '\n';
		return dbFormat;
	}

	//Getters
	string getItemSku()
	{
		return item_sku;
	}

	string getDescription()
	{
		return description;
	}

	int getPrice()
	{
		return price;
	}

	int getQuantity()
	{
		return availableQuanitity;
	}

	string getDate()
	{
		return creationDate;
	}

	//Setters
	void setItemSku(string sku)
	{
		this->item_sku = sku;
	}

	void setDescription(string des)
	{
		this->description = des;
	}

	void setPrice(int price)
	{
		this->price = price;
	}

	void setQuantity(int quantity)
	{
		this->availableQuanitity = quantity;
	}

	void setDate(string date)
	{
		this->creationDate = date;
	}

	~Item() {
		item_sku.clear();
		description.clear();
		creationDate.clear();
	}
};