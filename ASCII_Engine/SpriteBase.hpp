#ifndef SPRITEBASE_HPP
#define SPRITEBASE_HPP

#include "RenderBase.hpp"
#include "Cores.hpp"
#include <string>

#include <vector>
#include <map>

class SpriteBase : public RenderBase
{
	using MapaDeCores = std::vector< std::map<int,COR::Cor> >;
	
public:
	SpriteBase(unsigned largura=0, unsigned altura=0):largura(largura),altura(altura),
													cor(COR::PADRAO){clearMapaCores();}
	virtual ~SpriteBase(){}
	
	unsigned getLargura() const {return this->largura;}
	unsigned getAltura() const {return this->altura;}
	
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
	void setCor(COR::Cor cor) { this->cor = cor; clearMapaCores(); }
	
	void mergeCores(const MapaDeCores &, unsigned, unsigned);
	const MapaDeCores &getMapaCores() const { return mapaCores; }
	void clearMapaCores();
	

protected:
	unsigned largura, altura;
	
	//Coloração
	COR::Cor cor; //cor base
	
	//mapa de cores
	MapaDeCores mapaCores;
	
};

#endif // SPRITEBASE_HPP
