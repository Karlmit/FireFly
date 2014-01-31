//#include <SFML/Graphics.hpp>
#include "GameLoop.h"
#include <iostream>
#include <stdexcept>


int main()
{	
	try
	{
		GameLoop::getGameLoop().run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
