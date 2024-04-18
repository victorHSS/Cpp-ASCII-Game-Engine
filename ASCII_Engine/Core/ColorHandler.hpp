#ifndef COLOR_HANDLER_HPP
#define COLOR_HANDLER_HPP

#include <string>

#include <vector>
#include <map>

#include "Cores_base.hpp"

class ColorHandler {
	
public:

	using MapaDeCores = std::vector< std::map<int,COR::Cor> >;

	ColorHandler(COR::Cor cor):cor(cor) {}

	void setCor(COR::Cor cor) { this->cor = cor; clearMapaCores(); }
	COR::Cor getCorBase() const { return cor; }
	
	void pushCorLinha(unsigned front, unsigned end ) {mapaCores.push_back( { {front,cor}, {end,COR::PADRAO} } );}
	void pushLinhaSemCor() {mapaCores.push_back( { } ); }
	
	int getAltura() const { return mapaCores.size(); }
	int getLargura(int l) const;
	
	void mergeCores(const ColorHandler &, int, int);
	
	const MapaDeCores &getMapaCores() const { return mapaCores; }
	
	std::string colorir(const std::string &, unsigned) const;
	
	void clear() { mapaCores.clear(); }
	
	//void clearMapaCores();

private:
	COR::Cor cor; //cor base
	
	void clearMapaCores();
	
	MapaDeCores mapaCores;
};

#endif