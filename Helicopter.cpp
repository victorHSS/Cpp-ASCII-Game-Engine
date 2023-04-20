#include "Helicopter.hpp"

#include "Pessoa.hpp"

Helicopter::Helicopter(const ObjetoDeJogo &obj, unsigned capacidade, unsigned tanque, unsigned carga) :
ObjetoDeJogo(obj),capacidadeMaxima(capacidade),tanqueMaximo(tanque),cargaMaxima(carga),
				  ocupacaoAtual(0),tanqueAtual(tanque),cargaAtual(0),velConsumoCombustivel(1){}

void Helicopter::update()
{
	ObjetoDeJogo::update();
	if (tanqueAtual >= velConsumoCombustivel)
		tanqueAtual -= velConsumoCombustivel;
	else
		tanqueAtual = 0;
}

void Helicopter::abastecer(unsigned combustivel)
{
	tanqueAtual = ((tanqueAtual + combustivel) > tanqueMaximo)?(tanqueMaximo):(tanqueAtual + combustivel);
}

bool Helicopter::podeEmbarcar(const Pessoa &p) const
{
	return (cargaAtual + p.getPeso() <= cargaMaxima) && (ocupacaoAtual+1 <= capacidadeMaxima);
}

void Helicopter::embarcar(Pessoa *p)
{
	cargaAtual += p->getPeso();
	ocupacaoAtual++;
	resgatados.push_back(p);
}

std::list<Pessoa*> Helicopter::desembarcar()
{
	std::list<Pessoa*> tmp = resgatados;
	ocupacaoAtual = cargaAtual = 0;
	resgatados.clear();
	
	return tmp;
}
