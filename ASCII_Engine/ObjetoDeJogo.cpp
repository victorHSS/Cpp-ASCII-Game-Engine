#include "ObjetoDeJogo.hpp"

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
		(obj.posL <= posL + pSprite->getAltura() &&
		 obj.posL + pSprite->getAltura() >= posL) &&
		(obj.posC <= posC + pSprite->getLargura() &&
		 obj.posC + pSprite->getLargura() >= posC)
		);
	
	return false;
}
