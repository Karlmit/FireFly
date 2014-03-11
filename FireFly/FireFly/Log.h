#pragma once

#include <iostream>
using namespace std;

class Log
{
public:
	static void init();
	static void write(string str, bool repeatMessage = false);

private:

	static string mFilename;
	static string mLastMessage;
};