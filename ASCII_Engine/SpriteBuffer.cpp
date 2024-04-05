#include "SpriteBuffer.hpp"
#include <string>
#include <iostream>

std::ostream &operator<<(std::ostream &out, const SpriteBuffer &s)
{
	
	//
	//  Ficou um pouco custoso, o print dessa forma. Analisar como fazer otimizações e como se comporta num jogo real
	//	Talvez injetar primeiro na string as cores antes de printar otimize, mas não sei
	//
	
	int li = 0;
	for (auto it = s.sprt.begin() ; it != s.sprt.end() ; ++it){
		auto itCores = s.mapaCores[li].cbegin();
		auto itCoresFim = s.mapaCores[li].cend();
		int i;
		for (i = 0 ; i < it->size() ; i++){
			while (itCores != itCoresFim && itCores->first < i) ++itCores;
			if (itCores != itCoresFim && itCores->first == i)
				std::cout << itCores->second;
			//auto itCor = s.mapaCores[li].find(i);
			//if (itCor != itCoresFim)
			//	std::cout << itCor->second;
			std::cout << (*it)[i];
		}
		std::cout << std::endl;
		li++;
	}
	return out;
}

SpriteBuffer::SpriteBuffer(unsigned largura, unsigned altura) : SpriteBase(largura,altura)
{
	clear();
}

void SpriteBuffer::clear()
{
	sprt.clear();
	for (unsigned i = 0 ; i < alturaSprite ; i++)
		sprt.push_back(std::string(largura,' '));
}

std::string SpriteBuffer::getLinha(unsigned l) const
{
	if (l < sprt.size())
		return sprt[l];
	else 
		return "";
}

void SpriteBuffer::putAt(const SpriteBase &sprt, unsigned l, unsigned c)
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
	mergeCores(sprt.getMapaCores(),l,c,0,0);
}