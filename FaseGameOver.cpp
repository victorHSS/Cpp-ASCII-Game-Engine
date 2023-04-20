#include "ASCII_Engine/TextSprite.hpp"
#include "FaseGameOver.hpp"
#include <string>
#include <iostream>

void FaseGameOver::init()
{
	//crio objetos de jogo aqui
	
	objs.push_back(new ObjetoDeJogo("HeliRescue",SpriteAnimado("rsc/helicopterMenu.anm"),4,60));
	objs.push_back(new ObjetoDeJogo("TextGame",TextSprite("The ASCII Rescue Game"),20,68));
	objs.push_back(new ObjetoDeJogo("Text----",TextSprite("-----------------------"),21,67));
	objs.push_back(new ObjetoDeJogo("GameOverText",Sprite("rsc/gameOverText1.img"),25,42));

}

unsigned FaseGameOver::run(SpriteBuffer &screen)
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
			return Fase::MENU;
			
		
		system("clear");
		this->update();
		this->draw(screen);
		this->show(screen);
		
		system("sleep .2");
	}
	
	return Fase::END_GAME;
}
