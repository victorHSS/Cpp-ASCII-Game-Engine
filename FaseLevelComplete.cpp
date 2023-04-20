#include "ASCII_Engine/TextSprite.hpp"
#include "FaseLevelComplete.hpp"
#include <string>
#include <iostream>

void FaseLevelComplete::init()
{
	//crio objetos de jogo aqui
	
	objs.push_back(new ObjetoDeJogo("HeliRescue",SpriteAnimado("rsc/helicopterMenu.anm"),4,60));
	objs.push_back(new ObjetoDeJogo("TextGame",TextSprite("The ASCII Rescue Game"),20,68));
	objs.push_back(new ObjetoDeJogo("Text----",TextSprite("-----------------------"),21,67));
	objs.push_back(new ObjetoDeJogo("WinText",Sprite("rsc/levelComplete.img"),25,33));

}

unsigned FaseLevelComplete::run(SpriteBuffer &screen)
{
	std::string ent;
	
	system("clear");
	this->draw(screen);
	this->show(screen);
	
	while (true)
	{
		
		//logica da fase acontece aqui
		getline(std::cin,ent);
		if (ent == "q") break;
		else if (ent == "x")
			return Fase::OP_1;
			
		
		system("clear");
		this->update();
		this->draw(screen);
		this->show(screen);
		
		system("sleep .2");
	}
	
	return Fase::OP_1;
}

