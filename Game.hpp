#ifndef GAME_HPP
#define GAME_HPP

#include "FaseLevel1.hpp"
#include "FaseStart.hpp"
#include "FaseFinal.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include "ASCII_Engine/SpriteAnimado.hpp"

class Game
{
public:
	Game(){}
	~Game(){}
	
	static void run()
	{
		SpriteBuffer buffer(250,57);
	
		FaseStart start("FaseStart",SpriteAnimado("rsc/castleMedieval.anm",3));
		FaseLevel1 fase1("Fase1",Sprite("rsc/fase2.img"));
		FaseFinal faseFinal("Fase1",Sprite("rsc/title1Gothic.img"));
		
		start.init();
		start.run(buffer);
		
		buffer.clear();
		fase1.init();
		int ret1 = fase1.run(buffer);
		if ( ret1 != Fase::GAME_OVER && ret1 != Fase::END_GAME){
		
			buffer.clear();
			faseFinal.init();
			faseFinal.run(buffer);
		}
		else
			std::cout << "GAME OVER" << std::endl;
		
		std::cout << "Saindo..." << std::endl;
	}

};

#endif // GAME_HPP
