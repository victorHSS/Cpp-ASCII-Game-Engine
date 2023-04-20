#include "FaseLevel1.hpp"

#include "Helicopter.hpp"
#include "Pessoa.hpp"
#include "Fuel.hpp"
#include <sstream> 
#include <iostream>
#include <algorithm>

void FaseLevel1::init()
{
	
	objs.push_back(new ObjetoDeJogo("PonteAnm",SpriteAnimado("rsc/ponteAnimada.anm"),9,10));
	objs.push_back(new ObjetoDeJogo("PonteAnm",SpriteAnimado("rsc/ponteAnimada.anm"),9,78));
	objs.push_back(new ObjetoDeJogo("Ilha",Sprite("rsc/ilha1.img"),20,100));
	objs.push_back(new ObjetoDeJogo("Ilha",Sprite("rsc/ilha1.img"),20,30));
	
	objs.push_back(new ObjetoDeJogo("Base",Sprite("rsc/baseResgate.img"),32,4));
	baseResg = objs.back();
	
	objs.push_back(new ObjetoDeJogo("TxtTanque",TextSprite("Tanque: [##########]"),1,3));
	txtTanque = objs.back()->getSprite();
	
	objs.push_back(new ObjetoDeJogo("TxtCarga",TextSprite("Carga: [          ]"),1,33));
	txtCarga = objs.back()->getSprite();
	
	objs.push_back(new ObjetoDeJogo("TxtSalvos",TextSprite("Resgatados: 0/2"),1,62));
	txtSalvos = objs.back()->getSprite();
	
	objs.push_back(new Pessoa(ObjetoDeJogo("Pessoa",SpriteAnimado("rsc/pessoa.anm"),30,120),70));
	pessoa1 = dynamic_cast<Pessoa*> (objs.back());
	
	objs.push_back(new Pessoa(ObjetoDeJogo("Pessoa",SpriteAnimado("rsc/pessoa.anm"),30,50),80));
	pessoa2 = dynamic_cast<Pessoa*> (objs.back());
	
	objs.push_back(new Fuel(ObjetoDeJogo("Fuel",Sprite("rsc/combustivel.img"),35,140),30));
	fuel = dynamic_cast<Fuel*> (objs.back());
	
	objs.push_back(
		new Helicopter(ObjetoDeJogo("HeliRescue",SpriteAnimado("rsc/helicopteroAnim.anm"),4,10),
		5,300,200));
	heli = dynamic_cast<Helicopter*> (objs.back());
	
}

unsigned FaseLevel1::run(SpriteBuffer &screen)
{
	std::string ent;
	Pessoa *pAnt = nullptr;
	unsigned tResgatados = 0;
	
	system("clear");
	this->draw(screen);
	this->show(screen);
	
	while (true)
	{
		
		//logica da fase acontece aqui
		getline(std::cin,ent);
		
		if (tResgatados == 2)
			return Fase::LEVEL_COMPLETE;
		
		if (ent == "q") break;
		else if (ent == "s" && 
				(heli->getPosL() + heli->getSprite()->getAltura() < screen.getAltura()-1))
			heli->moveDown();
		else if (ent == "w" && 
				(heli->getPosL() > 3))
			heli->moveUp();
		else if (ent == "a" && 
				(heli->getPosC() > 1))
			heli->moveLeft();
		else if (ent == "d" && 
				(heli->getPosC() + heli->getSprite()->getLargura() < screen.getLargura()-1))
			heli->moveRight();
		else if (ent == "x")
		{
			if (heli->colideCom(*pessoa1) && 		//se helicoptero chegou na pessoa
				heli->podeEmbarcar(*pessoa1) &&     //e ainda cabe embarque
				!pessoa1->foiResgatada()) 			//e a pessoa ainda n foi resgatada
			{
				pessoa1->desativarObj();
				heli->embarcar(pessoa1);
			}
			else if (heli->colideCom(*pessoa2) && 
					 heli->podeEmbarcar(*pessoa2) &&
					 !pessoa2->foiResgatada())
			{
				pessoa2->desativarObj();
				heli->embarcar(pessoa2);
			}
			else if (heli->colideCom(*baseResg) && heli->temResgatados())
			{
				//std::cout << "Estou ma base..."; //apagar
				
				std::list<Pessoa*> resgatados = heli->desembarcar();
				auto it = resgatados.begin();
				if (!pAnt)
				{
					pAnt = resgatados.front();
					pAnt->ativarObj();
					pAnt->resgatar();
					tResgatados++;
					pAnt->moveTo(baseResg->getPosL()-pAnt->getSprite()->getAltura()+1,baseResg->getPosC());
					//trick = 1;
					++it;
					
				}
				//std::cout << pAnt->getPosL() << " " << pAnt->getPosC();
				
				for ( ; it != resgatados.end() ; ++it)
				{
					(*it)->ativarObj();
					(*it)->resgatar();
					tResgatados++;
					(*it)->moveTo(baseResg->getPosL()-(*it)->getSprite()->getAltura()+1,
								  pAnt->getPosC()+(*it)->getSprite()->getLargura()+1);
					pAnt = *it;
				}
				
			}
			else if (heli->colideCom(*fuel))
			{
				heli->abastecer(fuel->getFuel());
				fuel->desativarObj();
			}
			
			//ajustar carga
			std::string st(heli->getCargaAtual(),'#');
			st += std::string(10-heli->getCargaAtual(),' ');
			st = "["+st+"]";
			txtCarga->putAt(TextSprite(st),0,7);
			
			//ajuste resgatados
			st = std::string("Resgatados: 0/2");
			st[12] = '0' + tResgatados;
			txtSalvos->putAt(TextSprite(st),0,0);
		}
		
		if (!heli->podeVoar())
			return Fase::GAME_OVER;
		else
		{
			std::string st(heli->getTanqueAtual(),'#');
			st += std::string(10-heli->getTanqueAtual(),' ');
			st = "["+st+"]";
			
			txtTanque->putAt(TextSprite(st),0,8);
		}
		
		system("clear");
		this->update();
		this->draw(screen);
		this->show(screen);
		
		system("sleep .2");
	}
	
	return Fase::MENU;
}
