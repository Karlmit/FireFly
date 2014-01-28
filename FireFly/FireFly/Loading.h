#pragma once
#include <SFML/Graphics.hpp>

class Loading
{
public:
	static Loading &getLoading();
	void loadplayer();
	sf::Texture getplayer(){return player;}

private:
	Loading();
	~Loading();
	void operator=(const Loading &loading);
	static Loading loading;
	sf::Texture player;

};