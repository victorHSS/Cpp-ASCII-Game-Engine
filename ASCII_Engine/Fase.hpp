#ifndef FASE_HPP
#define FASE_HPP

#include "Core/SpriteBase.hpp"
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
		GAME_OVER,										//jogador nao completou fase
		MENU,											//opcao padrao para indicar fase menu
		OP_1, OP_2, OP_3, OP_4, OP_5,					//opcoes para menu
		LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5,	//fases
		PLAYING, PAUSED,								//opcoes para a fase
		LEVEL_COMPLETE,									//fase completada
		END_GAME										//quando jogador nao quiser mais jogar
	};


	Fase(std::string name, const SpriteBase &bkg) : name(name),background(bkg.copia()) {}
	virtual ~Fase();
	
	Fase(const Fase &f);
	
	const Fase &operator=(const Fase &);
	
	std::string getName() { return name;}
	
	virtual unsigned run(SpriteBuffer &screen) = 0; //cada derivada tem de implementar sua lógica nesse método
	void show(SpriteBuffer &screen) const {std::cout << screen << std::endl;};
	
	//RenderBase
	virtual void init() = 0;
	virtual void update();
	virtual void draw(SpriteBase &screen, int x = 0, int y = 0);

protected:
	std::string name;
	SpriteBase *background;
	std::list<ObjetoDeJogo*> objs;
};

#endif // FASE_HPP
