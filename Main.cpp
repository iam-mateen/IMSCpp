#include <iostream>
#include <windows.h>
#include "View/Application.cpp"

using namespace std;

void welcome(string text)
{
	system("cls");
	for (int i = 0; i < text.length(); i++)
	{
		cout << text[i];
		Sleep(50);
	}
	Sleep(1000);
}

int main()
{
	const string APP_USER = "admin";
	const string APP_PASS = "admin";
	
	cout << "Please Enter Login Credentials." << endl;
	string username, password;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;

	if (username.compare(APP_USER) == 0 && password.compare(APP_PASS) == 0)
	{
		welcome("Welcome ADMIN :))");
		Application application;
		application.start();
	}
	else
		cout << "Incorrect Username and Password!" << endl;

	return EXIT_SUCCESS;
}