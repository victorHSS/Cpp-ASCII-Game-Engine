#include "Keyboard_base.hpp"

#include <stdlib.h>

KeyboardInputBase::KeyboardInputBase(unsigned mode)
{
	if (tcgetattr(0, &old) < 0)
		throw KeyboardError("tcgetattr");
	
	old.c_lflag &= ~(ICANON | ECHO);
	old.c_cc[VMIN] = mode;
	old.c_cc[VTIME] = 0; //mode?0:1;
	
	if (tcsetattr(0, TCSANOW, &old) < 0)
		throw KeyboardError("tcsetattr");
}

KeyboardInputBase::~KeyboardInputBase()
{
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		throw KeyboardError("tcsetattr");
}

char KeyboardInputBase::getInput()
{
	char buf;
	
	if (read(0, &buf, 1) < 0)
		throw KeyboardError("read");

	tcflush(STDIN_FILENO, TCIFLUSH);
	
	return buf;
}

