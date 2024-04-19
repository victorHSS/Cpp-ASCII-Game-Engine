#ifndef DRAWER_HPP
#define DRAWER_HPP

#include "SpriteBuffer.hpp"

class Drawer {

public:

	static SpriteBuffer rectangle(unsigned, unsigned, char = '*', char = ' ');
	static SpriteBuffer circle(int, char = '*', char = ' ');
	static SpriteBuffer line(int, int , char = '*', char = ' ');
	
	static SpriteBuffer box(unsigned, unsigned, char = ' ');

};

#endif