#ifndef MESSENGER_HPP
#define MESSENGER_HPP

#include <string>
#include <string_view>
#include <list>

#include "../SpriteBuffer.hpp"
#include "../TextSprite.hpp"
#include "../ObjetoDeJogo.hpp"

class Messenger : public ObjetoDeJogo {
public:
	Messenger(std::string name, int posL, int posC) : 
		ObjetoDeJogo{name, posL, posC} {}
	
	virtual ~Messenger() = default;
	
	void setBox(const SpriteBase &sb, int textWidth, int textHeight, int offsetL = 0, int offsetC = 0);
	void setText(const std::string &text, COR::Cor textColor = COR::PADRAO);

	void restart();
	bool isTalking() const;
	void next();

	//void setGradually(bool = false); // de quantos em quantos caracteres
	
	virtual void draw(SpriteBase &screen, int x, int y) override;
private:
	void toTextSpriteList();
	
	int textWidth, textHeight;
	int offsetL, offsetC;
	
	COR::Cor textColor;
	std::list< ObjetoDeJogo > lTS;

	std::string text;
	std::string_view partialText;
};

#endif