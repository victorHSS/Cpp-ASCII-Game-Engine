#ifndef FASELEVEL1_HPP
#define FASELEVEL1_HPP

#include "ASCII_Engine/Fase.hpp"
#include <string>
#include <list>

#include "Enemy.hpp"
#include "Door.hpp"
#include "Hero.hpp"

class FaseLevel1 : public Fase
{
public:
	FaseLevel1(std::string name, const Sprite &bkg) : Fase(name,bkg) {}
	FaseLevel1(std::string name, const SpriteAnimado &bkg) : Fase(name,bkg) {}
	virtual ~FaseLevel1() {}
	
	
	virtual void init();
	virtual unsigned run(SpriteBuffer &screen);
	
	bool colideComBloco() const;
	
private:
	Enemy *guardas[2];
	Hero *hero;
	Door *porta;
	ObjetoDeJogo *tapetePorta;
	ObjetoDeJogo *portao;
	ObjetoDeJogo *chave;
	ObjetoDeJogo *miniChave;
	ObjetoDeJogo *princesa;
	
	TextSprite *life;
	
	std::list<ObjetoDeJogo*> colisoes;
};

#endif // FASELEVEL1_HPP
