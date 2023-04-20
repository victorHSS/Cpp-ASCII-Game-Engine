#ifndef GAME_HPP
#define GAME_HPP

#include "ASCII_Engine/SpriteBuffer.hpp"

class Game
{
public:
	Game(){}
	
	static void run();
private:
	static SpriteBuffer screen;
};

#endif // GAME_HPP
