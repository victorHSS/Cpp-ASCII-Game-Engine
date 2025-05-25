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

SpriteBuffer::SpriteBuffer(unsigned largura, unsigned altura, char backChar, COR::Cor cor) : 
							largura(largura), altura(altura),SpriteBase(cor), backChar(backChar)
{
	clear();
}

void SpriteBuffer::fillBack()
{
	sprt.clear();
	limits.clear();
	colorHandler.clear();
	for (unsigned i = 0 ; i < altura ; i++)
		sprt.push_back(std::string(largura,backChar));
}

void SpriteBuffer::clear()
{
	sprt.clear();
	limits.clear();
	colorHandler.clear();
	for (unsigned i = 0 ; i < altura ; i++) {
		sprt.push_back(std::string(largura,backChar));
		limits.push_back(LIMITS(0,largura - 1,largura));
		colorHandler.pushCorLinha( 0, largura );
	}
}

std::string SpriteBuffer::getLinha(unsigned l) const
{
	if (l < sprt.size())
		return sprt[l];
	else 
		return "";
}