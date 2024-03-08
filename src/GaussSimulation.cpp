#include "GaussSimulation.hpp"

#include "ASCII_Engine/Sprite.hpp"
#include "ASCII_Engine/TextSprite.hpp"

#include <random>
#include <chrono>
#include <sstream>

#include <iostream>

void GaussSimulation::init()
{
	objs.push_back(new ObjetoDeJogo("Piramide",Sprite("rsc/piramideGauss.img"),1,0));
	objs.push_back(new ObjetoDeJogo("Balde",Sprite("rsc/balde.img"),25,0));
	
	for (int i = 0 ; i < qtdeBolas ; i++){
		objs.push_back(new ObjetoDeJogo("Bolas",TextSprite("*"),1,30));
		bolas.push_back(objs.back());
	}
	
	for (int i = 0 ; i < 8 ; i++)
	{
		vBaldes[i] = 0;
		if (i == 0)
			objs.push_back(new ObjetoDeJogo("Balde",TextSprite(" 0"),40,2));
		else if (i < 7)
			objs.push_back(new ObjetoDeJogo("Balde",TextSprite(" 0"),40,1+8*i));
		else
			objs.push_back(new ObjetoDeJogo("Balde",TextSprite(" 0"),40,8*i));
		
		SpriteBase *tmp = const_cast<SpriteBase*> (objs.back()->getSprite());
		tBaldes[i] = dynamic_cast<TextSprite*> (tmp);
	}
	
	for (int baldeOp = 0 ; baldeOp < 8 ; baldeOp++)
	{
		if (baldeOp == 0)
			baldes[baldeOp].push_back(ObjetoDeJogo("*",TextSprite("     "),37,1));
		else if (baldeOp <=3)
			baldes[baldeOp].push_back(ObjetoDeJogo("*",TextSprite("       "),37,7+8*(baldeOp-1)));
		else if (baldeOp < 7)
			baldes[baldeOp].push_back(ObjetoDeJogo("*",TextSprite("       "),37,7+8*(baldeOp-1)));
		else
			baldes[baldeOp].push_back(ObjetoDeJogo("*",TextSprite("     "),37,55));
			
	}
	
	
}

unsigned GaussSimulation::run(SpriteBuffer &screen)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine gen(seed);
	std::uniform_int_distribution<int> side(0,1);
	
	std::string ent;
	int fBolas = 0, iBolas = 0;
	
	//padrão
	draw(screen);
	system("clear");
	show(screen);
	
	
	while(iBolas < qtdeBolas)
	{
		//lendo entrada
		//getline(std::cin,ent);
		if (ent == "q")
			return Fase::END_GAME;
		
		fBolas += (fBolas + 1) <= qtdeBolas?1:0;
		
		for (int b = iBolas ; b < fBolas ; b++)
		{
			if (bolas[b]->getPosL() >= 22) {
				bolas[b]->desativarObj();
				iBolas++;
				
				std::ostringstream ostr;
				ostr.width(2);
				ostr.fill(' ');
				
				//std::cout << "Pos " << bolas[b]->getPosC() << " ";
				/*for (int i = 0 ; i < 8 ; i++)
					std::cout << vBaldes[i] << " ";*/
				int baldeOp = -1;
				switch (bolas[b]->getPosC())
				{
					case 2:	baldeOp = 0; break;
					case 10:baldeOp = 1; break;
					case 18:baldeOp = 2; break;
					case 26:baldeOp = 3; break;
					case 34:baldeOp = 4; break;
					case 42:baldeOp = 5; break;
					case 50:baldeOp = 6; break;
					case 58:baldeOp = 7; break;
				}
				
				if (baldeOp != -1)
				{
					vBaldes[baldeOp]++;
					ostr << vBaldes[baldeOp];
					tBaldes[baldeOp]->setText(ostr.str());
					
					//colocar * no balde baldeOp
					if (vBaldes[baldeOp]%fator!=0)
						continue;
					
					int qteAst = (vBaldes[baldeOp]/fator) % astPLBalde[baldeOp];
					
					SpriteBase *pSB = const_cast<SpriteBase*> (baldes[baldeOp].back().getSprite());
						
					TextSprite *pTS = dynamic_cast<TextSprite*> (pSB);
						
						
					if ( qteAst == 0) {
						if (baldeOp == 0){
							pTS->setText(std::string("*****"));
							baldes[baldeOp].push_back(ObjetoDeJogo("*",TextSprite("     "),37-baldes[baldeOp].size(),1));
						}
						else if (baldeOp <=3) {
							pTS->setText(std::string("*******"));
							baldes[baldeOp].push_back(ObjetoDeJogo("*",TextSprite("       "),37-baldes[baldeOp].size(),7+8*(baldeOp-1)));
						}
						else if (baldeOp < 7) {
							pTS->setText(std::string("*******"));
							baldes[baldeOp].push_back(ObjetoDeJogo("*",TextSprite("       "),37-baldes[baldeOp].size(),7+8*(baldeOp-1)));
						}
						else {
							pTS->setText(std::string("*****"));
							baldes[baldeOp].push_back(ObjetoDeJogo("*",TextSprite("     "),37-baldes[baldeOp].size(),55));
						}
							
					}
					else
					{
						
						if (baldeOp == 0)
							pTS->setText(std::string(5-qteAst,' ') + std::string(qteAst,'*'));
						else if (baldeOp <=3)
							pTS->setText(std::string(7-qteAst,' ') + std::string(qteAst,'*'));
						else if (baldeOp < 7)
							pTS->setText(std::string(qteAst,'*') + std::string(7-qteAst,' '));
						else
							pTS->setText(std::string(qteAst,'*') + std::string(5-qteAst,' '));
						
					}
				}
				
			}
			else {
				bolas[b]->moveDown(3);
				if (side(gen))
					bolas[b]->moveLeft(4);
				else
					bolas[b]->moveRight(4);
			}
		}
		
		//padrão
		update();
		draw(screen);
		system("clear");
		show(screen);
		system("sleep 0.1");
	}
	
	return Fase::END_GAME; // não necessário
}

void GaussSimulation::draw(SpriteBase &screen, unsigned x, unsigned y)
{
	Fase::draw(screen);
	
	for (int i = 0 ; i < 8 ; i++)
		for (int j = 0 ; j < baldes[i].size() ; j++)
			baldes[i][j].draw(screen,baldes[i][j].getPosL(),baldes[i][j].getPosC());
}