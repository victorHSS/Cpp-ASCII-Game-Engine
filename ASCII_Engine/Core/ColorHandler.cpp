#include "ColorHandler.hpp"

#include <string>
#include <cstring>

#include <stdexcept>

#include <algorithm>

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

int ColorHandler::getLargura(int l) const
{
	if (l < 0 && l >= mapaCores.size())
		throw std::runtime_error("Linha inexistente no mapa de cores.");
	return mapaCores[l].rbegin()->first;
}

void ColorHandler::clearMapaCores()
{
	for (int i = 0 ; i < getAltura() ; i++)
	{
		if (!mapaCores[i].size()) continue;
		
		mapaCores[i] = std::map<int,COR::Cor>( { {mapaCores[i].begin()->first,cor}, {mapaCores[i].rbegin()->first,COR::PADRAO} } );
	}
}

void ColorHandler::mergeCores(const ColorHandler &oCoHa, int l, int c)
{
	const MapaDeCores &oMapCol = oCoHa.getMapaCores();
	
	for (int iL = std::max(0,l) ; iL < l + oCoHa.getAltura() ; iL++)
	{
		if (iL >= this->getAltura())
			break;
		
		if (!oCoHa.mapaCores[(iL-l)].size()) continue;		//se não tem cor pra trazer, prox
		unsigned larg = oCoHa.getLargura(iL-l);
		unsigned largThis = getLargura(iL-l);
		
		//descobrindo cor anterior ao limite da largura da linha que está chegando
		auto itCorAnt = mapaCores[iL].cend();
		auto itCorProx = mapaCores[iL].cbegin();
		while (itCorProx != mapaCores[iL].cend() && itCorProx->first <= c + larg) {itCorAnt = itCorProx; ++itCorProx;}
		
		COR::Cor corAnt = (itCorAnt != mapaCores[iL].cend()?itCorAnt->second:COR::PADRAO); 
		
		mapaCores[iL].erase(mapaCores[iL].upper_bound(oCoHa.mapaCores[(iL-l)].cbegin()->first + c) , mapaCores[iL].lower_bound(c+larg));
		
		for (auto itC = oMapCol[iL-l].cbegin() ; itC != oMapCol[iL-l].cend() ; ++itC)
		{
			if (c + itC->first >= largThis) {		//se a cor estiver passando...
				mapaCores[iL][largThis] = corAnt;
				break;
			}
				
			if (c + itC->first < 0) {
				mapaCores[iL][0] = itC->second;
				continue;
			}
			
			mapaCores[iL][c + itC->first] = itC->second;
		}
		
		if ( c + larg < largThis )
			mapaCores[iL][c + larg] = corAnt;
	}
}