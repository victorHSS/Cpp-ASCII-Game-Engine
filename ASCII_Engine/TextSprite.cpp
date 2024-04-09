#include "TextSprite.hpp"
#include <iostream>

std::ostream &operator<<(std::ostream &out, const TextSprite &ts)
{
	out << ts.colorHandler.colorir(ts.text, 0) << std::endl;
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
	
	/*nao precisa de transparencia em texto
	this->text = alvo.substr(0,c+sprt.getLimits()[0].front); //aproveita a linha base até o ponto onde vamos inserir o sprite novo
	this->text += linha.substr(sprt.getLimits()[0].front,std::min(sprt.getLimits()[0].larg,static_cast<unsigned>(alvo.length()-c-sprt.getLimits()[0].front) )); //pega a porção do sprite novo que cabe na linha destino
	
	if ( c + linha.length() - sprt.getLimits()[0].tail < alvo.length() ) //pega restante da base (alvo) se ainda puder
		this->text += alvo.substr(c+linha.length() - sprt.getLimits()[0].tail,alvo.length()-(c+linha.length())+sprt.getLimits()[0].tail);
	*/
	
	
	this->text = alvo.substr(0,c);
	this->text += linha.substr(0,alvo.length()-c);
	
	if ( c + linha.length() < alvo.length() ) //pega restante da base (alvo) se ainda puder
		this->text += alvo.substr(c+linha.length(),alvo.length()-(c+linha.length()));
	
	colorHandler.mergeCores(sprt.getColorHandler(),l,c);
}