#include "Entity.h"
#include "Animation.h"

class CameraScreen : public Entity
{
public:
	CameraScreen(string openTexture, string activeTexture, sf::Vector2f position);

	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void sendMessage(Entity* sender, string message);
	virtual void start();

private:
	enum class State 
	{
		Inactive,
		Open1,
		Open2,
		Active,
		Glitch,
		Close
	};

	Animation mOpenScreenAnimation;
	Animation mOpenAnimation;
	Animation mActiveAnimation;
	sf::Sprite mSprite;	
	bool mNoActiveAnimation;
	State mState;
};