#ifndef SPRITEBASE_HPP
#define SPRITEBASE_HPP

#include "RenderBase.hpp"
#include "ColorHandler.hpp"
#include "Cores_base.hpp"

#include <string>
#include <vector>

class SpriteBase : public RenderBase
{
	//using MapaDeCores = std::vector< std::map<int,COR::Cor> >;
protected:
	struct LIMITS { unsigned front, end, larg, tail;
					LIMITS(unsigned f, unsigned e, unsigned l):
						  front(f),end(e),tail(l - e - 1), larg(l - f - (l - e - 1)) {} };
	
public:
	SpriteBase(unsigned largura=0, unsigned altura=0, COR::Cor cor = COR::PADRAO):largura(largura), altura(altura),
													colorHandler(cor) {}
	virtual ~SpriteBase(){}
	
	unsigned getLargura() const {return this->largura;}
	unsigned getAltura() const {return this->altura;}
	
	virtual void putAt(const SpriteBase &, unsigned , unsigned) = 0;
	virtual void putCenter(const SpriteBase &sprt, unsigned l) { putAt(sprt,l,(largura-sprt.largura)/2); }
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
	virtual void setCor(COR::Cor cor) { colorHandler.setCor(cor); }
	virtual const ColorHandler &getColorHandler() const { return colorHandler; } 
	
	//Transp
	virtual const std::vector< LIMITS > &getLimits() const {return limits;}

protected:
	unsigned largura, altura;
	
	std::vector< LIMITS > limits;
	
	ColorHandler colorHandler;
};

#endif // SPRITEBASE_HPP
