#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>

using namespace std;
/** 
 * This file contains all the utility functions to perform specific operations
*/
class Util
{
public:
    string getCurrentDate()
    {
        time_t rawtime;
        struct tm *timeinfo;
        char buffer[80];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);
        string str(buffer);
        return str;
    }

    string *splitString(string data, char delimiter)
    {
        string *splitted = new string[data.length()];
        int index = 0;
        string temp;
        for (int i = 0; i < data.length(); i++)
        {
            if (data[i] == delimiter)
            {
                *(splitted + index) = string(temp);
                index++;
                temp = "";
            }
            else
                temp += data[i];
        }

        return splitted;
    }
};