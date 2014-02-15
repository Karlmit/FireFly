#pragma once

#include "LTBL\Light\LightSystem.h"
#include "LTBL\Light\Light_Point.h"
#include "LTBL\Utils.h"
#include <memory>

class LightManager {

public:
	static void setWindow(sf::RenderWindow* window);
	static void newLightSystem(sf::FloatRect bounds);
	static ltbl::LightSystem& instance();

	static Vec2f SfToLightVec(sf::Vector2f sfVec);

private:
	static std::unique_ptr<ltbl::LightSystem> sLightSystem;
	static sf::RenderWindow* mWindow;
	static sf::FloatRect mBounds;
};