// FileParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<fstream>
#include <string>

using namespace std;

int main()
{
	std::ifstream inputStream("D:\\Playground\\wraza\\FileParser\\Debug\\Input.txt");
	std::ofstream outputStream("D:\\Playground\\wraza\\FileParser\\Debug\\Output.txt");
	std::string strTemp, completeLine;
	bool lineCompleted = false;
	int lineNum = 0;
	while (std::getline(inputStream, strTemp))
	{
		if (lineNum == 0) // Job Title
		{
			completeLine += strTemp + ",";
		}
		else if (lineNum == 1) // Company/Organization Name
		{
			completeLine += strTemp + ",";
		}
		else if (lineNum == 2 || lineNum == 4 || lineNum == 6 || lineNum == 8) // Job Type Text, Job Shift Text, Experiance Text, Salary Text
		{
			lineNum++;
			continue;
		}
		else if (lineNum == 3) // Job Type
		{
			completeLine += strTemp + ",";
		}
		else if (lineNum == 5) // Job Shift
		{
			completeLine += strTemp + ",";
		}
		else if (lineNum == 7) // Experience
		{
			completeLine += strTemp + ",";
		}
		else if (lineNum == 9) // Salary Range
		{
			completeLine += strTemp + ",";
		}
		else if (lineNum == 10) // Job Description
		{
			completeLine += strTemp + ",";
		}
		else if (lineNum == 11) // Locations and Date
		{
			completeLine += strTemp;
			lineCompleted = true;
		}

		if (lineCompleted)
		{
			completeLine += "\r"; //New line char
			outputStream << completeLine;
			completeLine = "";
			lineNum = -1;
			lineCompleted = false;
		}
		lineNum++;
	}
}


