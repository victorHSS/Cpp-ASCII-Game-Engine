#ifndef FASETESTE_HPP
#define FASETESTE_HPP

#include "ASCII_Engine/Fase.hpp"
#include "ASCII_Engine/SpriteBuffer.hpp"
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include "ASCII_Engine/SpriteAnimado.hpp"
#include <vector>
#include <string>


class FaseTeste : public Fase
{
public:
	FaseTeste(std::string name, const Sprite &bkg) : Fase(name,bkg) {}
	FaseTeste(std::string name, const SpriteAnimado &bkg) : Fase(name,bkg) {}
	
	virtual void init();
	virtual unsigned run(SpriteBuffer &screen);
	
	virtual ~FaseTeste() {}

};

#endif // FASETESTE_HPP
