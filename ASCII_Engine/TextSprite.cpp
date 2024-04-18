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

void TextSprite::setText(std::string text) {
	this->text = text;
	limits.clear();
	limits.push_back(LIMITS(0,text.length()-1,text.length()));
	colorHandler.clear();
	colorHandler.pushCorLinha(limits.back().front,limits.back().end + 1);
}

void TextSprite::putAt(const SpriteBase &sprt, int l, int c)
{
	if (l != 0 || c >= this->text.length())
		return;
	
	for (int si = sprt.getLimits()[0].front ; si <= sprt.getLimits()[0].end ; si++)
		if (c + si < this->limits[0].largLinha)
			this->text[c+si] = sprt.getLinha(0)[si];
	
	colorHandler.mergeCores(sprt.getColorHandler(),l,c);
}