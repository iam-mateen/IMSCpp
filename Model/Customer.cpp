#pragma once
#include <iostream>
#include <string>

using namespace std;

class Customer
{
protected:
	string cnic;
	string name;
	string address;
	string phone;
	string email;
	int amountPayable;
	int salesLimit;
public:

	
	Customer(string cnic, string name, string address, string phone, string email, int amountPayable, int salesLimit)
	{
		this->cnic = cnic;
		this->name = name;
		this->address = address;
		this->phone = phone;
		this->email = email;
		this->amountPayable = amountPayable;
		this->salesLimit = salesLimit;
	}

	//Virtual Functions
	virtual float getDiscount() = 0;
	virtual int getType() = 0;
	virtual string toString() = 0;

	//Getters
	string getCnic()
	{
		return cnic;
	}

	string getName()
	{
		return name;
	}

	string getAddress()
	{
		return address;
	}

	string getPhone()
	{
		return phone;
	}

	string getEmail()
	{
		return email;
	}

	int getAmountPayable()
	{
		return amountPayable;
	}

	int getSalesLimit()
	{
		return salesLimit;
	}

	//Setters
	void setCnic(string cnic)
	{
		this->cnic = cnic;
	}

	void setName(string name)
	{
		this->name = name;
	}

	void setAddress(string address)
	{
		this->address = address;
	}

	void setPhone(string phone)
	{
		this->phone = phone;
	}

	void setEmail(string email)
	{
		this->email = email;
	}

	void setAmountPayable(int amount)
	{
		this->amountPayable = amount;
	}

	void setSalesLimit(int limit)
	{
		this->salesLimit = limit;
	}

	~Customer() {
		cnic.clear();
		name.clear();
		address.clear();
		phone.clear();
		email.clear();
	}
};

class SilverCustomer : public Customer
{
private:
	float DISCOUNT;

public:
	SilverCustomer(string cnic, string name, string address, string phone, string email, int amountPayable)
		: Customer(cnic, name, address, phone, email, amountPayable, 40000)
	{
		DISCOUNT = 0;
	};

	float getDiscount()
	{
		return DISCOUNT;
	}

	int getType()
	{
		return 1;
	}

	string toString()
	{
		string dbFormat = "";
		dbFormat += cnic + ";" + name + ";" + address + ";" + phone + ";" + email + ";" + to_string(1) + ";" + to_string(amountPayable) + ";" + to_string(salesLimit) + ";" + '\n';
		return dbFormat;
	}

	~SilverCustomer() {
		cnic.clear();
		name.clear();
		address.clear();
		phone.clear();
		email.clear();
	}
};

class GoldCustomer : public Customer
{
private:
	float DISCOUNT;

public:
	GoldCustomer(string cnic, string name, string address, string phone, string email, int amountPayable)
		: Customer(cnic, name, address, phone, email, amountPayable, 100000)
	{
		DISCOUNT = 3.0;
	};

	float getDiscount()
	{
		return DISCOUNT;
	}

	int getType()
	{
		return 2;
	}

	string toString()
	{
		string dbFormat = "";
		dbFormat += cnic + ";" + name + ";" + address + ";" + phone + ";" + email + ";" + to_string(2) + ";" + to_string(amountPayable) + ";" + to_string(salesLimit) + ";" + '\n';
		return dbFormat;
	}

	~GoldCustomer() {
		cnic.clear();
		name.clear();
		address.clear();
		phone.clear();
		email.clear();
	}

};

class PlatinumCustomer : public Customer
{
private:
	float DISCOUNT;

public:
	PlatinumCustomer(string cnic, string name, string address, string phone, string email, int amountPayable)
		: Customer(cnic, name, address, phone, email, amountPayable, 250000)
	{
		DISCOUNT = 5.0;
	};

	float getDiscount()
	{
		return DISCOUNT;
	}

	int getType()
	{
		return 3;
	}

	string toString()
	{
		string dbFormat = "";
		dbFormat += cnic + ";" + name + ";" + address + ";" + phone + ";" + email + ";" + to_string(3) + ";" + to_string(amountPayable) + ";" + to_string(salesLimit) + ";" + '\n';
		return dbFormat;
	}

	~PlatinumCustomer() {
		cnic.clear();
		name.clear();
		address.clear();
		phone.clear();
		email.clear();
	}

};