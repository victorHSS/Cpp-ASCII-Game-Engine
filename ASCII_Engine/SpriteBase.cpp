#include "SpriteBase.hpp"

#include <iostream> //apagarrr


void SpriteBase::clearMapaCores()
{
	//std::map<int,COR::Cor> map = { {0,cor}, {largura,COR::PADRAO} };
	mapaCores.clear();
	
	for (int i = 0 ; i < alturaSprite ; i++)
		mapaCores.push_back( { {0,cor}, {largura,COR::PADRAO} } );
}

void SpriteBase::mergeCores(const MapaDeCores &oMapCol, unsigned l, unsigned c, unsigned a, unsigned b)
{
	//std::cout << "Entrei no mergeCores." << std::endl;
	unsigned alt  = oMapCol.size();
	unsigned larg = oMapCol[0].crbegin()->first;
	
	//std::cout << "Altura: " << alt << " Largura: " << larg << std::endl;
	//std::cin.get();
	
	for (int iL = l ; iL < l + alt ; iL++)
	{
		if (iL >= this->alturaSprite)
			break;
		
		auto itCorAnt = mapaCores[iL].lower_bound(c); //pega a cor da linha imediatamente antes do sprite
		COR::Cor corAnt = (itCorAnt != mapaCores[iL].end()?itCorAnt->second:COR::PADRAO); 
		
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