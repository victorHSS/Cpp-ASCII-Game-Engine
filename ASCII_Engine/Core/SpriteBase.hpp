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
	struct LIMITS {
		unsigned front, end, larg, head, tail, largLinha;
		LIMITS(unsigned f, unsigned e, unsigned l) : front(f), end(e), head(f),
													 tail(l - e - 1), larg(e - f + 1), largLinha(l) 
		{
			if (f == static_cast<unsigned>(std::string::npos))
				front = end = larg = head = tail = largLinha = 0;
		}
	};
	
public:
	SpriteBase(COR::Cor cor = COR::NULL_COLOR):colorHandler(cor) {}
	
	virtual ~SpriteBase(){}
	
	virtual unsigned getLargura(unsigned l) const {return this->limits[l].largLinha;}
	virtual unsigned getAltura() const {return this->limits.size();}
	
	virtual void putAt(const SpriteBase &, unsigned , unsigned) = 0;
	virtual void putCenter(const SpriteBase &sprt, unsigned l) { putAt(sprt,l,(limits[l].largLinha-sprt.getLimits()[l].largLinha)/2); }
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
	//unsigned largura, altura;
	
	std::vector< LIMITS > limits;
	
	ColorHandler colorHandler;
};

#endif // SPRITEBASE_HPP
