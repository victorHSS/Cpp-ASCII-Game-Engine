#include "Sprite.hpp"
#include <fstream>

std::ostream &operator<<(std::ostream &out, const Sprite &s)
{
	for (auto it = s.sprt.begin() ; it != s.sprt.end() ; ++it)
		std::cout << *it << std::endl;
	
	return out;
}


Sprite::Sprite(std::string nameFile) : SpriteBase()
{
	this->loadFromFile(nameFile);
}

Sprite::Sprite(std::ifstream &fsprt) : SpriteBase()
{
	this->loadFromFile(fsprt);
}

Sprite::Sprite(std::ifstream &fsprt, unsigned n) : SpriteBase()
{
	this->loadFromFile(fsprt, n);
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
	{	
		std::cout << "Erro ao ler arquivo..." << std::endl;
		return;
	}
	
	this->largura = 0;
	
	std::string tmp;
	
	while(getline(fsprt,tmp))
	{
		sprt.push_back(tmp);
		
		if (tmp.length() > this->largura)
			this->largura = tmp.length();
		
	}
	
	this->alturaSprite = this->sprt.size();
}

void Sprite::loadFromFile(std::ifstream &fsprt, unsigned n)
{
	this->sprt.clear();
	
	if (!fsprt.is_open())
	{	
		std::cout << "Erro ao ler arquivo..." << std::endl;
		return;
	}
	
	this->largura = 0;
	
	std::string tmp;
	
	//std::cout << "Carregado Sprite..." << n << std::endl; //apagar
	
	while(getline(fsprt,tmp) && n--)
	{
		sprt.push_back(tmp);
		
		//std::cout << ">" << tmp << "<" << std::endl; //apagar
		
		if (tmp.length() > this->largura)
			this->largura = tmp.length();
	}
	
	this->alturaSprite = this->sprt.size();
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
	//std::cout << "Entrei..." << std::endl; //apagar
	if (c >= this->largura)
		return;
	
	//std::cout << "Passei da largura..." << std::endl; //apagar
	
	//std::cout << sprt.getAltura() << std::endl; //apagar
	for (int i = 0 ; i < sprt.getAltura() ; i++)
	{
		//std::cout << "No looop..." << std::endl; //apagar
		
		if (i + l >= this->sprt.size())
			break;
		
		//std::cout << "Passei do if da linha..." << std::endl; //apagar
			
		std::string linha = sprt.getLinha(i);
		std::string alvo = this->sprt[l+i];
		this->sprt[l+i] = alvo.substr(0,c);
		this->sprt[l+i] += linha.substr(0,alvo.length()-c);
		this->sprt[l+i] += alvo.substr(c+linha.length(),alvo.length()-(c+linha.length()));
		
		//if (c+linha.length() < alvo.length())
		//	this->sprt[l+i] += alvo.substr(c+linha.length(),alvo.length()-(c+linha.length()));
		
		
		//std::cout << this->sprt[l+i] << std::endl;
	}
	//std::cout << "Saindo..." << std::endl; //apagar
}