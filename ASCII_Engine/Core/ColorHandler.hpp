#ifndef COLOR_HANDLER_HPP
#define COLOR_HANDLER_HPP

#include <string>

#include <vector>
#include <map>

#include "Cores_base.hpp"

class ColorHandler {
	
public:

	using MapaDeCores = std::vector< std::map<int,COR::Cor> >;


	ColorHandler(unsigned largura, unsigned altura, COR::Cor cor = COR::NULL_COLOR):
				largura(largura),altura(altura) { setCor(cor); }
				
	void setCor(COR::Cor cor) { this->cor = cor; clearMapaCores(); }
	COR::Cor getCorBase() const { return cor; }
	
	unsigned getAltura() const { return altura; }
	unsigned getLargura() const { return largura; }
	
	//void mergeCores(const MapaDeCores &, unsigned, unsigned);
	void mergeCores(const ColorHandler &, unsigned, unsigned);
	
	const MapaDeCores &getMapaCores() const { return mapaCores; }
	
	std::string colorir(const std::string &, unsigned) const;
	
	void clearMapaCores();

private:
	COR::Cor cor; //cor base
	unsigned altura, largura;
	
	MapaDeCores mapaCores;
};

#endif