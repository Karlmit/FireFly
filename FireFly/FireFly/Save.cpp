#include "Save.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>

#include <Windows.h>

void Save::init()
{
	wchar_t* dir = L"data";
	CreateDirectory(dir, NULL);
}

void Save::writeLevel(string level)
{
	ofstream myfile;
	myfile.open ("data\\save.txt", ios::out | ios::trunc );
	myfile << level << endl;
	myfile.close();
}


string Save::readLevel()
{
	string line;
	ifstream myfile ("data\\save.txt");
	if (myfile.is_open())
	{
		getline(myfile,line);
		myfile.close();
		return line;
	}
	else
		return string();

}
