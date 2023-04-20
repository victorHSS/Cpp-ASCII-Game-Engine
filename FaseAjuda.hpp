#ifndef FASEAJUDA_HPP
#define FASEAJUDA_HPP

#include "ASCII_Engine/SpriteBuffer.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include "ASCII_Engine/SpriteAnimado.hpp"
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "ASCII_Engine/Fase.hpp"

class FaseAjuda : public Fase
{
public:
	FaseAjuda(std::string name, const Sprite &bkg) : Fase(name,bkg) {}
	FaseAjuda(std::string name, const SpriteAnimado &bkg) : Fase(name,bkg) {}
	virtual ~FaseAjuda(){}
	
	
	virtual void init();
	virtual unsigned run(SpriteBuffer &screen);

};

#endif // FASEAJUDA_HPP
