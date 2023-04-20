#ifndef HELICOPTER_HPP
#define HELICOPTER_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "Pessoa.hpp"
#include <list>

class Helicopter : public ObjetoDeJogo
{
public:
	Helicopter(const ObjetoDeJogo &, unsigned , unsigned , unsigned );
	virtual ~Helicopter(){}
	
	unsigned getOcupacao() const {return ocupacaoAtual;}
	unsigned getTanqueAtual() const {return 10*tanqueAtual/tanqueMaximo;} // 0%=0 10%=1 20%=2 ... 100%=10
	unsigned getCargaAtual() const {return 10*cargaAtual/cargaMaxima;}
	
	void abastecer(unsigned combustivel); //ignora o combustivel excedente
	
	bool podeEmbarcar(const Pessoa &) const;
	void embarcar(Pessoa *);
	bool temResgatados() { return resgatados.size() > 0; }
	std::list<Pessoa*> desembarcar();
	
	bool podeVoar() const { return tanqueAtual > 0; } //se tem combustivel, pode voar
	
	Helicopter &setVelConsumoCombustivel(unsigned v) { velConsumoCombustivel = v; return *this;}
	
	//RenderBase
	virtual void update();
	 
	
private:
	unsigned capacidadeMaxima, tanqueMaximo, cargaMaxima;
	unsigned ocupacaoAtual, tanqueAtual, cargaAtual;
	unsigned velConsumoCombustivel;
	
	std::list<Pessoa *> resgatados;//por enquanto nao aceita polimorfismo
};

#endif // HELICOPTER_HPP
