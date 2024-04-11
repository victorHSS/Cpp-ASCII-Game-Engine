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
	//colorHandler = ColorHandler(cor);
}

Sprite::Sprite(std::ifstream &fsprt, COR::Cor cor) : SpriteBase(cor)
{
	this->loadFromFile(fsprt);
	//colorHandler = ColorHandler(cor);
}

Sprite::Sprite(std::ifstream &fsprt, unsigned n, COR::Cor cor) : SpriteBase(cor)
{
	this->loadFromFile(fsprt, n);
	//colorHandler = ColorHandler(cor);
}

void Sprite::loadFromFile(std::string nameFile)
{
	std::ifstream fsprt(nameFile.c_str(),std::ios::in);
	
	loadFromFile(fsprt);
	
	fsprt.close();
}

void Sprite::loadFromFile(std::ifstream &fsprt)
{
	this->sprt.clear();
	
	if (!fsprt.is_open())
		throw std::runtime_error("Erro ao ler arquivo de Sprite...");
	
	this->largura = 0;
	
	std::string tmp;
	
	while(getline(fsprt,tmp))
	{
		sprt.push_back(tmp);
		
		limits.push_back(LIMITS(tmp.find_first_not_of(' '),tmp.find_last_not_of(' '),tmp.length()));
		colorHandler.pushCorLinha( limits.back().front, limits.back().end + 1 );
		
		if (tmp.length() > this->largura)
			this->largura = tmp.length();
		
	}
	
	this->altura = this->sprt.size();
}

void Sprite::loadFromFile(std::ifstream &fsprt, unsigned n)
{
	this->sprt.clear();
	
	if (!fsprt.is_open())
		throw std::runtime_error("Erro ao ler arquivo de Sprite...");
	
	this->largura = 0;
	
	std::string tmp;
	
	int nn = n;
	while(getline(fsprt,tmp) && nn--)
	{
		sprt.push_back(tmp);
		
		limits.push_back(LIMITS(tmp.find_first_not_of(' '),tmp.find_last_not_of(' '),tmp.length()));
		colorHandler.pushCorLinha( limits.back().front, limits.back().end + 1 );
		
		if (tmp.length() > this->largura)
			this->largura = tmp.length();
	}
	
	if ( (!fsprt && nn > 0) || (fsprt && nn >= 0) )
		throw std::runtime_error("Sprite Incompleto...");
	
	this->altura = this->sprt.size();
}

std::string Sprite::getLinha(unsigned l) const
{
	if (l < sprt.size())
		return sprt[l];
	else 
		return "";
}

void Sprite::putAt(const SpriteBase &sprt, unsigned l, unsigned c)
{
	if (c >= this->largura)	//se o objeto a ser desenhando estiver além da largura do destino, não faz nada.
		return;

	for (int i = 0 ; i < sprt.getAltura() ; i++)
	{
		
		if (i + l >= this->sprt.size()) //se o pedaço do sprite ultrapassar a altura do sprite destino, para
			break;
		
		std::string alvo = this->sprt[l+i];
		std::string linha = sprt.getLinha(i);
		
		this->sprt[l+i] = alvo.substr(0,c+sprt.getLimits()[i].front); //aproveita a linha base até o ponto onde vamos inserir o sprite novo
		this->sprt[l+i] += linha.substr(sprt.getLimits()[i].front,std::min(sprt.getLimits()[i].larg,static_cast<unsigned>(alvo.length()-c-sprt.getLimits()[i].front) )); //pega a porção do sprite novo que cabe na linha destino
		
		if ( c + linha.length() - sprt.getLimits()[i].tail < alvo.length() ) //pega restante da base (alvo) se ainda puder
			this->sprt[l+i] += alvo.substr(c+linha.length() - sprt.getLimits()[i].tail,alvo.length()-(c+linha.length())+sprt.getLimits()[i].tail);
		
		/*
		this->sprt[l+i] = alvo.substr(0,c); //aproveita a linha base até o ponto onde vamos inserir o sprite novo
		this->sprt[l+i] += linha.substr(0,alvo.length()-c); //pega a porção do sprite novo que cabe na linha destino
		
		if ( c + linha.length() < alvo.length() ) //pega restante da base (alvo) se ainda puder
			this->sprt[l+i] += alvo.substr(c+linha.length(),alvo.length()-(c+linha.length()));
		*/
	}
	colorHandler.mergeCores(sprt.getColorHandler(),l,c);
}