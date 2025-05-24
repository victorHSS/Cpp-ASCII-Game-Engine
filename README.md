# The ASCII Game Engine
Apenas uma Engine para criação de jogos em ASCII usando a biblioteca padrão de C++.

Oferece suporte a Textos, Sprites, Sprites Animados, Cores, Transparências (laterais), Objetos de Jogo e Fase, o kit básico e fundamental para criação de qualquer jogo em ASCII. 

>Agora com um Makefile para otimizar compilação do projeto!!

## Demais features suportadas: 
 - Classe Sound para tocar músicas/sons (apenas terminal Linux - requer pacote mpg321).
 - Classe Drawer, que faz desenhos bidimensionais: quadrado, círculo, caixas e caixa de texto.
 - Classe Keyboard para leitura de entrada bloqueante e não bloqueante (apenas terminal Linux).
 - Classe TextContainer para armazenamento de textos (scripts para falas, p.e.)
 - Classe Messenger para chats
 - Classes Font e FontSprite para escrever na tela com fontes personalizadas.
 - Classe SpriteView para criar um view a partir de um sprite (qualquer um dos suportados).

## Para rodar no GNU/Linux:
1 - Clone o repositório

2 - Siga os passos:
```shell
cd Cpp-ASCII-Game-Engine
```
```shell
make
```
```shell
./game
```
