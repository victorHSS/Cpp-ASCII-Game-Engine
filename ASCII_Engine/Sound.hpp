#ifndef SOUND_HPP
#define SOUND_HPP

#include <string>


class Sound
{
public:
	Sound(std::string );
	~Sound();

	bool play(unsigned = 1);
	bool playloop();
	bool stop();
	bool pause();
	bool unpause();
	bool ispaused() const {return paused;}
	bool isplaying() const;
	

private:
	std::string soundName;
	int PID_child;
	
	bool paused;
};

#endif // SOUND_HPP
