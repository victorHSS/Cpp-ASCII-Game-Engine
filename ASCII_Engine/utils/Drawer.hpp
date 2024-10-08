#ifndef DRAWER_HPP
#define DRAWER_HPP

#include "../SpriteBuffer.hpp"
#include "../TextSprite.hpp"

#include <string>
#include <stdexcept>

class DrawerError : public std::runtime_error {
public:
	DrawerError(const char *error) : std::runtime_error(error) {}
};

class Drawer {

public:

	static SpriteBuffer rectangle(unsigned, unsigned, char = '*', COR::Cor = COR::PADRAO, char = ' ');
	static SpriteBuffer circle(int, char = '*', COR::Cor = COR::PADRAO, char = ' ');
	//static SpriteBuffer line(int, int , char = '*', char = ' ');
	
	static SpriteBuffer box(unsigned, unsigned, COR::Cor = COR::PADRAO, char = ' ');
	static SpriteBuffer textbox(const TextSprite &, COR::Cor = COR::PADRAO, char = ' ');
	static SpriteBuffer boxFromModel(std::string, unsigned, unsigned, COR::Cor = COR::PADRAO);
	
	//...
};

#endif