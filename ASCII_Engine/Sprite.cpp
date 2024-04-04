#include "Sprite.hpp"
#include <fstream>

#include <stdexcept>
#include <algorithm>

std::ostream &operator<<(std::ostream &out, const Sprite &s)
{
	for (auto it = s.sprt.begin() ; it != s.sprt.end() ; ++it)
		std::cout << (s.colorido?s.cor:"") << *it << (s.colorido?COR::PADRAO:"") << std::endl;
	
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
		throw std::runtime_error("Erro ao ler arquivo de Sprite...");
	
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
		throw std::runtime_error("Erro ao ler arquivo de Sprite...");
	
	this->largura = 0;
	
	std::string tmp;
		
	while(getline(fsprt,tmp) && n--)
	{
		sprt.push_back(tmp);
				
		if (tmp.length() > this->largura)
			this->largura = tmp.length();
	}
	
	if (n > 0)
		throw std::runtime_error("Sprite Incompleto...");
	
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
	if (c >= this->largura)	//se o objeto a ser desenhando estiver além da largura do destino, não faz nada.
		return;

	for (int i = 0 ; i < sprt.getAltura() ; i++)
	{
		
		if (i + l >= this->sprt.size()) //se o pedaço do sprite ultrapassar a altura do sprite destino, para
			break;
		
		std::string linha = sprt.getLinha(i);
		std::string alvo = this->sprt[l+i];
		this->sprt[l+i] = alvo.substr(0,c); //aproveita a linha base até o ponto onde vamos inserir o sprite novo
		this->sprt[l+i] += linha.substr(0,alvo.length()-c); //pega a porção do sprite novo que cabe na linha destino
		
		if ( c + linha.length() < alvo.length() ) //pega restante da base (alvo) se ainda puder
			this->sprt[l+i] += alvo.substr(c+linha.length(),alvo.length()-(c+linha.length()));
	}
}