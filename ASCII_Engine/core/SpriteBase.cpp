#include "SpriteBase.hpp"

void SpriteBase::putAt(const SpriteBase &sprt, int l, int c)
{
	for (int i = 0 ; i < sprt.getAltura() ; i++)
	{
		if (i + l < 0) 					//se a linha atual estiver antes do sprite, avança
			continue;
		
		if (i + l >= this->getAltura()) //se o pedaço do sprite ultrapassar a altura do sprite destino, para
			break;
		
		if (c >= this->getLargura(i))	//se o objeto a ser desenhando estiver além da largura do destino, faz nada.
			break;
			
		if (!sprt.getLimits()[i].largLinha) //se linha do objeto foz vazia, faz nada
			continue;
		
		for (int si = sprt.getLimits()[i].front ; si <= sprt.getLimits()[i].end ; si++) {
			if (c + si >= 0 && c + si < this->limits[i].largLinha)
				this->sprt[l+i][c+si] = sprt.getLinha(i)[si];
		}
	}
	colorHandler.mergeCores(sprt.getColorHandler(),l,c);
}