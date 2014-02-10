#include "MusicManager.h"

unique_ptr<MusicManager> MusicManager::instance = nullptr;

void MusicManager::newManager()
{
	instance.reset(new MusicManager());
}

void MusicManager::addMusic(string filePath, int id) 
{}

void MusicManager::playMusic(int id)
{}

void MusicManager::playAll() 
{}

void MusicManager::fadeDown(int id) 
{}

void MusicManager::fadeUp(int id) 
{}

