#include "ASCII_Engine/TextSprite.hpp"
#include "ASCII_Engine/Sound.hpp"
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
	
	Sound backMusic("rsc/sounds/Cave.mp3");
	backMusic.playloop();
	
	system("clear");
	this->draw(screen);
	this->show(screen);
	
	while (true)
	{
		
		//logica da fase acontece aqui
		getline(std::cin,ent);
		if (ent == "q") break;
		else if (ent == "x")
		{
			backMusic.stop();
			return Fase::MENU;
		}
			
		
		this->update();
		this->draw(screen);
		system("clear");
		this->show(screen);
		
		system("sleep .2");
	}
	
	backMusic.stop();
	return Fase::END_GAME;
}
