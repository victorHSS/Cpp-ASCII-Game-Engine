#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include <string>
#include <iostream>

#include "SpriteBase.hpp"

class Sprite : public SpriteBase
{
	friend class SpriteAnimado;
	
	//temporarios
	friend std::ostream &operator<<(std::ostream &, const Sprite &);
	
public:
	Sprite(std::string);
	Sprite(std::ifstream &);
	Sprite(std::ifstream &,unsigned);
	virtual ~Sprite(){}
	
	void loadFromFile(std::string);
	void loadFromFile(std::ifstream &);
	void loadFromFile(std::ifstream &,unsigned);
	
	//SpriteBase
	virtual void putAt(const SpriteBase &, unsigned = 0, unsigned = 0);
	virtual std::string whoami() const {return "Sprite";}
	
	//RenderBase
	virtual void init() {};
	virtual void update() {};
	

private:
	std::vector<std::string> sprt;
	
	//SpriteBase
	virtual std::string getLinha(unsigned) const;
};

#endif // SPRITE_HPP
