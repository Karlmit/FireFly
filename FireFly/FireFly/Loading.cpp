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

void Loading::loadplayer()
{
	player.loadFromFile("Resources/zid.png");
}