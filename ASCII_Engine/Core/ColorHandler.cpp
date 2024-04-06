#include "ColorHandler.hpp"

#include <string>
#include <cstring>

#include <iostream>

std::string ColorHandler::colorir(const std::string &linha, unsigned li) const
{
	//std::string lColorida(linha.size() + mapaCores[li].size()*strlen(COR::BRANCA),'\0');
	//lColorida.insert(0, linha);
	std::string lColorida(linha);
	
	for (auto itL = mapaCores[li].cbegin() ; itL != mapaCores[li].cend() ; ++itL)
		lColorida.insert(itL->first, itL->second);
	
	return lColorida;

}


void ColorHandler::clearMapaCores()
{
	mapaCores.clear();
	
	for (int i = 0 ; i < altura ; i++)
		mapaCores.push_back( { {0,cor}, {largura,COR::PADRAO} } ); //{ pair<int,COR::Cor>, pair<int,COR::Cor> }
}

#define DEBUG 0

void ColorHandler::mergeCores(const ColorHandler &oCoHa, unsigned l, unsigned c)
{
	/*
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
	 * */
	
	// codigo antigo
	#if DEBUG
		std::cout << "Entrei no mergeCores." << std::endl;
	#endif
	const MapaDeCores &oMapCol = oCoHa.getMapaCores();
	#if DEBUG
		std::cout << "Peguei oMapCol." << std::endl;
	#endif
	unsigned alt  = oMapCol.size();
	#if DEBUG
		std::cout << "Peguei alt: " << alt << std::endl;
	#endif
	unsigned larg = oMapCol[0].crbegin()->first;
	#if DEBUG
		std::cout << "Peguei larg: " << larg<< std::endl;
	#endif
	
	#if DEBUG
	std::cin.get();
	#endif
	
	
	for (int iL = l ; iL < l + alt ; iL++)
	{
		if (iL >= this->altura)
			break;
		
		#if DEBUG
		std::cout << " Linha: " << iL << std::endl;
		
		std::cout << " Mapa de cores do Sprite origem: ";
		for (auto itC = oMapCol[iL-l].cbegin() ; itC != oMapCol[iL-l].cend() ; ++itC)
			std::cout << itC->first << " ";
		std::cout << std::endl;		
		
		std::cout << " Mapa de cores linha atual: ";
		for (auto itC = mapaCores[iL].cbegin() ; itC != mapaCores[iL].cend() ; ++itC)
			std::cout << itC->first << " ";
		std::cout << std::endl;
		#endif
		
		auto itCorAnt = mapaCores[iL].cend(); 
		auto itCorProx = mapaCores[iL].cbegin(); 
		while (itCorProx != mapaCores[iL].cend() && itCorProx->first <= c + larg) {itCorAnt = itCorProx; ++itCorProx;}
		COR::Cor corAnt = (itCorAnt != mapaCores[iL].cend()?itCorAnt->second:COR::PADRAO); 
		
		#if DEBUG
		std::cout << " >>> c = " << c << " Cor Ant: " << (itCorAnt != mapaCores[iL].cend()?itCorAnt->first:-1) << std::endl;
		#endif
		
		mapaCores[iL].erase(mapaCores[iL].upper_bound(c),mapaCores[iL].lower_bound(c+larg));
		
		#if DEBUG
		std::cout << " Mapa de cores linha atual após erase: ";
		for (auto itC = mapaCores[iL].cbegin() ; itC != mapaCores[iL].cend() ; ++itC)
			std::cout << itC->first << " ";
		std::cout << std::endl;
		
		//std::cin.get();
		
		std::cout << " Merging..." << std::endl;
		#endif
		
		
		for (auto itC = oMapCol[iL-l].cbegin() ; itC != oMapCol[iL-l].cend() ; ++itC)
		{
			if (c + itC->first > this->largura)
				break;
				
			mapaCores[iL][c + itC->first] = itC->second;
		}
		
		if ( c + larg <= this->largura )
			mapaCores[iL][c + larg] = corAnt;
		
		#if DEBUG
		std::cout << " Mapa de cores linha atual após merge: ";
		for (auto itC = mapaCores[iL].cbegin() ; itC != mapaCores[iL].cend() ; ++itC)
			std::cout << itC->first << " ";
		std::cout << std::endl;
		
		std::cin.get();
		#endif
	}
}