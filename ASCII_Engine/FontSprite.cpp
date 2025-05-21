#include "FontSprite.hpp"
#include "utils/Font.hpp"

FontSprite::FontSprite(std::string text, const Font &font, size_t wOffset, size_t hOffset, COR::Cor cor) :
	: SpriteBase(cor), font{font}, wOffset{wOffset}, hOffset{hOffset}
{
	setText(text);
}

virtual void FontSprite::putAt(const SpriteBase &sprt, int l, int c)
{
	for (int i{0} ; i < sprt.getAltura() ; i++)
	{
		if (i + l < 0) 					//se a linha atual estiver antes do sprite, avança
			continue;
		
		if (i + l >= this->getAltura()) //se o pedaço do sprite ultrapassar a altura do sprite destino, para
			break;
		
		if (c >= this->getLargura(i))	//se o objeto a ser desenhando estiver além da largura do destino, faz nada.
			break;
		
		if (!sprt.getLimits()[i].largLinha) //se linha do objeto foz vazia, faz nada
			continue;
		
		for (int si = sprt.getLimits()[i].front ; si <= sprt.getLimits()[i].end ; si++) {
			if (c + si >= 0 && c + si < this->limits[i].largLinha)
				this->sprt[l+i][c+si] = sprt.getLinha(i)[si];
		}
	}
	colorHandler.mergeCores(sprt.getColorHandler(),l,c);
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
						sprt.push_back(std::string{largChar, ' '});
					else
						sprt[posL + localL] += std::string{wOffset = spaceChar, ' '} // add wOffset + spacesize
						
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
						sprt[posL + localL] += std::string{wOffset, ' '} // add wOffset
											+  std::string{linhaChar.begin(), linhaChar.end()};
					
					localL++;
				}
			}
			posC += ( (!posC) ? (wOffset + largChar) : (largChar) );
			
			limits.push_back(LIMITS(0,posC-1,posC));
			colorHandler.pushCorLinha(limits.back().front,limits.back().end + 1);
		}
		
		posL += altChar;
	}
}