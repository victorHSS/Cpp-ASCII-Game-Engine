#ifndef SPRITEBASE_HPP
#define SPRITEBASE_HPP

#include "RenderBase.hpp"
#include "Cores.hpp"
#include <string>

class SpriteBase : public RenderBase
{
public:
	SpriteBase(unsigned largura=0, unsigned altura=0):largura(largura),alturaSprite(altura),colorido(false),cor(COR::PADRAO){}
	virtual ~SpriteBase(){}
	
	unsigned getLargura() const {return this->largura;}
	unsigned getAltura() const {return this->alturaSprite;}
	
	virtual void putAt(const SpriteBase &, unsigned , unsigned) = 0;
	//virtual void putCenter(const SpriteBase &, unsigned) = 0; //acho que essas eu consiga ja implementar aqui
	//virtual void putLeft(const SpriteBase &, unsigned) = 0;
	//virtual void putRight(const SpriteBase &, unsigned) = 0;
	//virtual void appendLeft(const SpriteBase &) = 0;
	//virtual void appendRight(const SpriteBase &) = 0;
	
	virtual std::string getLinha(unsigned) const = 0;
	
	virtual std::string whoami() const = 0;
	
	//RenderBase
	virtual void init() = 0;
	virtual void update() = 0;
	
	virtual void draw(SpriteBase &screen, unsigned x, unsigned y){screen.putAt(*this,x,y);}
	
	//Cores
	void setCor(COR::COR cor) { colorido = true; this->cor = cor; }
	

protected:
	unsigned largura, alturaSprite;
	
	//Coloração
	bool colorido;
	COR::COR cor;
	
};

#endif // SPRITEBASE_HPP
