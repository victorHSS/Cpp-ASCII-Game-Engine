#include "Drawer.hpp"

#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>

#include <iostream>

#include "../Sprite.hpp"

SpriteBuffer Drawer::rectangle(unsigned largura, unsigned altura, char pencil, COR::Cor cor, char back)
{
	SpriteBuffer rect(largura,altura,back);
	rect.limits.clear();
	rect.colorHandler.clear();
	rect.colorHandler.setCor(cor);
	
	for (unsigned i = 0 ; i < altura ; i++)
	{
		if (i == 0 || i == altura - 1)
			for (unsigned j = 0 ; j < largura ; j++)
				rect.sprt[i][j] = pencil;
		else
			rect.sprt[i][0] = rect.sprt[i][largura-1] = pencil;
			
		rect.limits.push_back( {0,largura - 1,largura} );
		rect.colorHandler.pushCorLinha( 0, largura );
	}
	
	return rect;
}

SpriteBuffer Drawer::circle(int raio, char pencil, COR::Cor cor, char back)
{
	SpriteBuffer circ(raio * 2,raio * 2,back);
	circ.limits.clear();
	circ.colorHandler.clear();
	circ.colorHandler.setCor(cor);
	
	const double PI = 3.141596;
	double incr = (1.0 / raio);
	
	std::vector< std::pair<unsigned,unsigned> > vLimits(raio*2,{0,raio*2-1});
	
	for (double i = PI/2 ; i < PI ; i+=incr)
	{
		unsigned sinE = static_cast<unsigned>(round(raio - sin(i)*raio));
		unsigned sinD = static_cast<unsigned>(round(raio + sin(i)*raio) - 1);
		unsigned cosE = static_cast<unsigned>(round(raio - cos(i)*raio) - 1);
		unsigned cosD = static_cast<unsigned>(round(raio + cos(i)*raio));


		circ.sprt[sinD].at(cosE) = pencil;
		circ.sprt[sinE].at(cosE) = pencil;
		circ.sprt[sinD].at(cosD) = pencil;
		circ.sprt[sinE].at(cosD) = pencil;
		
		vLimits[sinD] = std::pair<unsigned,unsigned> (std::min(vLimits[sinD].second,cosD),std::max(vLimits[sinD].first,cosE));
		vLimits[sinE] = std::pair<unsigned,unsigned> (std::min(vLimits[sinE].second,cosD),std::max(vLimits[sinE].first,cosE));
	}
	for (int i = 0 ; i < raio * 2 ; i++)
	{
		circ.limits.push_back( {vLimits[i].first,vLimits[i].second,vLimits[i].second+1} );
		circ.colorHandler.pushCorLinha( vLimits[i].first, vLimits[i].second+1 );
	}

	return circ;
}

SpriteBuffer Drawer::box(unsigned largura, unsigned altura, COR::Cor cor, char back)
{
	SpriteBuffer rect(largura,altura,back);
	rect.limits.clear();
	rect.colorHandler.clear();
	
	rect.colorHandler.setCor(cor);
	
	for (unsigned i = 0 ; i < altura ; i++)
	{
		if (i == 0 || i == altura - 1)
			for (unsigned j = 0 ; j < largura ; j++)
				if (j==0 || j==largura-1)
					rect.sprt[i][j] = '+';
				else
					rect.sprt[i][j] = '-';
		else
			rect.sprt[i][0] = rect.sprt[i][largura-1] = '|';
			
		rect.limits.push_back( {0,largura - 1,largura} );
		rect.colorHandler.pushCorLinha( 0, largura );
	}
	
	return rect;
}

SpriteBuffer Drawer::textbox(const TextSprite &str, COR::Cor cor, char back)
{
	SpriteBuffer tbox = box(str.getLarguraMax() + 4, 3, cor, back);
	tbox.putCenter(str,1);
	
	return tbox;
}

SpriteBuffer Drawer::boxFromModel(std::string nomeArq, unsigned largura, unsigned altura, COR::Cor cor)
{
	Sprite sprt(nomeArq);
	
	if (sprt.getLarguraMax() % 2 == 0 || sprt.getAltura() % 2 == 0)
		throw DrawerError("Modelo deve ter um número ímpar de linhas e colunas.");
	
	const unsigned	midLarg{static_cast<unsigned>(sprt.getLarguraMax()/2)},
					midAlt{static_cast<unsigned>(sprt.getAltura()/2)};
					
	SpriteBuffer tbox(largura + midLarg * 2, altura + midAlt * 2, '.', cor);
	
	auto convA {
		[midAlt , altura](unsigned a)
		{
			if (a < midAlt)
				return a;
			
			if (a < midAlt + altura)
				return midAlt;
			
			return a - altura + 1;
		}
	};
	
	for (unsigned a{0} ; a < tbox.getAltura() ; a++)
	{
		for (unsigned l1{0} ; l1 < midLarg ; l1++)
		{
			tbox.sprt[a][l1] = sprt.sprt[convA(a)][l1];
			tbox.sprt[a][midLarg + largura + l1] = sprt.sprt[convA(a)][midLarg + l1 + 1];
		}
		
		for (unsigned lm{0} ; lm < largura ; lm++)
		{
			tbox.sprt[a][midLarg + lm] = sprt.sprt[convA(a)][midLarg];
		}
	}
	
	return tbox;
}