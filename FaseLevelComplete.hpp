#ifndef FASELEVELCOMPLETE_HPP
#define FASELEVELCOMPLETE_HPP

#include "ASCII_Engine/SpriteBuffer.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include "ASCII_Engine/SpriteAnimado.hpp"
#include "ASCII_Engine/Fase.hpp"
#include "ASCII_Engine/ObjetoDeJogo.hpp"

class FaseLevelComplete : public Fase
{
public:
	FaseLevelComplete(std::string name, const Sprite &bkg) : Fase(name,bkg) {}
	FaseLevelComplete(std::string name, const SpriteAnimado &bkg) : Fase(name,bkg) {}
	virtual ~FaseLevelComplete(){}
	
	
	virtual void init();
	virtual unsigned run(SpriteBuffer &screen);

};
#endif // FASELEVELCOMPLETE_HPP
