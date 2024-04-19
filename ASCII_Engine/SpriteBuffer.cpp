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

void SpriteBuffer::putAt(const SpriteBase &sprt, int l, int c)
{
	for (int i = 0 ; i < sprt.getAltura() ; i++)
	{

		if (i + l < 0) 					//se a linha atual estiver antes do sprite, avança
			continue;
		
		if (i + l >= this->getAltura()) //se o pedaço do sprite ultrapassar a altura do sprite destino, para
			break;
		
		if (c >= this->getLargura(i))	//se o objeto a ser desenhando estiver além da largura do destino, faz nada.
			break;
			
		if (!sprt.getLimits()[i].largLinha) //se linha do objeto foz vazia, faz nada
			continue;
		
		for (int si = sprt.getLimits()[i].front ; si <= sprt.getLimits()[i].end ; si++) {
			if (c + si >= 0 && c + si < this->limits[i].largLinha)
				this->sprt[l+i][c+si] = sprt.getLinha(i)[si];
		}
	}
	colorHandler.mergeCores(sprt.getColorHandler(),l,c);
}