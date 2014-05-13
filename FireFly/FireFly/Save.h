#pragma once

#include <string>
using namespace std;

class Save
{
public:
	static void init();
	static void writeLevel(string level);
	static string readLevel();
};