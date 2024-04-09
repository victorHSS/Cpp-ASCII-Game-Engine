#include "ColorHandler.hpp"

#include <string>
#include <cstring>

#include <iostream>

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


void ColorHandler::clearMapaCores()
{
	mapaCores.clear();
	
	for (int i = 0 ; i < altura ; i++)
		mapaCores.push_back( { {0,cor}, {largura,COR::PADRAO} } ); //{ pair<int,COR::Cor>, pair<int,COR::Cor> }
}

void ColorHandler::mergeCores(const ColorHandler &oCoHa, unsigned l, unsigned c)
{
	const MapaDeCores &oMapCol = oCoHa.getMapaCores();
	unsigned larg = oCoHa.getLargura();
	
	for (int iL = l ; iL < l + oCoHa.getAltura() ; iL++)
	{
		if (iL >= this->altura)
			break;
		
		auto itCorAnt = mapaCores[iL].cend();
		auto itCorProx = mapaCores[iL].cbegin();
		while (itCorProx != mapaCores[iL].cend() && itCorProx->first <= c + larg) {itCorAnt = itCorProx; ++itCorProx;}
		
		COR::Cor corAnt = (itCorAnt != mapaCores[iL].cend()?itCorAnt->second:COR::PADRAO); 
		
		mapaCores[iL].erase(mapaCores[iL].upper_bound(c),mapaCores[iL].lower_bound(c+larg));
		
		for (auto itC = oMapCol[iL-l].cbegin() ; itC != oMapCol[iL-l].cend() ; ++itC)
		{
			if (c + itC->first > this->largura)
				break;
				
			mapaCores[iL][c + itC->first] = itC->second;
		}
		
		if ( c + larg <= this->largura )
			mapaCores[iL][c + larg] = corAnt;
	}
}