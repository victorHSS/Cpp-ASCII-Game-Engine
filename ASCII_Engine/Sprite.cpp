#include "Sprite.hpp"
#include <fstream>

#include <stdexcept>
#include <algorithm>

std::ostream &operator<<(std::ostream &out, const Sprite &s)
{
	unsigned li{0};
	for (auto it = s.sprt.begin() ; it != s.sprt.end() ; ++it)
		out << s.colorHandler.colorir(*it, li++) << std::endl;
	
	return out;
}

Sprite::Sprite(std::string nameFile, COR::Cor cor) : SpriteBase(cor)
{
	this->loadFromFile(nameFile);
}

Sprite::Sprite(std::ifstream &fsprt, int n, COR::Cor cor) : SpriteBase(cor)
{
	this->loadFromFile(fsprt, n);
}

void Sprite::loadFromFile(std::string nameFile)
{
	std::ifstream fsprt(nameFile.c_str(),std::ios::in);
	
	loadFromFile(fsprt);
	
	fsprt.close();
}

void Sprite::loadFromFile(std::ifstream &fsprt, int n)
{
	bool flagIgnoreN = (n == -1);
	std::string tmp;
	
	this->sprt.clear();
	this->limits.clear();
	this->colorHandler.clear();
	
	if (!fsprt.is_open())
		throw std::runtime_error("Erro ao ler arquivo de Sprite...");
	
	while(getline(fsprt,tmp) && (flagIgnoreN || n--) )
	{
		sprt.push_back(tmp);
		
		limits.push_back(LIMITS(tmp.find_first_not_of(' '),tmp.find_last_not_of(' '),tmp.length()));
		
		if (limits.back().larg != 0)
			colorHandler.pushCorLinha( limits.back().front, limits.back().end + 1 );
		else
			colorHandler.pushLinhaSemCor();
	}
	
	if ( (!fsprt && n > 0) || (fsprt && n >= 0) )
		throw std::runtime_error("Sprite Incompleto...");
}

std::string Sprite::getLinha(unsigned l) const
{
	if (l < sprt.size())
		return sprt[l];
	else 
		return "";
}

void Sprite::putAt(const SpriteBase &sprt, int l, int c)
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