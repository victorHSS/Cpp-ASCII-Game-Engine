#ifndef DRAWER_HPP
#define DRAWER_HPP

#include "../SpriteBuffer.hpp"
#include "../TextSprite.hpp"
#include <string>
class Drawer {

public:

	static SpriteBuffer rectangle(unsigned, unsigned, char = '*', COR::Cor = COR::PADRAO, char = ' ');
	static SpriteBuffer circle(int, char = '*', COR::Cor = COR::PADRAO, char = ' ');
	static SpriteBuffer box(unsigned, unsigned, COR::Cor = COR::PADRAO, char = ' ');
	static SpriteBuffer textbox(const TextSprite &, COR::Cor = COR::PADRAO, char = ' ');
	//static SpriteBuffer line(int, int , char = '*', char = ' ');
	//...
};

#endif