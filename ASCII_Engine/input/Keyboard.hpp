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


enum class KEY
{
	KEY_0		=	'0',
	KEY_1,	KEY_2,	KEY_3,
	KEY_4,	KEY_5,	KEY_6,
	KEY_7,	KEY_8,	KEY_9,
	
	KEY_A		=	'a',
	KEY_B,	KEY_C, 	KEY_D,	KEY_E,	KEY_F,	KEY_G,	KEY_H,
	KEY_I,	KEY_J, 	KEY_K,	KEY_L,	KEY_M,	KEY_N,
	KEY_O,	KEY_P,	KEY_Q, 	KEY_R,	KEY_S,	KEY_T,
	KEY_U,	KEY_V,	KEY_W,	KEY_X, 	KEY_Y,	KEY_Z,
	//...
	KEY_ENTER	=	13,
	KEY_SPACE	=	32
};

class Keyboard
{
public:
	~Keyboard();

	enum {
		NONBLOCKING	= 0,
		BLOCKING	= 1
	};
	
	//impedindo a cópia do objeto
	Keyboard(const Keyboard&) = delete;
	Keyboard &operator=(const Keyboard &) = delete;
	
	
	static void setMode( unsigned );
	
	static char read();

private:
	//queremos um singleton
	Keyboard( unsigned = BLOCKING );
	
	static unsigned mode;
	static struct termios old;
};

#endif