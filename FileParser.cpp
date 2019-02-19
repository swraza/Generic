// FileParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<fstream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	auto delimeter = ";";
	std::ifstream inputStream("E:\\Usman & Mujtaba NUML Project\\FileParser\\Debug\\Input.txt");
	std::ofstream outputStream("E:\\Usman & Mujtaba NUML Project\\FileParser\\Debug\\Output.txt");
	std::string strTemp, completeLine;
	int lineNum = 0;
	while (std::getline(inputStream, strTemp))
	{
		if (lineNum == 0) // Job Title
		{
			completeLine += strTemp + delimeter;
		}
		else if (lineNum == 1) // Company/Organization Name
		{
			completeLine += strTemp + delimeter;
		}
		else if (lineNum == 2 || lineNum == 4 || lineNum == 6 || lineNum == 8) // Job Type Text, Job Shift Text, Experiance Text, Salary Text
		{
			lineNum++;
			continue;
		}
		else if (lineNum == 3) // Job Type
		{
			completeLine += strTemp + delimeter;
		}
		else if (lineNum == 5) // Job Shift
		{
			completeLine += strTemp + delimeter;
		}
		else if (lineNum == 7) // Experience
		{
			completeLine += strTemp + delimeter;
		}
		else if (lineNum == 9) // Salary Range
		{
			// Note that salary is listed in a range like 40,000 - 70,000 PKR . Here we need to do following things
			// 1 Split into min and max salary
			// 2 get rid of commas so it does not confuse with our column separator.
			// 3 get the currency symbol which is PKR in the above example.
			// and most importantly, do check if we get something for salary as there are cases where salary information is not given.
			if (strTemp.length() > 0)
			{
				auto firstSpace = strTemp.find(" ", 0);
				auto lastSpace = strTemp.find(" ", firstSpace + 3);
				auto minSal = strTemp.substr(0, firstSpace);
				auto maxSal = strTemp.substr(firstSpace+3, lastSpace - (firstSpace +3));
				minSal.erase(std::remove(minSal.begin(), minSal.end(), ','), minSal.end());
				maxSal.erase(std::remove(maxSal.begin(), maxSal.end(), ','), maxSal.end());
				completeLine += minSal + delimeter;
				completeLine += maxSal + delimeter;
				auto currency = strTemp.substr(strTemp.length()-3, 3);
				completeLine += currency + delimeter;
			}
		}
		else if (lineNum == 10) // Job Description
		{
			completeLine += strTemp + delimeter;
		}
		else if (lineNum == 11) // Locations and Date
		{
			//This is tricky. We need to find out how many locations a job is posted to.
			// Lets first get the date separate out
			auto pakEndIndex = strTemp.find("Pakistan", 0)+8;
			auto date = strTemp.substr(pakEndIndex, strTemp.length()- pakEndIndex);
			auto noOfLocations = std::count(strTemp.begin(), strTemp.end(), ',') - 1; // -1 as one comma is in the date
			// now for every location we need to enter the whole row.
			auto startIndex = 0;
			for (int i = 0; i < noOfLocations; i++)
			{
				auto tempLine = completeLine;
				auto commaIndex = strTemp.find(",", startIndex);
				auto location = strTemp.substr(startIndex, commaIndex - startIndex);
				tempLine += location + delimeter;
				tempLine += date;
				tempLine += "\r"; //New line char
				outputStream << tempLine;
				// update the start index to find next comma index /location
				startIndex = commaIndex + 1;
			}
			completeLine = "";
			lineNum = -1;
		}
		lineNum++;
	}
}


