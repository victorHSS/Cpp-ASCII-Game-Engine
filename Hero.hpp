#ifndef HERO_HPP
#define HERO_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"

class Hero : public ObjetoDeJogo
{
public:
	Hero(const ObjetoDeJogo &obj, int life=100) : ObjetoDeJogo(obj), life(life), chave(false), princesa(false) {}
	virtual ~Hero()	{}
	
	bool isAlive() const { return life != 0; }
	int getLife() const { return life; }
	
	void sofrerAtaque(int ataque) { life = (life - ataque >= 0)?(life - ataque):0; }
	int atacar() const { return 10; }
	
	void pegarChave() { chave = true; }
	bool possuiChave() const { return chave; } 
	
	void salvarPrincesa() { princesa = true; }
	bool salvouPrincesa() const { return princesa; }

private:
	int life;
	bool chave;
	bool princesa;
};

#endif // HERO_HPP
