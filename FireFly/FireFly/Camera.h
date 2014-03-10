#pragma once


#include <SFML/Window.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Camera : public sf::Transformable
{
public:
	static Camera& currentCamera();
private:
	static Camera* sCurrentCamera;

public:
	Camera(sf::Window* window);
	void update(sf::Time dt);

	sf::Vector2f	getMousePosition();
	sf::Vector2f getWindowMousePosition();
	sf::Vector2f getMouseScale();

	sf::View		getView();
	sf::View		getViewZ();

	void setTargetPosition(sf::Vector2f position);
	void setBounds(sf::FloatRect bounds);
	void changeZoom(int steps);
	void setZoom(float zoom);
	
private:
	sf::Window* mWindow;
	sf::View	mView;
	
	float		mTargetZoom;
	float		mZoom;
	sf::Vector2f mFollowTargetPosition;
	sf::FloatRect mBounds;

	sf::Vector2u mInitial_Size;

};