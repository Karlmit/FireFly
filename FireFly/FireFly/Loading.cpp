#include "Loading.h"

Loading Loading::loading;

Loading::Loading()
{
}

Loading::~Loading()
{
}

Loading &Loading::getLoading()
{
	return loading;
}

void Loading::loadLevel0()
{
	player.loadFromFile("Resources/zid.png");
	fly.loadFromFile("Resources/canary.wav");
	
	mothTexture.loadFromFile("Resources/mal.png");
}