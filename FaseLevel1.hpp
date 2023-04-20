#ifndef FASELEVEL1_HPP
#define FASELEVEL1_HPP

#include "ASCII_Engine/Fase.hpp"
#include "Helicopter.hpp"
#include "Pessoa.hpp"
#include "Fuel.hpp"

class FaseLevel1 : public Fase
{
public:
	FaseLevel1(std::string name, const Sprite &bkg) : Fase(name,bkg) {}
	FaseLevel1(std::string name, const SpriteAnimado &bkg) : Fase(name,bkg) {}
	virtual ~FaseLevel1(){}
	
	
	virtual void init();
	virtual unsigned run(SpriteBuffer &screen);
	
private:
	Helicopter *heli;
	SpriteBase *txtTanque, *txtCarga, *txtSalvos;
	Pessoa *pessoa1, *pessoa2;
	Fuel *fuel;
	ObjetoDeJogo *baseResg;
};

#endif // FASELEVEL1_HPP
