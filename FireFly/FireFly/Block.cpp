//Block.cpp - Firefly

#include "Block.h"

Block::Block(sf::FloatRect blockArea, bool allowBlock)	// Creates an area which blocks light.
{
	this->blockArea = blockArea;
	this->allowBlock = allowBlock;
}

Block::~Block() //Deconstructor
{

}




