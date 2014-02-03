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
	sf::View		getView();

	void setTargetPosition(sf::Vector2f position);
	void setBounds(sf::FloatRect bounds);
	void changeZoom(int steps);

private:
	sf::Window* mWindow;
	sf::View	mView;
	float		mZoom;
	float		mTargetZoom;

	sf::Vector2f mFollowTargetPosition;
	sf::FloatRect mBounds;

};