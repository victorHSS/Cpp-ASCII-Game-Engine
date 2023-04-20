#include "FaseTeste.hpp"

void FaseTeste::init()
{
	//crio objetos de jogo aqui
	
	objs.push_back(new ObjetoDeJogo("HeliRescue",SpriteAnimado("rsc/helicopteroAnim.anm"),4,25));
	
	objs.push_back(new ObjetoDeJogo("PessoaAnimada",SpriteAnimado("rsc/pessoaGritando.anm"),15,75));
	objs.push_back(new ObjetoDeJogo(*( objs.back() )));
	objs.back()->moveTo(15,83);
	
	SpriteAnimado ponte("rsc/ponteAnimada.anm");
	ponte.putAt(TextSprite("Bem-vindo!!"),5,28);
	
	objs.push_back(new ObjetoDeJogo("Ponte",ponte,9,1));
	objs.push_back(new ObjetoDeJogo("TextoVidas",TextSprite("Vidas:"),1,3));
	objs.push_back(new ObjetoDeJogo("TextoPeso",TextSprite("Peso Total:"),1,15));
	objs.push_back(new ObjetoDeJogo("TextoSalvos",TextSprite("Resgatados:"),1,45));

}

unsigned FaseTeste::run(SpriteBuffer &screen)
{
	//while (true) 
	for (int i = 0 ; i < 24 ; i++) // enquanto nao resolvo entrada
	{
		system("clear");
		
		//logica da fase acontece aqui
		
		
		this->update();
		this->draw(screen);
		this->show(screen);
		
		system("sleep .2");
	}
	
	return Fase::END_GAME;
}

