#include "SpriteBuffer.hpp"
#include <string>
#include <iostream>

std::ostream &operator<<(std::ostream &out, const SpriteBuffer &s)
{
	for (auto it = s.sprt.begin() ; it != s.sprt.end() ; ++it)
		std::cout << *it << std::endl;
	
	return out;
}

SpriteBuffer::SpriteBuffer(unsigned largura, unsigned altura) : SpriteBase(largura,altura)
{
	clear();
}

void SpriteBuffer::clear()
{
	sprt.clear();
	for (unsigned i = 0 ; i < alturaSprite ; i++)
		sprt.push_back(std::string(largura,' '));
}

std::string SpriteBuffer::getLinha(unsigned l) const
{
	if (l < sprt.size())
		return sprt[l];
	else 
		return "";
}

void SpriteBuffer::putAt(const SpriteBase &sprt, unsigned l, unsigned c)
{
	
	if (c >= this->largura)
		return;
	
	for (int i = 0 ; i < sprt.getAltura() ; i++)
	{
		
		if (i + l >= this->sprt.size())
			break;
		
		std::string linha = sprt.getLinha(i);
		std::string alvo = this->sprt[l+i];
		this->sprt[l+i] = alvo.substr(0,c);
		this->sprt[l+i] += linha.substr(0,alvo.length()-c);
		this->sprt[l+i] += alvo.substr(c+linha.length(),alvo.length()-(c+linha.length()));
		
	}
}