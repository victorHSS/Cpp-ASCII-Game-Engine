#include "FaseFinal.hpp"

void FaseFinal::init()
{
	objs.push_back(new ObjetoDeJogo("Loving",SpriteAnimado("rsc/rescuePrincess.anm",4,COR::ROSA),24,30));
}

unsigned FaseFinal::run(SpriteBuffer &screen)
{
	std::string ent;
	
	//padrão
	screen.clear();
	draw(screen);
	system("clear");
	show(screen);
	
	
	for (int i = 0 ; i < 7*4 ; i++)
	{
		//lendo entrada
		getline(std::cin,ent);
		if (ent == "q")
			return Fase::END_GAME;
		
		//padrão
		update();
		screen.clear();
		draw(screen);
		system("clear");
		show(screen);
	}
	
	return Fase::END_GAME; // não necessário
}

