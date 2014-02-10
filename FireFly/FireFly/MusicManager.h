#pragma once

#include <memory>
#include <string>
#include <map>
#include <SFML\Audio\Music.hpp>

using namespace std;

class MusicManager : public sf::NonCopyable
{
public:
	static void newManager();
	static void update(sf::Time dt);
	static void addMusic(string filePath, int id);
	static void play(int id);
	static void playAll();
	static void fadeDown(int id);
	static void fadeUp(int id);
	static void fadeToggle(int id);

private:
	static unique_ptr<MusicManager> instance;

public:
	MusicManager();
	~MusicManager();

private:


private:
	map<int, unique_ptr<sf::Music>> mMusicsMap;
	map<int, bool> mFadeUpMap;

};