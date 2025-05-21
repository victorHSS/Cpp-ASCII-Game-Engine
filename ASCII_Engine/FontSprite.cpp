#include "FontSprite.hpp"
#include "utils/Font.hpp"

FontSprite::FontSprite(std::string text, const Font &font, size_t wOffset, size_t hOffset, COR::Cor cor) :
	: SpriteBase(cor), font{font}, wOffset{wOffset}, hOffset{hOffset}
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
	}
	
	size_t altChar{font[text[0]].getHeight()};
	size_t spaceChar{ 3 * wOffset };
	
	size_t posL{0};
	
	for (const auto& subt : text | std::ranges::views::split('\n')) //cada linha do texto
	{
		size_t posC{0};
		std::string line{subt.cbegin(),subt.cend()}, lRes{};
		for (size_t l{} ; l < altChar ; l++)
		{
			for (char &ch : line)
			{
				if (ch == " ")
					lRes = std::string(spaceChar + 2*wOffset, ' ');
				else
					lRes = font[ch].getValue();//MUDAR A LOGICA pq getValue retorna o char com \n
				sprt.push_back(lRes);
				
			}
		}
		sprt.push_back("\n");
	}
	sprt.pop_back(); // remove último \n
	
}