#include "FontSprite.hpp"
#include "utils/Font.hpp"

#include <ranges>
#include <format>

std::ostream &operator<<(std::ostream &out, const FontSprite &s)
{
	unsigned li{0};
	out << "\"\n";
	for (auto it = s.sprt.begin() ; it != s.sprt.end() ; ++it)
		out <<  s.colorHandler.colorir(*it, li++) << ": Chars-> " << it->size() << std::endl;
	out << "\"\nTotal Linhas: " << s.sprt.size() << std::endl;
	return out;
}

FontSprite::FontSprite(std::string text, size_t wOffset, size_t hOffset, const Font &font, COR::Cor cor)
	: SpriteBase(cor), wOffset{wOffset}, hOffset{hOffset}, font{font}
{
	setText(text);
}

void FontSprite::setText(std::string text)
{
	if (text.empty())
	{
		sprt.clear();
		colorHandler.clear();
		limits.clear();
		return;
	}
	
	size_t altChar{ font[text[0]].getHeight() };
	size_t spaceChar{ (!wOffset)?1:wOffset };
	
	size_t posL{0};
	
	for (const auto& subt : text | std::ranges::views::split('\n')) //cada linha do texto
	{
		size_t posC{0};
		std::string line{subt.begin(),subt.end()}, lRes{};
		
		//offset de linha
		if (posL) {
			for (size_t i{0} ; i < hOffset ; i++)
			{
				sprt.push_back("");
				limits.push_back(LIMITS(0,0,0));
				colorHandler.pushLinhaSemCor();
			}
			posL += hOffset;
		}
		
		for (const char ch : line)
		{
			size_t largChar{}, localL{0};
			
			if (ch == ' ')
			{
				largChar = spaceChar;
				
				for (size_t lSpace{0} ; lSpace < altChar ; lSpace++)
				{
					if (!posC) //se começo de linha
						sprt.push_back(std::string(largChar, ' '));
					else
						sprt[posL + localL] += std::string(wOffset + spaceChar, ' '); // add wOffset + spacesize
						
					localL++;
				}
			}
			else
			{
				largChar = font[ch].getWidth();
				
				for (const auto& linhaChar : font[ch].getChar() | std::ranges::views::split('\n'))
				{
					if (!posC) //se começo de linha
						sprt.emplace_back(linhaChar.begin(), linhaChar.end());
					else
						sprt[posL + localL] += std::string(wOffset, ' ') // add wOffset
											+  std::string{linhaChar.begin(), linhaChar.end()};
					
					localL++;
				}
			}
			posC += ( (posC) ? (wOffset + largChar) : (largChar) );
		}
		
		for (size_t i{0} ; i < altChar ; i++)
		{
			limits.push_back(LIMITS(0,posC - 1,posC));
			colorHandler.pushCorLinha(limits.back().front,limits.back().end + 1);
		}
		
		posL += altChar;
	}
}