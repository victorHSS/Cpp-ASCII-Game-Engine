#include "Sound.hpp"
#include <sstream>
#include <fstream>

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

Sound::~Sound()
{
	if (isplaying())
		stop();
}

//nao funciona se soundName tiver espacos
bool Sound::play(unsigned times)
{
	if (isplaying()) //evita tocar a mesma música paralela e perder o controle da anterior
		return false;
	
	if (( PID_child = fork() ) == 0) //processo filho
	{
		std::ostringstream sTimes;
		sTimes.str(std::string());
		sTimes << "-l" << times;
		char *argv[] = {"/usr/bin/mpg321","-q",const_cast<char*>(sTimes.str().c_str()),
						const_cast<char*>(soundName.c_str()),
						nullptr};
		execv(argv[0],argv);
		exit(1); // se chegar aqui é porque deu erro no execv
	}
	
	if (isplaying())
		return !(paused = false);
	
	PID_child = -1;
	return false;
}


bool Sound::playloop() 
{
	return play(0);
}


bool Sound::stop()
{
	if (PID_child == -1)
		return false;
		
	if (kill(PID_child,SIGKILL))
		return !(paused = false);

	PID_child = -1;
	return false;
}

bool Sound::pause()
{
	if (PID_child == -1)
		return false;
		
	if (kill(PID_child,SIGSTOP))
		return (paused = true);

	return false;
}

bool Sound::unpause()
{
	if (PID_child == -1)
		return false;
		
	if (kill(PID_child,SIGCONT))
		return !(paused = false);

	return false;
}


bool Sound::isplaying() const 
{
	if (PID_child == -1)
		return false;
	
	if (waitpid(PID_child, nullptr, WNOHANG) == 0)
		return true;
	
	return false;
}