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
				<< fc.height << " " << fc.width << std::endl;
			return out;
		}
	public:
		FontChar(std::string charF, size_t height, size_t width):
			charF{charF},
			height{height},
			width{width} {}

		~FontChar() = default;
		
		std::string getChar() const { return charF; }
		size_t getHeight() const { return height; }
		size_t getWidth() const { return width; }
		
	private:
		std::string charF;
		size_t height, width;
	};
	
	Font(std::string fontFile = "ASCII_Engine/assets/fonts/defaultFont.fnt");
	~Font() = default;
	
	FontChar operator[](std::string);
private:
	TextContainer font;
};

#endif // FONT_HPP
