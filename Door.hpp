#ifndef DOOR_HPP
#define DOOR_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"

class Door : public ObjetoDeJogo
{
public:
	Door(const ObjetoDeJogo &obj) : ObjetoDeJogo(obj), open(false) {}
	virtual ~Door()	{}
	
	void openTheDoor() { if (!open) { ObjetoDeJogo::update(); this->open = true;} }
	bool isOpen() const { return this->open; }
	
	virtual void update() { /* porta se mantem estática */ }
	
private:
	bool open;
};

#endif // DOOR_HPP
