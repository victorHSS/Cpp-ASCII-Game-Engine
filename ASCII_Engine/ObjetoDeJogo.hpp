#ifndef OBJETODEJOGO_HPP
#define OBJETODEJOGO_HPP

#include "RenderBase.hpp"
#include "SpriteBase.hpp"
#include "SpriteBuffer.hpp"
#include "Sprite.hpp"
#include "SpriteAnimado.hpp"
#include "TextSprite.hpp"

#include <string>

class ObjetoDeJogo : public RenderBase
{
public:
	ObjetoDeJogo(std::string name, const Sprite &s, unsigned posL, unsigned posC) : 
		name(name),pSprite(new Sprite(s)),posL(posL),posC(posC),active(true) {}
		
	ObjetoDeJogo(std::string name, const SpriteAnimado &s, unsigned posL, unsigned posC) :
		name(name),pSprite(new SpriteAnimado(s)),posL(posL),posC(posC),active(true) {}
		
	ObjetoDeJogo(std::string name, const TextSprite &s, unsigned posL, unsigned posC) :
		name(name),pSprite(new TextSprite(s)),posL(posL),posC(posC),active(true) {}
	
	ObjetoDeJogo(std::string name, const SpriteBuffer &s, unsigned posL, unsigned posC) :
		name(name),pSprite(new SpriteBuffer(s)),posL(posL),posC(posC),active(true) {}
	
	ObjetoDeJogo(const ObjetoDeJogo&);
	
	virtual ~ObjetoDeJogo(){ delete pSprite;}
	
	const ObjetoDeJogo &operator=(const ObjetoDeJogo &);
	
	bool colideCom(const ObjetoDeJogo &) const ;
	
	void moveTo(unsigned posL, unsigned posC){ this->posL = posL; this->posC = posC;}
	void moveLeft()	{ moveTo(posL,posC-1); }
	void moveRight(){ moveTo(posL,posC+1); }
	void moveUp()	{ moveTo(posL-1,posC); }
	void moveDown()	{ moveTo(posL+1,posC); }
	
	std::string getName() const {return name;}
	unsigned getPosL() const {return posL;}
	unsigned getPosC() const {return posC;}
	SpriteBase *getSprite() {return pSprite;}
	
	void ativarObj() {this->active = true;};
	void desativarObj() {this->active = false;};
	
	//RenderBase
	virtual void init() {};
	virtual void update() {if (active) pSprite->update();}//lembrar de chamar esta nas derivadas...
	
	virtual void draw(SpriteBase &screen, unsigned x, unsigned y) {if (active) pSprite->draw(screen,x,y);}
private:
	std::string name;
	unsigned   posL, posC;
	SpriteBase *pSprite;
	
	bool active;
};

#endif // OBJETODEJOGO_HPP
