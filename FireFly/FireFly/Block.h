//Block.h - Firefly

#pragma once

#include <SFML/Graphics.hpp>

class Block 
{
public:
	Block(sf::FloatRect blockArea, bool allowBlock);
	~Block();

	sf::FloatRect blockArea;				
	bool allowBlock;						
};