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
	static void addMusic(string filePath, string id);
	static void play(string id);
	static void playAll();
	static void fadeDown(string id);
	static void fadeUp(string id);
	static void fadeToggle(string id);

private:
	static unique_ptr<MusicManager> instance;

public:
	MusicManager();
	~MusicManager();

private:


private:
	map<string, unique_ptr<sf::Music>> mMusicsMap;
	map<string, bool> mFadeUpMap;

};