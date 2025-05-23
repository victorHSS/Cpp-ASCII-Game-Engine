#include "../ASCII_Engine/Cores.hpp"
#include "../ASCII_Engine/Sound.hpp"
#include "../ASCII_Engine/Sprite.hpp"
#include "../ASCII_Engine/SpriteAnimado.hpp"
#include "../ASCII_Engine/FontSprite.hpp"
#include "../ASCII_Engine/SpriteBuffer.hpp"
#include "../ASCII_Engine/TextSprite.hpp"
#include "../ASCII_Engine/input/Keyboard.hpp"
#include "../ASCII_Engine/utils/Drawer.hpp"
#include "../ASCII_Engine/utils/TextContainer.hpp"
#include "../ASCII_Engine/utils/Font.hpp"
#include "../ASCII_Engine/assets/Messenger.hpp"

#include <iostream>
#include <string>

int main() {
	SpriteBuffer buffer(50, 30, '.');
	Sprite coracao("trab/coracao");
	Sprite olho("trab/olho");
	SpriteAnimado boneco("trab/boneco", 2);

	boneco.setCor(COR::AZUL);
	olho.setCor(COR::AMARELA);

	coracao.setCor(COR::ROSA);
	boneco.putAt(olho, 0, 1);

	TextSprite txt("Um texto qualquer", COR::VERMELHA);
	TextSprite txt2("outro");
	txt.setCor(COR::AMARELA);
	txt2.setCor(COR::VERDE);

	txt.putAt(txt2, 0, 3);

	TextContainer tc;
	tc.addFromFile("trab/falas.txt");
	tc.addText("teste1", "Era uma vez...\num jogo de xadrez\nUma banana\nde cada vez.");
	tc.addText("teste2", "tesando multiplas\nlinhas para ver\nse tudo esta ok");

	std::cout << tc;

	SpriteBuffer boxModel1{Drawer::boxFromModel(
	  "ASCII_Engine/assets/boxModels/msgbox1.box", 22, 4, COR::AZUL)};
	SpriteBuffer boxModel2{Drawer::boxFromModel(
	  "ASCII_Engine/assets/boxModels/msgbox2.box", 22, 4, COR::AZUL)};
	SpriteBuffer boxModel3{Drawer::boxFromModel(
	  "ASCII_Engine/assets/boxModels/msgbox3.box", 22, 4, COR::AZUL)};
	SpriteBuffer boxModel4{Drawer::boxFromModel(
	  "ASCII_Engine/assets/boxModels/msgbox4.box", 22, 4, COR::AZUL)};
	SpriteBuffer boxModel5{Drawer::boxFromModel(
	  "ASCII_Engine/assets/boxModels/msgbox5.box", 22, 4, COR::AZUL)};


	std::cout << boxModel1 << std::endl;
	std::cout << boxModel2 << std::endl;
	std::cout << boxModel3 << std::endl;
	std::cout << boxModel4 << std::endl;
	std::cout << boxModel5 << std::endl;
	
	Font font{};
	std::string linha{};
	std::cout << font << std::endl;
	std::cout << font["P"] << std::endl;
	
	
	FontSprite fontText{"TESTANDO ESSA\nQUEBRADA!"};
	std::cout << fontText;
	getline(std::cin, linha);

	Messenger msg{"testando",12,3};
	msg.setBox(boxModel5,20,3,2,3);
	msg.setText(tc.getText("perto da escola"));
	msg.setLineByLine(false);

	Keyboard::setMode(Keyboard::NONBLOCKING);
	int a = 0, l = 1;
	while (true) {

		system("clear");
		buffer.clear();

		buffer.putAt(txt, 0, 0);
		buffer.putAt(coracao, 2, 6);
		buffer.putAt(boneco, a, l);
		buffer.putAt(fontText, 20, 3);

		msg.draw(buffer,msg.getPosL(),msg.getPosC());

		std::cout << buffer;

		system("sleep .1");

		char ent = Keyboard::read();

		if (ent == 'w')
			a--;
		else if (ent == 's')
			a++;
		else if (ent == 'a')
			l--;
		else if (ent == 'd')
			l++;
		else if (ent == 'q')
			exit(0);

		boneco.update();
		msg.update();

		if (msg.isTalking())
			msg.next();
		else {
			msg.desativarObj();
			msg.restart();
		}
			
	}
	return 0;
}
