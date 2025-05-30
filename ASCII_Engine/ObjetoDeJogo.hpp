#ifndef OBJETODEJOGO_HPP
#define OBJETODEJOGO_HPP

#include "core/RenderBase.hpp"
#include "core/SpriteBase.hpp"
#include "SpriteBuffer.hpp"
#include "Sprite.hpp"
#include "SpriteAnimado.hpp"
#include "TextSprite.hpp"

#include <string>

class ObjetoDeJogo : public RenderBase
{
public:
	ObjetoDeJogo(std::string name, const SpriteBase &s, int posL, int posC) : 
		name(name),pSprite(s.copia()),posL(posL),posC(posC),active(true) {}
	
	ObjetoDeJogo(const ObjetoDeJogo&);
	
	virtual ~ObjetoDeJogo(){ if (pSprite) delete pSprite;}
	
	const ObjetoDeJogo &operator=(const ObjetoDeJogo &);
	
	bool colideCom(const ObjetoDeJogo &) const;			//considera os limites do sprite (quadrado)
	bool colideComBordas(const ObjetoDeJogo &) const;	//considera as linhas do desenho propriamente dito
	
	void moveTo(int posL, int posC){ this->posL = posL; this->posC = posC;}
	void moveLeft(int qpos=1)	{ moveTo(posL,posC-qpos); }
	void moveRight(int qpos=1)	{ moveTo(posL,posC+qpos); }
	void moveUp(int qpos=1)		{ moveTo(posL-qpos,posC); }
	void moveDown(int qpos=1)	{ moveTo(posL+qpos,posC); }
	
	std::string getName() const {return name;}
	int getPosL() const {return posL;}
	int getPosC() const {return posC;}
	const SpriteBase *getSprite() const {return pSprite;}
	
	void ativarObj() 	{this->active = true;};
	void desativarObj() {this->active = false;};
	
	bool getActive() const { return this->active; }
	
	//RenderBase
	virtual void init() {};
	//lembrar de chamar update nas derivadas se elas sobrescreverem
	virtual void update() {if (pSprite && active) pSprite->update();} 
	
	virtual void draw(SpriteBase &screen, int x, int y) {if (pSprite && active) pSprite->draw(screen,x,y);}

protected:
	ObjetoDeJogo(std::string name, int posL, int posC) : 
		name(name),
		pSprite(nullptr),
		posL(posL),
		posC(posC),
		active(true) {}
	
	void setSprite(SpriteBase *pSprite) { if (this->pSprite) delete this->pSprite; this->pSprite = pSprite; };

private:
	std::string name;
	int	posL, posC;
	SpriteBase *pSprite;
	
	bool active;
};

#endif // OBJETODEJOGO_HPP
