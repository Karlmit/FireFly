#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <Box2D/Box2D.h>


class Rigidbody : public sf::Transformable
{
public:
	// Conversion functions between sfml units and box2d units
	static b2Vec2 SfToBoxVec(const sf::Vector2f& vec);
	static b2Vec2 SfToBoxVec(float x, float y);
	static sf::Vector2f BoxToSfVec(const b2Vec2& vec);
	static sf::Vector2f BoxToSfVec(float32 x, float32 y);
	static float32 SfToBoxFloat(float val);
	static float BoxToSfFloat(float32 val);
	static float SfToBoxAngle(float degrees);
	static float BoxToSfAngle(float rads);


public:
	// Creates nothing. Call AddBody to make it do something
	Rigidbody();
	virtual ~Rigidbody();

	// Static Lines
	void AddStaticLineBody(const std::vector<sf::Vector2f>& pointList, bool loop = false);
	// Dynamic Circle
	void AddDynCircleBody(float radius, sf::Vector2f position, float32 density = 1.f, bool isSensor = false);
	// Dynamic Rectangles
	void AddDynRectBody(std::vector<sf::FloatRect> rects, sf::Vector2f position, float density = 1.f, bool dynamic = true);
	// Trigger Box
	void AddTriggerBoxBody(sf::FloatRect rect);

public:
	void			update();
	virtual void	drawDebug(sf::RenderTarget& target, sf::RenderStates states) const;

	b2Body*			getBody();

private:
	b2World*	mB2World;

	std::vector<sf::RectangleShape>	mRectShapes;
	sf::CircleShape		mCircleShape;
	std::vector<sf::Vector2f> mLinePointList;
	bool		mStatic;
	b2Body*		mBody;


};

#endif