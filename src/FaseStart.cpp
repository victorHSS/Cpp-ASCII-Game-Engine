#include "FaseStart.hpp"

#include "../ASCII_Engine/Cores.hpp"

void FaseStart::init()
{
	heroMove1 = new ObjetoDeJogo("Hero1",SpriteAnimado("rsc/heroKnightHorse.anm",2,COR::AZUL),39,30);
	objs.push_back(heroMove1);
	
	heroMove2 = new ObjetoDeJogo("Hero2",SpriteAnimado("rsc/littleKnight.anm",4,COR::AZUL),38,61);
	objs.push_back(heroMove2);
	heroMove2->desativarObj();
}

unsigned FaseStart::run(SpriteBuffer &screen)
{
	std::string ent;
	
	//padrão
	screen.clear();
	draw(screen);
	system("clear");
	show(screen);
	
	int state = RIDING;
	int countPracing = 0;
	
	while (true)
	{
		//lendo entrada
		getline(std::cin,ent);
		if (ent == "q")
			return Fase::END_GAME;
		
		switch(state){
			case RIDING:
				if (heroMove1->getPosC() <= 60)
					heroMove1->moveRight();
				else
				{
					heroMove1->desativarObj();
					heroMove2->ativarObj();
					state = PRACING;
				}
				break;
			case PRACING:
				if(countPracing++ == 24){
					heroMove2->desativarObj();
					heroMove1->ativarObj();
					state = END;
				}
				break;
			case END:
				if(heroMove1->getPosC() < 90){
					heroMove1->moveRight();
				}
				else
					return Fase::LEVEL_COMPLETE;
				break;
		}
		
		//padrão
		update();
		screen.clear();
		draw(screen);
		system("clear");
		show(screen);
	}
	
	return Fase::END_GAME; // não necessário
}
