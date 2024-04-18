#include "ObjetoDeJogo.hpp"

#include <algorithm>

ObjetoDeJogo::ObjetoDeJogo(const ObjetoDeJogo &o) : name(o.name),posL(o.posL),posC(o.posC),active(true)
{
	//trick
	if (o.pSprite->whoami() == "Sprite")
		pSprite = new Sprite(*(dynamic_cast<Sprite*>(o.pSprite)));
	else if (o.pSprite->whoami() == "SpriteAnimado")
		pSprite = new SpriteAnimado(*(dynamic_cast<SpriteAnimado*>(o.pSprite)));
	else if (o.pSprite->whoami() == "TextSprite")
		pSprite = new TextSprite(*(dynamic_cast<TextSprite*>(o.pSprite)));
	else if (o.pSprite->whoami() == "SpriteBuffer")
		pSprite = new SpriteBuffer(*(dynamic_cast<SpriteBuffer*>(o.pSprite)));
}

const ObjetoDeJogo &ObjetoDeJogo::operator=(const ObjetoDeJogo &o)
{
	if (this != &o) //evita auto-atribuicao
	{
		this->name = o.name;
		this->posL = o.posL;
		this->posC = o.posC;
		this->active = o.active;
		delete this->pSprite;
		
		//trick
		if (o.pSprite->whoami() == "Sprite")
			pSprite = new Sprite(*(dynamic_cast<Sprite*>(o.pSprite)));
		else if (o.pSprite->whoami() == "SpriteAnimado")
			pSprite = new SpriteAnimado(*(dynamic_cast<SpriteAnimado*>(o.pSprite)));
		else if (o.pSprite->whoami() == "TextSprite")
			pSprite = new TextSprite(*(dynamic_cast<TextSprite*>(o.pSprite)));
		else if (o.pSprite->whoami() == "SpriteBuffer")
			pSprite = new SpriteBuffer(*(dynamic_cast<SpriteBuffer*>(o.pSprite)));
	}
	return *this;
}

bool ObjetoDeJogo::colideCom(const ObjetoDeJogo &obj) const
{
	if (active && obj.active)
		return (
		(obj.posL < posL + pSprite->getAltura() &&
		 obj.posL + obj.getSprite()->getAltura() > posL) &&
		(obj.posC < posC + pSprite->getLarguraMax() &&
		 obj.posC + obj.getSprite()->getLarguraMax() > posC)
		);
	
	return false;
}

bool ObjetoDeJogo::colideComBordas(const ObjetoDeJogo &obj) const
{
	if (active && obj.active)
	{
		int maxPosLini = std::max(posL,obj.posL);
		int minPosLfim = std::min(posL+pSprite->getAltura(),obj.posL+obj.getSprite()->getAltura());
		for (int l = maxPosLini ; l < minPosLfim ; l++)
			if (obj.posC + obj.getSprite()->getLimits()[l].front <= posC + pSprite->getLimits()[l].end &&
				obj.posC + obj.getSprite()->getLimits()[l].end >= posC + pSprite->getLimits()[l].front)
				
				return true;
	}
	
	return false;
}
