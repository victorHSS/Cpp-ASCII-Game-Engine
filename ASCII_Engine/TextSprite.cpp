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
	
	for (int si = sprt.getLimits()[0].front ; si <= sprt.getLimits()[0].end ; si++)
		if (c + si < this->limits[0].largLinha)
			this->text[c+si] = sprt.getLinha(0)[si];
	
	colorHandler.mergeCores(sprt.getColorHandler(),l,c);
}