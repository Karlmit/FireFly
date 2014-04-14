#pragma once

#include <SFML\Graphics.hpp>
#include "Audio.h"

enum class ButtonType {
	Continue,
	NewGame,		
	Quit
};

class SimpleMenu;
class SimpleButton : public sf::Drawable, public sf::Transformable
{
public:
	SimpleButton(SimpleMenu *menu, ButtonType type);
	void update(sf::Time dt);
	void start();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	SimpleMenu* mMenu;
	sf::Text mText;
	ButtonType mType;
	bool mOver;
	Audio mOverSound;
	Audio mClickSound;
};


class SimpleMenu : public sf::Drawable
{
	friend class SimpleButton;	

public:
	SimpleMenu(sf::Window* window);
	void update(sf::Time dt);
	void setActive(bool active);
	void toggleActive();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Window* mWindow;
	sf::Font mFont;
	sf::Text mText;
	SimpleButton mContinueButton;
	SimpleButton mNewGameButton;
	SimpleButton mQuitButton;
	bool mActive;	

};

