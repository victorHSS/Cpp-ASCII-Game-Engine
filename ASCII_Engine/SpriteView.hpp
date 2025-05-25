#ifndef SPRITEVIEW_HPP
#define SPRITEVIEW_HPP

#include "core/SpriteBase.hpp"

/*
 *  O SpriteView está implementado de forma que o view possa "sair"
 * da área do spritebase. Isso pode ser ajustado no moveTo, analisando se
 * a nova posição permite que o view permaneça dentro dos limites do
 * sprite base.
 * 
 */

class SpriteView : public SpriteBase
{
public:
	SpriteView(SpriteBase &spbase, int lin, int col, int height, int width, COR::Cor cor = COR::NULL_COLOR);
	~SpriteView() = default;
	
	void moveTo(int l, int c);
	void moveLeft(int qpos = 1)	 { moveTo(lin,col-qpos); }
	void moveRight(int qpos = 1) { moveTo(lin,col+qpos); }
	void moveUp(int qpos = 1)	 { moveTo(lin-qpos,col); }
	void moveDown(int qpos = 1)	 { moveTo(lin+qpos,col); }
	
	void setAltura(int height);
	void setLargura(int width);
	
	virtual SpriteView *copia() const { return new SpriteView{*this}; }
	
	virtual void putAt(const SpriteBase &, int , int);
	
	//RenderBase
	virtual void init() {};
	virtual void update() {}; //o SpriteView é apenas um observador passivo
	virtual void draw(SpriteBase &screen, int x, int y){screen.putAt(*this,x+lin,y-col);}
	
private:
	SpriteBase &spbase;
	int lin, col;
	int height, width;
	
	virtual std::string getLinha(unsigned l) const;
};

#endif // SPRITEVIEW_HPP
