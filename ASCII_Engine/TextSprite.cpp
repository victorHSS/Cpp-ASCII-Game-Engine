#include "TextSprite.hpp"
#include <iostream>

std::ostream &operator<<(std::ostream &out, const TextSprite &ts)
{
	out << ts.text << std::endl;
	return out;
}

std::string TextSprite::getLinha(unsigned l) const
{
	if (l == 0)
		return text;
	else 
		return "";
}

void TextSprite::putAt(const SpriteBase &sprt, unsigned l, unsigned c)
{
	if (l != 0 || c >= this->text.length())
		return;
		
	std::string linha = sprt.getLinha(0);
	std::string alvo = this->text;
	
	this->text = alvo.substr(0,c);
	this->text += linha.substr(0,alvo.length()-c);
	
	if ( c + linha.length() < alvo.length() ) //pega restante da base (alvo) se ainda puder
		this->text += alvo.substr(c+linha.length(),alvo.length()-(c+linha.length()));
}