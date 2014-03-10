#pragma once

#include <iostream>
using namespace std;

class Log
{
public:
	static void init();
	static void write(string str);

private:

	static string mFilename;

};