#include "SpriteView.hpp"
#include <stdexcept>


SpriteView::SpriteView(SpriteBase &spbase, int lin, int col, int height, int width, COR::Cor cor)
		: SpriteBase{( cor != COR::NULL_COLOR ) ? cor : spbase.getColorHandler().getCorBase() }
		, spbase{spbase}, lin{lin}, col{col}, height{height}, width{width}
{
	if (height > spbase.getAltura())
		throw std::invalid_argument{"Altura do SpriteView maior que altura do Sprite base."};

	if (width > spbase.getLarguraMax())
		throw std::invalid_argument{"Largura do SpriteView maior que altura do Sprite base."};
	
	if (height <= 0 || width <= 0)
		throw std::invalid_argument{"Altura e Largura do SpriteView devem ser maiores que 0."};
	
	moveTo(lin, col);
}

void SpriteView::moveTo(int l, int c)
{
	limits.clear();
	colorHandler.clear();
	lin = l;
	col = c;
	
	for (int i{} ; i < std::min(height, spbase.getAltura() - (lin + 1)) ; i++)
	{
		limits.push_back( 
			LIMITS{ std::max(c, 0),
					std::min(c + width - 1, static_cast<int> (spbase.getLimits()[lin + i].largLinha) - 1),
					width
			}
		);
		
		colorHandler.pushCorLinha(limits.back().front, limits.back().end + 1);
	}
}

void SpriteView::setAltura(int height)
{
	this->height = height;
	moveTo(lin, col);
}

void SpriteView::setLargura(int width)
{
	this->width = width;
	moveTo(lin, col);
}

std::string SpriteView::getLinha(unsigned l) const
{
	return ( ( l < limits.size() ) ? spbase.getLinha(lin + l) : "" );
}

void SpriteView::putAt(const SpriteBase &sprt, int l, int c)
{
	throw std::runtime_error{"SpriteView é um view passivo."};
}