#pragma once

#include <memory>
#include <string>
using namespace std;

class MusicManager
{
public:
	static void newManager();
	static void addMusic(string filePath, int id);
	static void playMusic(int id);
	static void playAll();
	static void fadeDown(int id);
	static void fadeUp(int id);

private:
	static unique_ptr<MusicManager> instance;

public:
	MusicManager();
	~MusicManager();

private:
	

};