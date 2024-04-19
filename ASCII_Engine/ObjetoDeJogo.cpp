#include "ObjetoDeJogo.hpp"

#include <algorithm>

ObjetoDeJogo::ObjetoDeJogo(const ObjetoDeJogo &o) : name(o.name),posL(o.posL),posC(o.posC),active(true)
{
	pSprite = o.pSprite->copia();
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
		
		pSprite = o.pSprite->copia();
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
			if (obj.posC + obj.getSprite()->getLimits()[l-maxPosLini].front <= 
				posC + pSprite->getLimits()[l-maxPosLini].end &&
				obj.posC + obj.getSprite()->getLimits()[l-maxPosLini].end >= 
				posC + pSprite->getLimits()[l-maxPosLini].front )
				
				return true;
	}
	
	return false;
}
