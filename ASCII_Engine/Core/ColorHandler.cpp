#include "ColorHandler.hpp"

#include <string>
#include <cstring>

#include <iostream>

#include <stdexcept>

std::string ColorHandler::colorir(const std::string &linha, unsigned li) const
{
	std::string lColorida(linha.size() + mapaCores[li].size()*strlen(COR::BRANCA),'\0');
	lColorida.insert(0, linha);
	
	unsigned comp{0};
	
	for (auto itL = mapaCores[li].cbegin() ; itL != mapaCores[li].cend() ; ++itL) {
		lColorida.insert(itL->first + comp, itL->second);
		comp += strlen(itL->second);
	}
	
	return lColorida;
}

unsigned ColorHandler::getLargura(unsigned l) const
{
	if (l >= mapaCores.size())
		throw std::runtime_error("Linha inexistente no mapa de cores.");
	return mapaCores[l].rbegin()->first;
}

void ColorHandler::clearMapaCores()
{	
	for (int i = 0 ; i < getAltura() ; i++) 
		mapaCores[i] = std::map<int,COR::Cor>( { {mapaCores[i].begin()->first,cor}, {mapaCores[i].rbegin()->first,COR::PADRAO} } );
}

void ColorHandler::mergeCores(const ColorHandler &oCoHa, unsigned l, unsigned c)
{
	const MapaDeCores &oMapCol = oCoHa.getMapaCores();
	
	
	for (int iL = l ; iL < l + oCoHa.getAltura() ; iL++)
	{
		if (iL >= this->getAltura())
			break;
		
		unsigned larg = oCoHa.getLargura(iL-l);
		
		auto itCorAnt = mapaCores[iL].cend();
		auto itCorProx = mapaCores[iL].cbegin();
		while (itCorProx != mapaCores[iL].cend() && itCorProx->first <= c + larg) {itCorAnt = itCorProx; ++itCorProx;}
		
		COR::Cor corAnt = (itCorAnt != mapaCores[iL].cend()?itCorAnt->second:COR::PADRAO); 
		
		mapaCores[iL].erase(mapaCores[iL].upper_bound(c),mapaCores[iL].lower_bound(c+larg));
		
		for (auto itC = oMapCol[iL-l].cbegin() ; itC != oMapCol[iL-l].cend() ; ++itC)
		{
			//if (c + itC->first > this->getLargura(iL)) //retirei e funcionou, mas revisar...
			//	break;
				
			mapaCores[iL][c + itC->first] = itC->second;
		}
		
		if ( c + larg <= this->getLargura(iL))
			mapaCores[iL][c + larg] = corAnt;
	}
}