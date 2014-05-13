#include "SimpleMenu.h"
#include "Globals.h"
#include "Save.h"
#include "Level.h"

const float VERTICAL_SPACING = 50.f;

const sf::Color DEFAULT_COLOR = sf::Color::White;
const sf::Color OVER_COLOR = sf::Color::Yellow;

SimpleMenu::SimpleMenu(sf::Window* window)
	: mWindow(window)
	, mFont()
	, mContinueButton(this, ButtonType::Continue)
	, mNewGameButton(this, ButtonType::NewGame)
	, mQuitButton(this, ButtonType::Quit)
	, mActive(false)
{
	setActive(true);
	mFont.loadFromFile("Resources/BEBAS___.ttf");
	mContinueButton.start();
	mNewGameButton.start();
	mQuitButton.start();	
	
}


void SimpleMenu::update(sf::Time dt)
{
	if (mActive)
	{
		mContinueButton.update(dt);
		mNewGameButton.update(dt);
		mQuitButton.update(dt);		
	}
	else 
	{		
	}
}

void SimpleMenu::setActive(bool active)
{
	mActive = active;
	Globals::ZID_INPUT = !active;
}

void SimpleMenu::toggleActive()
{
	setActive(!mActive);
}

void SimpleMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	if (mActive)
	{
		target.draw(mContinueButton, states);
		target.draw(mNewGameButton, states);
		target.draw(mQuitButton, states);
	}
}




//////////////////////////////////////////
//////////// SimpleButton ////////////////
//////////////////////////////////////////

SimpleButton::SimpleButton(SimpleMenu* menu, ButtonType type)
	: mMenu(menu)
	, mText()
	, mType(type)
	, mOverSound(Loading::getSound("Meny/Tangent2.wav"), true)
	, mClickSound(Loading::getSound("Meny/TangentSpacebar.wav"), true)
	, mOver(false)
{	
	
	mText.setPosition(100.f, 100.f);
	mText.setCharacterSize(30);
	mText.setString("NEW GAME");
	mText.setColor(sf::Color::White);

	switch (mType)
	{
	case ButtonType::Continue:
		mText.setString("CONTINUE");
		mText.move(0, VERTICAL_SPACING*0);
		break;
	case ButtonType::NewGame:
		mText.setString("NEW GAME");
		mText.move(0, VERTICAL_SPACING*1);
		break;
	case ButtonType::Quit:
		mText.setString("QUIT");
		mText.move(0, VERTICAL_SPACING*2);
		break;
	default:
		break;
	}
}

void SimpleButton::start()
{
	mText.setFont(mMenu->mFont);
}

void SimpleButton::update(sf::Time dt)
{
	sf::FloatRect bounds = mText.getGlobalBounds();
	bounds.left = bounds.left - 10;

	sf::Vector2i mousePos = sf::Mouse::getPosition(*mMenu->mWindow);
	if (bounds.contains(float(mousePos.x), float(mousePos.y)))
	{
		if (mOver == false)
			mOverSound.play();
		mOver = true;

		mText.setColor(OVER_COLOR);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mClickSound.play();
			switch (mType)
			{
			case ButtonType::Continue:
				mMenu->setActive(false);
				break;
			case ButtonType::NewGame:
				mMenu->setActive(false);
				if (Level::getLevel().mCurrentMap != "level1.tmx")
					Level::getLevel().fadeToBlackChangeLevel("level1.tmx");
				Save::writeLevel("");
				break;
			case ButtonType::Quit:
				mMenu->mWindow->close();
				break;
			default:
				break;
			}
		}
	}
	else
	{
		mText.setColor(DEFAULT_COLOR);
		mOver = false;
	}
}





void SimpleButton::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(mText, states);
}