#include "Entity.h"
#include "Animation.h"

class ServerRoomEyeScreen : public Entity
{
public:
	ServerRoomEyeScreen(sf::Vector2f position);

	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void sendMessage(Entity* sender, string message);
	virtual void start();

private:
	enum class State
	{
		Inactive,
		Open,
		Glitch,
		Close
	};

	Animation mOpenAnimation;
	Animation mGlitchAnimation;
	Animation mCloseAnimation;	
	sf::Sprite mSprite;	
	State mState;
};