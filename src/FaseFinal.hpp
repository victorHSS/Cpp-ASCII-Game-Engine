#ifndef FASEFINAL_HPP
#define FASEFINAL_HPP

#include "../ASCII_Engine/Fase.hpp"

class FaseFinal : public Fase
{
public:
	FaseFinal(std::string name, const Sprite &bkg) : Fase(name,bkg) {}
	FaseFinal(std::string name, const SpriteAnimado &bkg) : Fase(name,bkg) {}
	virtual ~FaseFinal() {}
	
	virtual void init();
	virtual unsigned run(SpriteBuffer &screen);

};

#endif // FASEFINAL_HPP
