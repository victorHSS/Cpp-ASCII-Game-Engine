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
	virtual void putAt(const SpriteBase &, int = 0, int = 0);
	virtual SpriteBase *copia() const { return new SpriteAnimado(*this);}
	
	virtual int getLarguraMaxFit() const { return sprites[iSpriteAnim].getLarguraMaxFit(); }
	virtual int getLarguraMax() const { return sprites[iSpriteAnim].getLarguraMax(); }
	
	virtual int getLargura(unsigned l) const {return sprites[iSpriteAnim].limits[l].largLinha;}
	virtual int getAltura() const {return sprites[iSpriteAnim].getAltura();}
	
	//Cores
	virtual void setCor(COR::Cor cor);
	virtual const ColorHandler &getColorHandler() const { return sprites[iSpriteAnim].getColorHandler(); } 
	
	//Transp
	virtual const std::vector< LIMITS > &getLimits() const {return sprites[iSpriteAnim].getLimits();}
	
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
