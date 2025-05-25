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
		ObjetoDeJogo{name, posL, posC}, textWidth{}, textHeight{}, offsetL{}, offsetC{},
		lineByLine{true} {}
	
	virtual ~Messenger() = default;
	
	void setBox(const SpriteBase &sb, int textWidth, int textHeight, int offsetL = 0, int offsetC = 0);
	void setText(const std::string &text, COR::Cor textColor = COR::PADRAO);

	void restart();
	void close() { desativarObj(); }
	bool isTalking() const; //se ainda tem pagina de texto para exibir
	void next();
	
	//FUTURE
	//bool isWriting() const; //se pagina atual ainda está sendo escrita (setGradually != 0)
	
	//modos de funcionamento
	void setLineByLine(bool lineByLine = true) { this->lineByLine = lineByLine; }
	//FUTURE
	//void setGradually(int speed = 0);

	virtual void draw(SpriteBase &screen, int x, int y) override;
private:
	void toTextSpriteList();
	
	int textWidth, textHeight;
	int offsetL, offsetC;
	
	COR::Cor textColor;
	std::list< ObjetoDeJogo > lTS;

	std::string text;
	std::string_view partialText;
	
	//modos
	bool lineByLine;
};

#endif