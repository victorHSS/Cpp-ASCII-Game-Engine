#ifndef FONT_HPP
#define FONT_HPP

#include "TextContainer.hpp"
#include <iostream>
#include <string>

class Font
{
public:

	class FontChar
	{
		friend std::ostream &operator<<(std::ostream &out, const FontChar &fc)
		{
			out << fc.charF << std::endl 
				<< fc.heigth << " " << fc.width << std::endl;
			return out;
		}
	public:
		FontChar(std::string charF, size_t heigth, size_t width):
			charF{charF},
			heigth{heigth},
			width{width} {}

		~FontChar() = default;
		
		std::string getChar() const { return charF; }
		size_t getHeigth() const { return heigth; }
		size_t getWidth() const { return width; }
		
	private:
		std::string charF;
		size_t heigth, width;
	};
	
	Font(std::string fontFile = "ASCII_Engine/assets/fonts/defaultFont.fnt");
	~Font() = default;
	
	FontChar operator[](std::string);
private:
	TextContainer font;
};

#endif // FONT_HPP
