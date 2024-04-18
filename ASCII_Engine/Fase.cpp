#include "Fase.hpp"

Fase::Fase(const Fase &f) : name(f.name)
{
	//trick
	if (f.background->whoami() == "Sprite")
		background = new Sprite(*(dynamic_cast<Sprite*>(f.background)));
	else if (f.background->whoami() == "SpriteAnimado")
		background = new SpriteAnimado(*(dynamic_cast<SpriteAnimado*>(f.background)));
	
	for (auto it = f.objs.begin() ; it != f.objs.end() ; ++it)
		this->objs.push_back( new ObjetoDeJogo(**it) );
}

const Fase &Fase::operator=(const Fase &f)
{
	if (this != &f)
	{
		this->name = f.name;
		
		delete this->background;
		//trick
		if (f.background->whoami() == "Sprite")
			background = new Sprite(*(dynamic_cast<Sprite*>(f.background)));
		else if (f.background->whoami() == "SpriteAnimado")
			background = new SpriteAnimado(*(dynamic_cast<SpriteAnimado*>(f.background)));
		
		for (auto it = this->objs.begin() ; it != this->objs.end() ; ++it)
			delete *it;
			
		this->objs.clear();
		
		for (auto it = f.objs.begin() ; it != f.objs.end() ; ++it)
			this->objs.push_back( new ObjetoDeJogo(**it) );
		
	}
	
	return *this;
}

Fase::~Fase()
{
	delete background;
	for (auto it = objs.begin() ; it != objs.end() ; ++it)
		delete (*it);
}

void Fase::update()
{
	background->update();
	
	for (auto it = objs.begin() ; it != objs.end() ; ++it)
		(*it)->update();
}

void Fase::draw(SpriteBase &screen, int x, int y)
{
	background->draw(screen,0,0);
	for (auto it = objs.begin() ; it != objs.end() ; ++it)
		(*it)->draw(screen,(*it)->getPosL(),(*it)->getPosC());
}
