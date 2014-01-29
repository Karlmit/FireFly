#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Audio\SoundBuffer.hpp>

class Loading
{
public:
	static Loading &getLoading();
	void loadLevel0();
	sf::Texture getplayer(){return player;}
	sf::SoundBuffer getFlySound(){return fly;}
	sf::Texture getMothTexture(){return mothTexture;}
	sf::SoundBuffer getMothBuffer(){return mothBuffer;}

private:
	Loading();
	~Loading();
	void operator=(const Loading &loading);
	static Loading loading;
	sf::Texture player;
	sf::Texture mothTexture;
	sf::SoundBuffer mothBuffer;
	sf::SoundBuffer fly;
};