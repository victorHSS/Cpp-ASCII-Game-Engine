#include "Messenger.hpp"

#include <iostream>

void Messenger::setBox(const SpriteBase &sb, int textWidth, int textHeight, int offsetL, int offsetC)
{
	setSprite(sb.copia());
	
	this->textWidth = textWidth;
	this->textHeight = textHeight;
	this->offsetL = offsetL;
	this->offsetC = offsetC;
}

void Messenger::setText(const std::string &text, COR::Cor textColor)
{
	this->text = partialText = text;
	this->textColor = textColor;
	
	restart();
}

void Messenger::restart()
{
	partialText = text;
	lTS.clear();	
	toTextSpriteList();
	ativarObj();
}

void Messenger::toTextSpriteList()
{	
	while (!partialText.empty())
	{
		size_t bn{partialText.find_first_of("\n")};
		
		if (bn == std::string_view::npos)
			bn = partialText.size();
		
		lTS.push_back( ObjetoDeJogo (
			"Text", 
			TextSprite( std::string(partialText.substr( 0 , bn )) , textColor ),
			0, 0
			)
		);
		
		partialText.remove_prefix( bn );
		
		if (!partialText.empty() && partialText.front() == '\n')
			partialText.remove_prefix(1);
	}
}

bool Messenger::isTalking() const
{
	return lTS.size() > textHeight;
}

//melhorar isso daqui... (vector + std::spam)
void Messenger::next()
{
	if (lineByLine) {
		if (lTS.size())
			lTS.pop_front();
	}
	else {
		int lines{textHeight};
		
		while (lines-- && lTS.size())
			lTS.pop_front();
	}
}

void Messenger::draw(SpriteBase &screen, int x, int y)
{
	if (!getActive())
		return;
	
	int lines{textHeight}, lp{offsetL};
	
	if (getSprite())
		(const_cast<SpriteBase*> (getSprite()))->draw(screen, x, y);
	
	for (auto &ts : lTS) {
		ts.moveTo(lp++,offsetC);
		
		ts.draw(screen, x + ts.getPosL(), y + ts.getPosC());
		
		if (! --lines)
			break;
	}
}