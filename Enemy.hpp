#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"

class Enemy : public ObjetoDeJogo
{
public:
	Enemy(const ObjetoDeJogo &obj, int life=30, int velAtaque=3) : 
			ObjetoDeJogo(obj), life(life), velAtaque(velAtaque), contAtaque(velAtaque) {}
	
	virtual ~Enemy(){}
	
	bool isAlive() const { return life != 0; }
	
	void sofrerAtaque(int ataque) {
		life = (life - ataque >= 0)?(life - ataque):0;
	}
	
	int atacar() { 
		if (--contAtaque == 0) {
			contAtaque = velAtaque;
			return 10;
		}
		return 0;
	}

private:
	int life;
	int velAtaque, contAtaque;
};

#endif // ENEMY_HPP
