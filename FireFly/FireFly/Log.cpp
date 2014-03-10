#include "Log.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>

#include <sstream>
#include <string>

#include <ostream>
#include <fstream>

#include <Windows.h>

string Log::mFilename;

std::string currentDateTimeForFileName() {
	

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    //tstruct = *localtime_s(&now);

	//struct tm tstruct;
	localtime_s(&tstruct, &now);

    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d %H.%M", &tstruct); 

	
	stringstream ss;
	ss << buf;
	string s;	
	ss >> s;

	s = ss.str();

    return s;
}

std::string currentDateTime() {
	

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    //tstruct = *localtime_s(&now);

	//struct tm tstruct;
	localtime_s(&tstruct, &now);

    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct); 

	
	stringstream ss;
	ss << buf;
	string s;	
	ss >> s;

	s = ss.str();

    return s;
}

void Log::init()
{
	Log::mFilename = "Logs/" +  currentDateTimeForFileName() + ".txt";

	wchar_t* dir = L"Logs";
	CreateDirectory(dir, NULL);
}


void Log::write(string str)
{
	std::ofstream outfile;

	outfile.open(mFilename, std::ios_base::app);
	outfile << currentDateTime() << ": " << str << endl; 
}