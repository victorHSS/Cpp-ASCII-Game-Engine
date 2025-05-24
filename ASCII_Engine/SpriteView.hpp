#ifndef SPRITEVIEW_HPP
#define SPRITEVIEW_HPP

#include "Core/SpriteBase.hpp"

class SpriteView : public SpriteBase
{
public:
	SpriteView(SpriteBase &spbase, int lin, int col, int height, int width, COR::Cor cor = COR::NULL_COLOR);
	~SpriteView() = default;
	
	void moveTo(int l, int c);
	void setAltura(int height);
	void setLargura(int width);
	
	virtual SpriteView *copia() const { return new SpriteView{*this}; }
	
	virtual void putAt(const SpriteBase &, int , int);
	
	//RenderBase
	virtual void init() {};
	virtual void update() final {}; //o SpriteView é apenas um observador passivo
	
private:
	SpriteBase &spbase;
	int lin, col;
	int height, width;
	
	virtual std::string getLinha(unsigned l) const;
};

#endif // SPRITEVIEW_HPP
