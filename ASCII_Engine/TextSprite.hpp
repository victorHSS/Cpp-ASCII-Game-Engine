#ifndef TEXTSPRITE_HPP
#define TEXTSPRITE_HPP

#include <string>
#include "Core/SpriteBase.hpp"

class TextSprite : public SpriteBase
{
	friend std::ostream &operator<<(std::ostream &, const TextSprite &);
public:
	TextSprite(std::string text, COR::Cor cor = COR::PADRAO):SpriteBase(cor){setText(text);}
	
	~TextSprite(){}
	
	void setText(std::string text);
	
	//SpriteBase
	virtual void putAt(const SpriteBase &, int = 0, int = 0);
	virtual SpriteBase *copia() const { return new TextSprite(*this);}
	
	//RenderBase
	virtual void init() {};
	virtual void update() {};
private:
	std::string text;
	
	//SpriteBase
	virtual std::string getLinha(unsigned) const;
};

#endif // TEXTSPRITE_HPP
