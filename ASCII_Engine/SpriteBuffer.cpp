#include "SpriteBuffer.hpp"
#include <string>
#include <iostream>

std::ostream &operator<<(std::ostream &out, const SpriteBuffer &s)
{
	unsigned li{0};
	for (auto it = s.sprt.begin() ; it != s.sprt.end() ; ++it)
			out << s.colorHandler.colorir(*it, li++) << std::endl;
	return out;
}

SpriteBuffer::SpriteBuffer(unsigned largura, unsigned altura, COR::Cor cor) : SpriteBase(largura,altura,cor)
{
	clearBuffer();
}

void SpriteBuffer::clearBuffer()
{
	sprt.clear();
	for (unsigned i = 0 ; i < altura ; i++)
		sprt.push_back(std::string(largura,' '));
}

void SpriteBuffer::clear()
{
	clearBuffer();					// limpando buffer
	
	colorHandler.clearMapaCores(); 	// limpando cores
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
	if (c >= this->largura)	//se o objeto a ser desenhando estiver além da largura do destino, não faz nada.
		return;

	for (int i = 0 ; i < sprt.getAltura() ; i++)
	{
		
		if (i + l >= this->sprt.size()) //se o pedaço do sprite ultrapassar a altura do sprite destino, para
			break;
		
		std::string linha = sprt.getLinha(i);
		std::string alvo = this->sprt[l+i];
		this->sprt[l+i] = alvo.substr(0,c); //aproveita a linha base até o ponto onde vamos inserir o sprite novo
		this->sprt[l+i] += linha.substr(0,alvo.length()-c); //pega a porção do sprite novo que cabe na linha destino
		
		if ( c + linha.length() < alvo.length() ) //pega restante da base (alvo) se ainda puder
			this->sprt[l+i] += alvo.substr(c+linha.length(),alvo.length()-(c+linha.length()));
	}
	colorHandler.mergeCores(sprt.getColorHandler(),l,c);
}