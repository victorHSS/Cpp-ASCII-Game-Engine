#ifndef GAME_HPP
#define GAME_HPP

#include "GaussSimulation.hpp"

class Game
{
public:
	static void run()
	{
		SpriteBuffer screen(65,42);
		GaussSimulation gs("Simulation",Sprite("rsc/back.img"));
		
		gs.init();
		gs.run(screen);
	}

};

#endif // GAME_HPP
