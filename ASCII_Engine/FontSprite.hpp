#ifndef FONTSPRITE_HPP
#define FONTSPRITE_HPP

#include <string>
#include <iostream>
#include "core/SpriteBase.hpp"
#include "utils/Font.hpp"
#include "SpriteBuffer.hpp"

class FontSprite : public SpriteBase
{
	friend std::ostream &operator<<(std::ostream &, const FontSprite &);
public:
	FontSprite(std::string text, size_t wOffset = 1ul, size_t hOffset = 1ul, const Font &font = Font{}, COR::Cor cor = COR::PADRAO);
	~FontSprite() = default;
	
	void setText(std::string text);
	
	//SpriteBase
	virtual SpriteBase *copia() const { return new FontSprite(*this);}
	
	//RenderBase
	virtual void init() {};
	virtual void update() {};
private:
	Font font;
	size_t wOffset, hOffset;
	
	//SpriteBase
	virtual std::string getLinha(unsigned l) const { return ( ( l < sprt.size() ) ? sprt[l] : "" ); }
};

#endif // FONTSPRITE_HPP
