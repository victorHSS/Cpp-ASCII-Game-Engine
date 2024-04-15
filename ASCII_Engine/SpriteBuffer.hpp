#ifndef SPRITEBUFFER_HPP
#define SPRITEBUFFER_HPP

#include "Core/SpriteBase.hpp"
#include <vector>

class SpriteBuffer : public SpriteBase
{
	friend std::ostream &operator<<(std::ostream &, const SpriteBuffer &);
public:
	SpriteBuffer(unsigned , unsigned , char = ' ', COR::Cor = COR::PADRAO);
	virtual ~SpriteBuffer(){}
	
	void clear();
	
	//SpriteBase
	virtual void putAt(const SpriteBase &, int = 0, int = 0);
	virtual std::string whoami() const {return "SpriteBuffer";}
	
	virtual int getLargura(unsigned l) const {return this->limits[l].largLinha;}
	
	//RenderBase
	virtual void init() {};
	virtual void update() {};
	
private:

	unsigned largura, altura;

	std::vector<std::string> sprt;
	
	char backChar;
	
	void clearBuffer();
	
	//SpriteBase
	virtual std::string getLinha(unsigned) const;
};

#endif // SPRITEBUFFER_HPP
