#ifndef PESSOA_HPP
#define PESSOA_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"

class Pessoa : public ObjetoDeJogo
{
public:
	Pessoa(const ObjetoDeJogo &o, unsigned peso):ObjetoDeJogo(o), peso(peso), resgatada(false){}
	virtual ~Pessoa(){}
	
	unsigned getPeso() const {return peso;}
	unsigned foiResgatada() const {return resgatada;}
	void resgatar() { resgatada = true;}
	
private:
	unsigned peso;
	bool resgatada;
};

#endif // PESSOA_HPP
