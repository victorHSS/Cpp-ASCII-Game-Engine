#ifndef FASE_HPP
#define FASE_HPP

#include "SpriteBase.hpp"
#include "SpriteBuffer.hpp"
#include "ObjetoDeJogo.hpp"
#include "Sprite.hpp"
#include "SpriteAnimado.hpp"
#include <list>
#include <string>
#include <iostream>

//Abstrata
class Fase : public RenderBase
{
public:

	enum {
		GAME_OVER,
		MENU,
		OP_1, OP_2, OP_3, OP_4, OP_5,
		LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5,
		LEVEL_COMPLETE,
		END_GAME
	};


	Fase(std::string name, const Sprite &bkg) : name(name),background(new Sprite(bkg)) {}
	Fase(std::string name, const SpriteAnimado &bkg) : name(name),background(new SpriteAnimado(bkg)) {}
	virtual ~Fase();
	
	Fase(const Fase &f);
	
	const Fase &operator=(const Fase &);
	
	std::string getName() { return name;}
	
	virtual unsigned run(SpriteBuffer &screen) = 0; //cada derivada tem de implementar sua lógica nesse método
	void show(SpriteBuffer &screen) const {std::cout << screen << std::endl;};
	
	//RenderBase
	virtual void init() = 0;
	virtual void update();
	virtual void draw(SpriteBase &screen, unsigned x = 0, unsigned y = 0);

protected:
	std::string name;
	SpriteBase *background;
	std::list<ObjetoDeJogo*> objs;
};

#endif // FASE_HPP
