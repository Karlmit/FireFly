#include "LightManager.h"
#include "Camera.h"

std::unique_ptr<ltbl::LightSystem> LightManager::sLightSystem(nullptr);
sf::RenderWindow* LightManager::mWindow = nullptr;
sf::FloatRect LightManager::mBounds;

void LightManager::setWindow(sf::RenderWindow* window)
{
	mWindow = window;
}

void LightManager::newLightSystem(sf::FloatRect bounds) 
{
	

	mBounds = bounds;
	Vec2f lowerBound(-bounds.width, -bounds.height);
	Vec2f upperBound(bounds.width*2, bounds.height*2);
	AABB aabb = AABB(lowerBound, upperBound);

	std::string lightFin = "Resources/Light/lightFin.png";
	std::string shader = "Resources/Light/shaders/lightAttenuationShader.frag";

	ltbl::LightSystem* lightSystem = new ltbl::LightSystem(aabb, mWindow, lightFin, shader);	
	lightSystem->m_useBloom = true;
	lightSystem->m_ambientColor = sf::Color(100,100,100,255);
	

	sLightSystem.reset(lightSystem);
	
}

ltbl::LightSystem& LightManager::instance() 
{
	return *sLightSystem.get();
}

Vec2f LightManager::SfToLightVec(sf::Vector2f sfVec)
{
	//std::cout << "CamSize" << Camera::currentCamera().getView().getSize().y << std::endl;
	return Vec2f(sfVec.x, 864  - sfVec.y);
}