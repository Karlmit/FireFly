#include "MusicManager.h"

unique_ptr<MusicManager> MusicManager::instance = nullptr;

const float MAX_VOLUME = 30;
const float FADE_SPEED = 20;

void MusicManager::newManager()
{
	instance.reset(new MusicManager());
}

void MusicManager::update(sf::Time dt)
{
	for(auto& iter : instance->mMusicsMap) 
	{
		auto& music = (*iter.second);
		string id = iter.first;

		auto foundFade = instance->mFadeUpMap.find(id);
		bool bfadeUp = foundFade->second;
		
		if (bfadeUp && music.getVolume() < MAX_VOLUME)
		{
			float newVolume = min(music.getVolume() + dt.asSeconds()*FADE_SPEED, MAX_VOLUME);
			music.setVolume(newVolume);
		}
		else if (!bfadeUp && music.getVolume() > 0)
		{
			float newVolume = max(music.getVolume() - dt.asSeconds()*FADE_SPEED, 0.f);
			music.setVolume(newVolume);
		}
	}
}

void MusicManager::addMusic(string filePath, string id) 
{
	// Adding a new musics file
	sf::Music* music = new sf::Music();
	filePath = "Resources/Music/" + filePath;
	if (!music->openFromFile(filePath))
		throw std::runtime_error("MusicManager::addMusic - Music \"" + filePath + "\" could not be loaded.");

	// Setting default values for the music
	music->setLoop(true);
	music->setRelativeToListener(true);
	music->setVolume(0);

	// Adding the music to the map of all musics loaded
	auto uPtr = unique_ptr<sf::Music>(music);
	instance->mMusicsMap.insert(make_pair(id, std::move(uPtr)));

	// Adds a fade element for the id
	instance->mFadeUpMap.insert(make_pair(id, false));
}

void MusicManager::play(string id)
{
	auto found = instance->mMusicsMap.find(id);
	
	if (found == instance->mMusicsMap.end())
		throw std::runtime_error("MusicManager::play - Music with the id=" + id + " could not be played");

	(*found->second).play();	
}

void MusicManager::playAll() 
{
	for(auto& iter : instance->mMusicsMap) 
	{
		(*iter.second).play();
	}
}

void MusicManager::fadeDown(string id) 
{
	auto found = instance->mFadeUpMap.find(id);

	if (found == instance->mFadeUpMap.end())
		throw std::runtime_error("MusicManager::fadeDown - Music with the id=" + id + " could not be faded");

	found->second = false;
}

void MusicManager::fadeUp(string id) 
{
	auto found = instance->mFadeUpMap.find(id);

	if (found == instance->mFadeUpMap.end())
		throw std::runtime_error("MusicManager::fadeUp - Music with the id=" + id + " could not be faded");

	found->second = true;
}

void MusicManager::fadeToggle(string id) 
{
	auto found = instance->mFadeUpMap.find(id);

	if (found == instance->mFadeUpMap.end())
		throw std::runtime_error("MusicManager::fadeToggle - Music with the id=" + id + " could not be faded");

	found->second = !found->second;
}

MusicManager::MusicManager()
	:mMusicsMap()
{
}

MusicManager::~MusicManager()
{
}