#ifndef SPRITEBUFFER_HPP
#define SPRITEBUFFER_HPP

#include "core/SpriteBase.hpp"
#include <vector>

class Drawer;

class SpriteBuffer : public SpriteBase
{
	friend class Drawer;
	
	friend std::ostream &operator<<(std::ostream &, const SpriteBuffer &);
public:
	SpriteBuffer(unsigned = 0, unsigned = 0, char = ' ', COR::Cor = COR::PADRAO);
	virtual ~SpriteBuffer(){}
	
	void clear();
	
	void setBackChar(char backChar) {this->backChar = backChar;}
	
	//SpriteBase
	virtual SpriteBase *copia() const { return new SpriteBuffer(*this);}
	
	virtual int getLargura(unsigned l) const {return this->limits[l].largLinha;}
	
	//RenderBase
	virtual void init() {};
	virtual void update() {};
	
private:
	
	unsigned largura, altura;
	
	char backChar;
	
	//utilitárias
	void fillBack();
	
	//SpriteBase
	virtual std::string getLinha(unsigned) const;
};

#endif // SPRITEBUFFER_HPP
