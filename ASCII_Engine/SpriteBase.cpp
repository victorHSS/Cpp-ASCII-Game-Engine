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
		
		//std::cout << " Linha: " << iL << std::endl;
		
		//std::cout << " Mapa de cores do Sprite origem: ";
		//for (auto itC = oMapCol[iL-l].cbegin() ; itC != oMapCol[iL-l].cend() ; ++itC)
		//	std::cout << itC->first << " ";
		//std::cout << std::endl;		
		
		//std::cout << " Mapa de cores linha atual: ";
		//for (auto itC = mapaCores[iL].cbegin() ; itC != mapaCores[iL].cend() ; ++itC)
		//	std::cout << itC->first << " ";
		//std::cout << std::endl;
		
		auto itCorAnt = mapaCores[iL].cend(); //pega a cor da linha imediatamente antes do fim da largura do sprite
		auto itCorProx = mapaCores[iL].cbegin(); //pega a cor da linha imediatamente antes do fim da largura do sprite
		while (itCorProx != mapaCores[iL].cend() && itCorProx->first <= c + larg) {itCorAnt = itCorProx; ++itCorProx;}
		COR::Cor corAnt = (itCorAnt != mapaCores[iL].cend()?itCorAnt->second:COR::PADRAO); 
		//std::cout << " >>> c = " << c << " Cor Ant: " << (itCorAnt != mapaCores[iL].cend()?itCorAnt->first:-1) << std::endl;
		
		
		mapaCores[iL].erase(mapaCores[iL].upper_bound(c),mapaCores[iL].lower_bound(c+larg));
		
		//std::cout << " Mapa de cores linha atual após erase: ";
		///for (auto itC = mapaCores[iL].cbegin() ; itC != mapaCores[iL].cend() ; ++itC)
		//	std::cout << itC->first << " ";
		//std::cout << std::endl;
		
		//std::cin.get();
		
		//std::cout << " Merging..." << std::endl;
		for (auto itC = oMapCol[iL-l].cbegin() ; itC != oMapCol[iL-l].cend() ; ++itC)
		{
			if (c + itC->first > this->largura)
				break;
				
			mapaCores[iL][c + itC->first] = itC->second;
		}
		
		if ( c + larg <= this->largura )
			mapaCores[iL][c + larg] = corAnt;
			
		//std::cout << " Mapa de cores linha atual após merge: ";
		//for (auto itC = mapaCores[iL].cbegin() ; itC != mapaCores[iL].cend() ; ++itC)
		//	std::cout << itC->first << " ";
		//std::cout << std::endl;
		
		//std::cin.get();
	}
}