#include "SpriteBuffer.hpp"
#include <string>
#include <iostream>
#include <algorithm>


std::ostream &operator<<(std::ostream &out, const SpriteBuffer &s)
{
	unsigned li{0};
	for (auto it = s.sprt.begin() ; it != s.sprt.end() ; ++it)
			out << s.colorHandler.colorir(*it, li++) << std::endl;
	return out;
}

SpriteBuffer::SpriteBuffer(unsigned largura, unsigned altura, char backChar, COR::Cor cor) : SpriteBase(largura,altura,cor), backChar(backChar)
{
	clearBuffer();
}

void SpriteBuffer::clearBuffer()
{
	sprt.clear();
	colorHandler.clear();
	for (unsigned i = 0 ; i < getAltura() ; i++) {
		sprt.push_back(std::string(getLargura(),backChar));
		limits.push_back(LIMITS(0,getLargura() - 1,getLargura()));
		colorHandler.pushCorLinha( 0, getLargura() );
	}
}

void SpriteBuffer::clear()
{
	clearBuffer();						// limpando buffer
	
	//colorHandler.clearMapaCores(); 	// limpando cores
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
	if (c >= this->getLargura())	//se o objeto a ser desenhando estiver além da largura do destino, não faz nada.
		return;

	for (int i = 0 ; i < sprt.getAltura() ; i++)
	{
		if (i + l >= this->sprt.size()) //se o pedaço do sprite ultrapassar a altura do sprite destino, para
			break;
		
		for (int si = sprt.getLimits()[i].front ; si <= sprt.getLimits()[i].end ; si++)
			if (c + si < this->limits[i].largLinha)
				this->sprt[l+i][c+si] = sprt.getLinha(i)[si];
	}
	colorHandler.mergeCores(sprt.getColorHandler(),l,c);
}