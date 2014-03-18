#include "Entity.h"
#include "Animation.h"

class ServerRoomDoor : public Entity
{
public:
	ServerRoomDoor(string texture, sf::Vector2f position);

	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void sendMessage(Entity* sender, string message);
	virtual void start();

private:
	Animation mAnimation; 
	sf::Sprite mSprite;	

};