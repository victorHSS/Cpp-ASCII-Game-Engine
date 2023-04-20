#ifndef FUEL_HPP
#define FUEL_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"

class Fuel : public ObjetoDeJogo
{
public:
	Fuel(const ObjetoDeJogo &o, unsigned litros) : ObjetoDeJogo(o), litros(litros) {}
	virtual ~Fuel(){}
	
	unsigned getFuel() const {return litros;}
private:
	unsigned litros;
};

#endif // FUEL_HPP
