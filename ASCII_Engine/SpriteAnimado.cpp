#include "SpriteAnimado.hpp"

#include <fstream>
#include <string>

std::ostream &operator<<(std::ostream &out, const SpriteAnimado &sa)
{
	//printa apenas o sprite atual da animacao
	out << sa.sprites[sa.iSpriteAnim] << std::endl;

	return out;
}

SpriteAnimado::SpriteAnimado(std::string nameFile, unsigned velAnim, COR::Cor cor):SpriteBase(cor)
{ 
	int ns, altura;
	
	this->velAnim = this->stepAnim = velAnim;
	this->iSpriteAnim = 0;
	
	std::ifstream fanm(nameFile.c_str(),std::ios::in);
	
	if (!fanm.is_open())
		throw std::runtime_error("Erro ao ler arquivo de SpriteAnimado...");
	
	if (!(fanm >> numSprites >> altura))
		throw std::runtime_error("Erro na estrutura de arquivo de SpriteAnimado...");
	
	fanm.ignore(1,'\n');	// ignorando o \n que ficou no input da linha anterior
	
	ns = numSprites;
	while (ns--)
	{
		try {
			sprites.push_back(Sprite(fanm,altura,cor));
		} catch(std::runtime_error &e) {
			throw std::runtime_error("Erro na estrutura de arquivo de SpriteAnimado. Sprite incompleto...");
		}
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
	if (l < sprites[iSpriteAnim].getAltura())
		return sprites[iSpriteAnim].getLinha(l);
	else 
		return "";
}

void SpriteAnimado::putAt(const SpriteBase &sprt, int l, int c)
{
	for (int i = 0 ; i < sprites.size() ; i++)
		sprites[i].putAt(sprt,l,c);
}

void SpriteAnimado::setCor(COR::Cor cor)
{
	for (int i = 0 ; i < sprites.size() ; i++)
		sprites[i].colorHandler.setCor(cor);
}