#include "ASCII_Engine/TextSprite.hpp"
#include "FaseAjuda.hpp"
#include <string>
#include <iostream>

void FaseAjuda::init()
{
	//crio objetos de jogo aqui
	
	objs.push_back(new ObjetoDeJogo("HeliRescue",SpriteAnimado("rsc/helicopterMenu.anm"),4,60));
	objs.push_back(new ObjetoDeJogo("TextGame",TextSprite("The ASCII Rescue Game"),20,68));
	objs.push_back(new ObjetoDeJogo("Text----",TextSprite("-----------------------"),21,67));
	objs.push_back(new ObjetoDeJogo("Ajuda1",TextSprite("w     - UP"),23,74));
	objs.push_back(new ObjetoDeJogo("Ajuda2",TextSprite("s     - DOWN"),25,74));
	objs.push_back(new ObjetoDeJogo("Ajuda3",TextSprite("a     - LEFT"),27,74));
	objs.push_back(new ObjetoDeJogo("Ajuda4",TextSprite("d     - RIGHT"),29,74));
	objs.push_back(new ObjetoDeJogo("Ajuda5",TextSprite("x     - SELECT/RESCUE"),31,74));
	objs.push_back(new ObjetoDeJogo("Ajuda6",TextSprite("p     - PAUSE"),33,74));
	objs.push_back(new ObjetoDeJogo("Ajuda6",TextSprite("ENTER - TURN"),35,74));
	objs.push_back(new ObjetoDeJogo("AjudaAviso",TextSprite("Pressione x para voltar ao menu."),37,64));
	

}

unsigned FaseAjuda::run(SpriteBuffer &screen)
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
			
		
		this->update();
		this->draw(screen);
		system("clear");
		this->show(screen);
		
		system("sleep .2");
	}
	
	return Fase::END_GAME;
}