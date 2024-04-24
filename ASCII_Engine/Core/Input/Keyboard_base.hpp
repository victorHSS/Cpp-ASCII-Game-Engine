#ifndef KEYBOARD_BASE_HPP
#define KEYBOARD_BASE_HPP

#include <unistd.h>
#include <termios.h>

#include <stdexcept>

class KeyboardError : public std::runtime_error
{
public:
	KeyboardError(const char *error) : std::runtime_error(error){}
};

class KeyboardInputBase
{
public:

	enum {
		UNBLOCKING_MODE = 0,
		BLOCKING_MODE	= 1
	};

	KeyboardInputBase(unsigned = UNBLOCKING_MODE);
	~KeyboardInputBase();
	char getInput();

private:
	struct termios old;
};

#endif