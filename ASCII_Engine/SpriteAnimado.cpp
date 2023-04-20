#include "SpriteAnimado.hpp"

#include <fstream>
#include <string>

std::ostream &operator<<(std::ostream &out, const SpriteAnimado &sa)
{
	//printa apenas o sprite atual da animacao
	std::cout << sa.sprites[sa.iSpriteAnim] << std::endl;

	return out;
}

SpriteAnimado::SpriteAnimado(std::string nameFile, unsigned velAnim):SpriteBase()
{ 
	unsigned ns;
	
	this->velAnim = this->stepAnim = velAnim;
	this->iSpriteAnim = 0;
	
	std::ifstream fanm(nameFile.c_str(),std::ios::in);
	
	fanm >> numSprites >> alturaSprite;
	fanm.ignore(1,'\n');	// ignorando o \n que ficou no input da linha anterior
	
	ns = numSprites;
	while (ns--)
	{
		sprites.push_back(Sprite(fanm,alturaSprite));
		if (sprites.back().getLargura() > this->largura)
			this->largura = sprites.back().getLargura();
	}
	
	fanm.close();
}


Sprite SpriteAnimado::operator[](int i) const
{
	return sprites[i];
}

void SpriteAnimado::update()
{
	if (!--stepAnim)
	{
		stepAnim = velAnim;
		iSpriteAnim = (iSpriteAnim + 1) % numSprites;
	}
}

std::string SpriteAnimado::getLinha(unsigned l) const
{
	if (l < sprites[0].getAltura())
		return sprites[iSpriteAnim].getLinha(l);
	else 
		return "";
}

void SpriteAnimado::putAt(const SpriteBase &sprt, unsigned l, unsigned c)
{
	for (int i = 0 ; i < sprites.size() ; i++)
		sprites[i].putAt(sprt,l,c);
}
