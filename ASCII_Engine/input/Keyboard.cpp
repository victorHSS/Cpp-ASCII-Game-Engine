#include "Keyboard.hpp"

#include <cstdlib>

Keyboard Keyboard::getKeyboard(unsigned mode)
{
	return Keyboard{mode};
}

Keyboard::Keyboard(unsigned mode)
{
	if (tcgetattr(0, &old) < 0)
		throw KeyboardError("tcgetattr");
	
	old.c_lflag &= ~(ICANON | ECHO);
	old.c_cc[VMIN] = mode;
	old.c_cc[VTIME] = 0; //mode?0:1;
	
	if (tcsetattr(0, TCSANOW, &old) < 0)
		throw KeyboardError("tcsetattr");
}

Keyboard::~Keyboard()
{
	old.c_lflag |= (ICANON | ECHO);
	
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		throw KeyboardError("tcsetattr");
}

char Keyboard::read()
{
	char buf;
	
	if (::read(0, &buf, 1) < 0)
		throw KeyboardError("read error");

	tcflush(STDIN_FILENO, TCIFLUSH);
	
	return buf;
}

