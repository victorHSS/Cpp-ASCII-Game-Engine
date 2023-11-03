#include "FaseLevel1.hpp"

#include "Enemy.hpp"

#include <iostream>

void FaseLevel1::init()
{	
	//Objetos de jogo
	princesa = new ObjetoDeJogo("Princess",SpriteAnimado("rsc/littlePrincess.anm",2),16,196);
	objs.push_back(princesa);
	
	guardas[0] = new Enemy(ObjetoDeJogo("Enemy1",SpriteAnimado("rsc/enemy3.anm",3),20,20));
	objs.push_back(guardas[0]);
	
	guardas[1] = new Enemy(ObjetoDeJogo("Enemy2",SpriteAnimado("rsc/enemy2.anm",2),35,180));
	objs.push_back(guardas[1]);
	
	objs.push_back(new ObjetoDeJogo("Cama",Sprite("rsc/bed.img"),12,168));
	
	chave = new ObjetoDeJogo("Chave",Sprite("rsc/key.img"),12,140);
	objs.push_back(chave);
	
	miniChave = new ObjetoDeJogo("MiniChave",TextSprite("O=;"),7,118);
	objs.push_back(miniChave);
	miniChave->desativarObj();
	
	porta = new Door(ObjetoDeJogo("Door",SpriteAnimado("rsc/door.anm"),31,182));
	objs.push_back(porta);
	
	tapetePorta = new ObjetoDeJogo("Tapete",SpriteBuffer(17,1),35,182);
	objs.push_back(tapetePorta);
	
	hero = new Hero(ObjetoDeJogo("Hero",SpriteAnimado("rsc/hero.anm",2),39,108));
	objs.push_back(hero);
	
	portao = new ObjetoDeJogo("frontDoor",Sprite("rsc/frontDoor.img"),49,102);
	objs.push_back(portao);
													 //std::string(20,'#')
	objs.push_back(new ObjetoDeJogo("Life",TextSprite("####################"),7,85));
	SpriteBase *tmp = const_cast<SpriteBase*> (objs.back()->getSprite());
	life = dynamic_cast<TextSprite*> (tmp);
	
	//blocos
	objs.push_back(new ObjetoDeJogo("B1",Sprite("rsc/castleBlock1.img"),18,38));
	colisoes.push_back(objs.back());
	
	objs.push_back(new ObjetoDeJogo("B2",Sprite("rsc/castleBlock2.img"),33,38));
	colisoes.push_back(objs.back());
	
	objs.push_back(new ObjetoDeJogo("B3",Sprite("rsc/castleBlock3.img"),33,132));
	colisoes.push_back(objs.back());
	
	objs.push_back(new ObjetoDeJogo("B4",Sprite("rsc/castleBlock4.img"),18,45));
	colisoes.push_back(objs.back());
	
	objs.push_back(new ObjetoDeJogo("B5",Sprite("rsc/castleBlock5.img"),18,120));
	colisoes.push_back(objs.back());
	
	objs.push_back(new ObjetoDeJogo("B6",Sprite("rsc/castleBlock6.img"),10,158));
	colisoes.push_back(objs.back());
	
	objs.push_back(new ObjetoDeJogo("B7",Sprite("rsc/castleBlock7.img"),31,158));
	colisoes.push_back(objs.back());
	
	objs.push_back(new ObjetoDeJogo("B8",Sprite("rsc/castleBlock8.img"),31,199));
	colisoes.push_back(objs.back());
	
}

unsigned FaseLevel1::run(SpriteBuffer &screen)
{
	std::string ent;
	
	//padrão
	draw(screen);
	system("clear");
	show(screen);
	
	while (true)
	{
		//lendo entrada
		getline(std::cin,ent);
		
		//processando entradas
		int posL = hero->getPosL(), posC = hero->getPosC();
		
		if (ent == "w" && hero->getPosL() > 10)
			hero->moveUp(3);
		else if (ent == "s" && hero->getPosL() < screen.getAltura() - 15)
			hero->moveDown(3);
		else if (ent == "a" && hero->getPosC() > 12)
			hero->moveLeft(3);
		else if (ent == "d" && hero->getPosC() < screen.getLargura() - hero->getSprite()->getLargura() - 13)
			hero->moveRight(3);
		else if (ent == "x") {
			for (int g = 0 ; g < 2 ; g++)
				if (hero->colideCom(*guardas[g])) {
					guardas[g]->sofrerAtaque(hero->atacar());
					if (!guardas[g]->isAlive())
						guardas[g]->desativarObj();
				}
		}
		else if (ent == "q")
			return Fase::END_GAME;
			

		if (colideComBloco()) 
			hero->moveTo(posL,posC);
		
		
		//processando eventos
		for (int g = 0 ; g < 2 ; g++)
				if (hero->colideCom(*guardas[g])) {
					hero->sofrerAtaque(guardas[g]->atacar());
					
					if (!hero->isAlive())
						return Fase::GAME_OVER;
					
					life->setText(std::string(hero->getLife()/5,'#'));
				}
		
		if (hero->colideCom(*chave))
		{
			chave->desativarObj();
			miniChave->ativarObj();
			hero->pegarChave();
		}
		else if (hero->colideCom(*tapetePorta) && hero->possuiChave())
		{
			porta->openTheDoor();
		}
		else if (hero->colideCom(*princesa))
		{
			princesa->desativarObj();
			hero->salvarPrincesa();
		}
		else if (hero->colideCom(*portao) && hero->salvouPrincesa())
		{
			return Fase::LEVEL_COMPLETE;
		}
		
		
		//padrão
		update();
		draw(screen);
		system("clear");
		show(screen);
	}
	
	return Fase::END_GAME; // não necessário
}

bool FaseLevel1::colideComBloco() const
{
	for (auto it = colisoes.begin() ; it != colisoes.end() ; ++it)
		if (hero->colideCom(**it)) {
			return true;
		}
	
	if (hero->colideCom(*porta) && !porta->isOpen() )
		return true;
	
	return false;
}

