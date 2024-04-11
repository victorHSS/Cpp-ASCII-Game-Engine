#ifndef TEXTSPRITE_HPP
#define TEXTSPRITE_HPP

#include <string>
#include "Core/SpriteBase.hpp"

class TextSprite : public SpriteBase
{
	friend std::ostream &operator<<(std::ostream &, const TextSprite &);
public:
	TextSprite(std::string text, COR::Cor cor = COR::PADRAO):SpriteBase(0,1,cor){setText(text);}
	
	~TextSprite(){}
	
	void setText(std::string text) {
		this->text = text;
		this->largura = text.length();
		limits.clear();
		limits.push_back(LIMITS(text.find_first_not_of(' '),text.find_last_not_of(' '),text.length()));
		colorHandler.clear();
		colorHandler.pushCorLinha(limits.back().front,limits.back().end + 1);
	}
	
	//SpriteBase
	virtual void putAt(const SpriteBase &, unsigned = 0, unsigned = 0);
	virtual std::string whoami() const {return "TextSprite";}
	
	//RenderBase
	virtual void init() {};
	virtual void update() {};
private:
	std::string text;
	
	//SpriteBase
	virtual std::string getLinha(unsigned) const;
};

#endif // TEXTSPRITE_HPP
