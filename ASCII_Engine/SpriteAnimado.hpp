#ifndef SPRITEANIMADO_HPP
#define SPRITEANIMADO_HPP

#include "Core/SpriteBase.hpp"
#include "Sprite.hpp"
#include <vector>
#include <string>

class SpriteAnimado : public SpriteBase
{
	friend std::ostream &operator<<(std::ostream &, const SpriteAnimado &);
public:
	SpriteAnimado(std::string, unsigned = 1, COR::Cor = COR::PADRAO);
	virtual ~SpriteAnimado(){}
	
	unsigned size() const {return sprites.size();} //numero de Sprites da animacão
	
	Sprite operator[](int) const;
	
	//SpriteBase
	virtual void putAt(const SpriteBase &, unsigned = 0, unsigned = 0);
	virtual void setCor(COR::Cor cor);
	virtual std::string whoami() const {return "SpriteAnimado";}
	
	//RenderBase
	virtual void init() {};
	virtual void update();
	
private:
	std::vector<Sprite> sprites;
	unsigned numSprites;
	
	//controle de animacao
	unsigned velAnim, stepAnim, iSpriteAnim;
	
	//SpriteBase
	virtual std::string getLinha(unsigned) const;
};

#endif // SPRITEANIMADO_HPP
