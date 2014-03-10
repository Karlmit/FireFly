
#include "Camera.h"
#include "Utility.h"

const float CAMERA_SPEED = 340.f;
const float ZOOM_SPEED = 1.f;
const float DEF_ZOOM = 1.f;

Camera* Camera::sCurrentCamera = nullptr;

Camera& Camera::currentCamera() {
	return *sCurrentCamera;
}

Camera::Camera(sf::Window* window) 
: mWindow(window)
, mView()
, mZoom(DEF_ZOOM)
, mTargetZoom(DEF_ZOOM)
, mFollowTargetPosition()
, mBounds()
{
	sCurrentCamera = this;
	mInitial_Size = window->getSize();
}


void Camera::update(sf::Time dt) {

	// Smooth follow after target position
	// low damping = slower follow
    float damping = 4.0f;
	setPosition(Util::Lerp(getPosition(), mFollowTargetPosition, dt.asSeconds() * damping));

	// Applies the position to the view
	sf::Vector2f viewSize = sf::Vector2f(float(mWindow->getSize().x),float(mWindow->getSize().y));
	mView = sf::View(getPosition(), viewSize);

	// Zooms in and out withthe pageup and pqgedown keys
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
        mZoom -= ZOOM_SPEED * dt.asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
        mZoom += ZOOM_SPEED * dt.asSeconds(); 
	*/

	// Smooth zoom
	float zoomDamping = 3.f;
	mZoom = Util::Lerp(mZoom, mTargetZoom, dt.asSeconds() * zoomDamping);
	mView.zoom(mZoom);
	

	// Size after zoom
	viewSize = mView.getSize();

	// Limit the cameraview to the level bounds
	if (mBounds.width != 0 && mBounds.height != 0)
	{
		float x = getPosition().x;
		float y = getPosition().y;
		// Left boundry
		if ((getPosition().x - viewSize.x/2) < mBounds.left)
			x = mBounds.left + viewSize.x/2;
		// Right boundry
		if ((getPosition().x + viewSize.x/2) > (mBounds.left+mBounds.width))
			x = (mBounds.left+mBounds.width) - viewSize.x/2;
		// Top boundry
		if ((getPosition().y - viewSize.y/2) < mBounds.top)
			y = mBounds.top + viewSize.y/2;
		// Bottom boundry
		if ((getPosition().y + viewSize.y/2) > (mBounds.top+mBounds.height))
			y = (mBounds.top+mBounds.height) - viewSize.y/2;


		setPosition(x, y);
	}
	
	mView.setCenter(getPosition());	
}



sf::Vector2f Camera::getMousePosition() {
	sf::Vector2f pos;
	pos.x = sf::Mouse::getPosition(*mWindow).x*mZoom + mView.getCenter().x - mView.getSize().x/2;
	pos.y = sf::Mouse::getPosition(*mWindow).y*mZoom + mView.getCenter().y - mView.getSize().y/2;

	return pos;
}

sf::Vector2f Camera::getWindowMousePosition()
{
	sf::Vector2f pos;
	pos.x = sf::Mouse::getPosition(*mWindow).x * (mInitial_Size.x / mView.getSize().x);
	pos.y = sf::Mouse::getPosition(*mWindow).y * (mInitial_Size.y / mView.getSize().y);

	return pos;
}

sf::Vector2f Camera::getMouseScale()
{

	sf::Vector2f scale;
	scale.x = mInitial_Size.x / mView.getSize().x;
	scale.y = mInitial_Size.y / mView.getSize().y;
	return scale;

}

sf::View Camera::getView() {
	return mView;
}

sf::View Camera::getViewZ() {
	sf::View view(mView);
	//view.setSize(sf::Vector2f(1536, 864));
	view.setSize(sf::Vector2f(1920, 1080));
	//view.setSize(sf::Vector2f(5000, 2160));
	//view.zoom(1.f/mZoom);
	return view;

	sf::RenderTexture tex;	
}


void Camera::setTargetPosition(sf::Vector2f position)
{
	mFollowTargetPosition = position;
}

void Camera::setBounds(sf::FloatRect bounds)
{
	mBounds = bounds;
}

void Camera::changeZoom(int steps) 
{
	float zoomStep = 0.1f;
	float lowerLimit = 0.1f;
	float topLimit = 2.f;
	mTargetZoom -= steps * zoomStep;
	if (mTargetZoom < lowerLimit)
		mTargetZoom = lowerLimit;
	if (mTargetZoom > topLimit)
		mTargetZoom = topLimit;
}

void Camera::setZoom(float zoom)
{
	mTargetZoom = zoom;
}
