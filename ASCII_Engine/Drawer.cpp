#include "Drawer.hpp"

#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>

#include <iostream>

SpriteBuffer Drawer::rectangle(unsigned largura, unsigned altura, char pencil, char back)
{
	SpriteBuffer rect(largura,altura,back);
	rect.limits.clear();
	rect.colorHandler.clear();
	
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

SpriteBuffer Drawer::circle(int raio, char pencil, char back)
{
	SpriteBuffer circ(raio * 2,raio * 2,back);
	circ.limits.clear();
	circ.colorHandler.clear();
	
	const double PI = 3.141596;
	double incr = (1.0 / raio);
	
	std::vector< std::pair<int,int> > vLimits(raio*2,{0,raio*2-1});
	
	for (double i = PI/2 ; i < PI ; i+=incr)
	{
		int sinE = static_cast<int>(round(raio - sin(i)*raio));
		int sinD = static_cast<int>(round(raio + sin(i)*raio) - 1);
		int cosE = static_cast<int>(round(raio - cos(i)*raio) - 1);
		int cosD = static_cast<int>(round(raio + cos(i)*raio));
		/*
		std::cout << "Ang " << i << " l1 " << sinE
							<< " l2 " << sinD
							<< " c1 " << cosE
							<< " c2 " << cosD << std::endl;
		*/
		circ.sprt[sinD].at(cosE) = pencil;
		circ.sprt[sinE].at(cosE) = pencil;
		circ.sprt[sinD].at(cosD) = pencil;
		circ.sprt[sinE].at(cosD) = pencil;
		
		vLimits[sinD] = std::pair<int,int> (std::min(vLimits[sinD].second,cosD),std::max(vLimits[sinD].first,cosE));
		vLimits[sinE] = std::pair<int,int> (std::min(vLimits[sinE].second,cosD),std::max(vLimits[sinE].first,cosE));
	}
	for (int i = 0 ; i < raio * 2 ; i++)
	{
		circ.limits.push_back( {vLimits[i].first,vLimits[i].second,vLimits[i].second+1} );
		circ.colorHandler.pushCorLinha( vLimits[i].first, vLimits[i].second+1 );
	}
	/*
	std::cout << "-----" << std::endl;
	for (int i = 0 ; i < raio * 2 ; i++)
	{
		for (int j = 0 ; j < raio * 2 ; j++)
			std::cout << circ.sprt[i][j];
		std::cout << "|" << vLimits[i].first << " " << vLimits[i].second << std::endl;
	}
	std::cout << "-----" << std::endl;
	std::cin.get();
	*/
	return circ;
}

SpriteBuffer Drawer::line(int x, int y, char pencil, char back)
{
	
}

SpriteBuffer Drawer::box(unsigned largura, unsigned altura, char back)
{
	
}