#ifndef GAUSSSIMULATION_HPP
#define GAUSSSIMULATION_HPP

#include "ASCII_Engine/Fase.hpp"
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include <vector>


class GaussSimulation : public Fase
{
public:
	GaussSimulation(std::string name, const Sprite &bkg) : Fase(name,bkg) {}
	GaussSimulation(std::string name, const SpriteAnimado &bkg) : Fase(name,bkg) {}
	virtual ~GaussSimulation() {}

	virtual void init();
	virtual unsigned run(SpriteBuffer &screen);
	
	virtual void draw(SpriteBase &screen, unsigned x = 0, unsigned y = 0);
	
private:
	std::vector<ObjetoDeJogo*> bolas;
	
	const int qtdeBolas = 600;
	int fator = 2;
	
	int vBaldes[8];
	TextSprite *tBaldes[8]; 
	
	int astPLBalde[8]{5,7,7,7,7,7,7,5};
	std::vector<ObjetoDeJogo> baldes[8];
};

#endif // GAUSSSIMULATION_HPP
