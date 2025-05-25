#ifndef RENDERBASE_HPP
#define RENDERBASE_HPP

class SpriteBase;

class RenderBase
{
public:
	RenderBase(){}
	virtual ~RenderBase(){}
	
	virtual void init() = 0;
	virtual void update() = 0;
	
	virtual void draw(SpriteBase &screen, int x, int y) = 0;

};

#endif // RENDERBASE_HPP
