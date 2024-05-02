#ifndef SPRITEBASE_HPP
#define SPRITEBASE_HPP

#include "RenderBase.hpp"
#include "ColorHandler.hpp"
#include "Cores_base.hpp"

#include <string>
#include <vector>

class SpriteBase : public RenderBase
{
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
	
	virtual SpriteBase *copia() const = 0;

    virtual int getLarguraMaxFit() const {
		unsigned lm{0};
		for (auto itL = limits.cbegin() ; itL != limits.end() ; ++itL)
			lm = (itL->end + 1 > lm)?itL->end + 1:lm;
		return lm;
	}
	
	virtual int getLarguraMax() const {
		unsigned lm{0};
		for (auto itL = limits.cbegin() ; itL != limits.end() ; ++itL)
			lm = (itL->largLinha > lm)?itL->largLinha:lm;
		return lm;
	}
	
	virtual int getLargura(unsigned l) const {return this->limits[l].largLinha;}
	virtual int getAltura() const {return this->limits.size();}
	
	virtual void putAt(const SpriteBase &, int , int) = 0;
	virtual void putCenter(const SpriteBase &sprt, int l) { putAt(sprt,l,(getLarguraMax()-sprt.getLarguraMax())/2); }
	//virtual void putCenter(const SpriteBase &sprt, int l) { putAt(sprt,l,(limits[l].largLinha-sprt.getLimits()[l].largLinha)/2); }
	//virtual void putLeft(const SpriteBase &sprt, int l) { putAt(sprt,l,0); }
	//virtual void putRight(const SpriteBase &sprt, int l) { putAt(sprt,l,limits[l].largLinha-sprt.limits[l]); };
	//virtual void appendLeft(const SpriteBase &) = 0;
	//virtual void appendRight(const SpriteBase &) = 0;
	
	virtual std::string getLinha(unsigned) const = 0;
	
	//RenderBase
	virtual void init() = 0;
	virtual void update() = 0;
	
	virtual void draw(SpriteBase &screen, int x, int y){screen.putAt(*this,x,y);}
	
	//Cores
	virtual void setCor(COR::Cor cor) { colorHandler.setCor(cor); }
	virtual const ColorHandler &getColorHandler() const { return colorHandler; } 
	
	//Transp
	virtual const std::vector< LIMITS > &getLimits() const {return limits;}

protected:
	
	std::vector< LIMITS > limits;
	
	ColorHandler colorHandler;
};

#endif // SPRITEBASE_HPP
