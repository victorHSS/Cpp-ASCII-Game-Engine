#include "Drawer.hpp"

#include <cmath>

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
	SpriteBuffer circ(raio * 2+1,raio * 2+1,back);
	circ.limits.clear();
	circ.colorHandler.clear();
	
	const double PI = 3.141596;
	
	for (double i = 0 ; i < 2*PI ; i+=.1)
	{
		std::cout << "Ang " << i << " l " << raio + static_cast<int>((sin(i)*raio)) 
							<< " c " << raio + static_cast<int>((cos(i)*raio)) << std::endl;
		circ.sprt[raio + static_cast<int>((sin(i)*raio))][raio + static_cast<int>((cos(i)*raio))] = pencil;
	}
	for (int i = 0 ; i < raio * 2+1 ; i++)
	{
		for (int j = 0 ; j < raio * 2+1 ; j++)
			std::cout << circ.sprt[i][j];
		std::cout << std::endl;
	}
	std::cin.get();
	
	return circ;
}

SpriteBuffer Drawer::line(int x, int y, char pencil, char back)
{
	
}

SpriteBuffer Drawer::box(unsigned largura, unsigned altura, char back)
{
	
}