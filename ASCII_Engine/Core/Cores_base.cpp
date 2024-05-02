#include "Cores_base.hpp"

namespace COR
{
	const char *const NULL_COLOR 		= "";
	const char *const PADRAO 			= "\e[0m";
	
	//Modo de cores 24-bit true color (R, G, B) ==> "\e[38;2; R ; G ; B m"
	const char *const BRANCA 			= "\e[38;2;255;255;255m";
	const char *const PRETA 			= "\e[38;2;0;0;0m";
	const char *const VERMELHA 			= "\e[38;2;255;0;0m";
	const char *const VERDE 			= "\e[38;2;0;255;0m";
	const char *const AZUL 				= "\e[38;2;0;0;255m";
	const char *const AMARELA			= "\e[38;2;255;255;0m";
	const char *const ROSA 				= "\e[38;2;255;0;127m";
	const char *const MARROM 			= "\e[38;2;166;42;42m";
	const char *const MARROM_ESCURA		= "\e[38;2;92;64;51m";
	const char *const CINZA		 		= "\e[38;2;192;192;192m";
	const char *const CINZA_ESCURA 		= "\e[38;2;84;84;84m";
	const char *const CIANO		 		= "\e[38;2;0;255;255m";
	const char *const MAGENTA	 		= "\e[38;2;255;0;255m";
	
	
	//defina mais cores aqui...
}

/*
 * Para mais detalhes...
 * 
 * -> https://bureau-it.com/artigos/como-exibir-cores-no-terminal/
 * -> https://github.com/leilaapsilva/pokemon-terminal/blob/master/jogo.cpp
 * -> https://www.cin.ufpe.br/~js/tabeladecores.htm <- tabela de cores
 * 
 * */