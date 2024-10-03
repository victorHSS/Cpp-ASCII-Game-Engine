#include "Keyboard.hpp"

#include <cstdlib>

unsigned Keyboard::mode{Keyboard::BLOCKING};
struct termios Keyboard::old{};

void Keyboard::setMode(unsigned m)
{
	if (tcgetattr(0, &old) < 0)
		throw KeyboardError("tcgetattr");
	
	old.c_lflag &= ~(ICANON | ECHO);
	old.c_cc[VMIN] = mode = m;
	old.c_cc[VTIME] = 0;
	
	if (tcsetattr(0, TCSANOW, &old) < 0)
		throw KeyboardError("tcsetattr");
}

Keyboard::Keyboard(unsigned mode)
{
	setMode(mode);
}

Keyboard::~Keyboard()
{
	old.c_lflag |= (ICANON | ECHO);
	
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		throw KeyboardError("tcsetattr");
}

char Keyboard::read()
{
	static Keyboard kb{mode};
	
	char buf;
	
	if (::read(0, &buf, 1) < 0)
		throw KeyboardError("read error");

	tcflush(STDIN_FILENO, TCIFLUSH);
	
	return buf;
}

