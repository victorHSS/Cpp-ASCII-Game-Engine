#include "Messenger.hpp"

void Messenger::setBox(const SpriteBuffer &sb, int textWidth, int textHeight, int offsetL, int offsetC)
{
	this->pSprite = sb.copia();
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
	toTextSpriteList();
}

void Messenger::toTextSpriteList()
{	
	while (!partialText.empty())
	{
		size_t bn{partialText.find_first_of("\n")};
		
		if (bn == std::string_view::npos)
			bn = partialText.size();
		
		//AQUI TEM QUE SER OBJETO DE JOGO!!!!!
		lTS.push_back(TextSprite( partialText.substr( 0 , bn ) , textColor ));
		
		partialText.remove_prefix( bn ); //verificar se precisa somar mais um, e se não dará problema
										 //no caso de final de string
	}
}

bool Messenger::isTalking() const
{
	return lTS.size() > textHeight;
}

void Messenger::next()
{
	if (lTS.size())
		lTS.pop_front();
}

//TERMINAR!!!!!
virtual void update() override {}
virtual void draw(SpriteBase &screen, int x, int y) override {}