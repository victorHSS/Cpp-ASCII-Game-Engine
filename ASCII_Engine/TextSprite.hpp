#ifndef TEXTSPRITE_HPP
#define TEXTSPRITE_HPP

#include <string>
#include "Core/SpriteBase.hpp"

class TextSprite : public SpriteBase
{
	friend std::ostream &operator<<(std::ostream &, const TextSprite &);
public:
	TextSprite(std::string text, COR::Cor cor = COR::PADRAO):SpriteBase(text.length(),1, cor) {this->text = text;limits.push_back(LIMITS(text.find_first_not_of(' '),text.find_last_not_of(' '),text.length()));}
	~TextSprite(){}
	
	void setText(std::string text) {this->text = text;this->largura = text.length();limits[0] = (LIMITS(text.find_first_not_of(' '),text.find_last_not_of(' '),text.length()));}
	
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
