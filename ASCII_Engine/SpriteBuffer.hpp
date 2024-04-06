#ifndef SPRITEBUFFER_HPP
#define SPRITEBUFFER_HPP

#include "Core/SpriteBase.hpp"
#include <vector>

class SpriteBuffer : public SpriteBase
{
	friend std::ostream &operator<<(std::ostream &, const SpriteBuffer &);
public:
	SpriteBuffer(unsigned , unsigned , COR::Cor = COR::PADRAO);
	virtual ~SpriteBuffer(){}
	
	void clear();
	
	//SpriteBase
	virtual void putAt(const SpriteBase &, unsigned = 0, unsigned = 0);
	virtual std::string whoami() const {return "SpriteBuffer";}
	
	//RenderBase
	virtual void init() {};
	virtual void update() {};
	
private:
	std::vector<std::string> sprt;
	
	void clearBuffer();
	
	//SpriteBase
	virtual std::string getLinha(unsigned) const;
};

#endif // SPRITEBUFFER_HPP
