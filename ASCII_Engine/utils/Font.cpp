#include "Font.hpp"

#include <string_view>
#include <algorithm>
#include <ranges>

Font::Font(std::string fontFile)
{
	font.addFromFile(fontFile, "<key>");
}

Font::FontChar Font::operator[](std::string key)
{
	std::string value{font.getText(key)};
	
	if (value.empty())
		throw std::runtime_error{"Char da fonte não encontrado..."};
	
	size_t heigth{std::ranges::count(value, '\n') + 1ul};
	
	//size_t width{std::ranges::max_element(value | std::views::split('\n'), {} , 
	//		[](std::string_view s){ return s.size();} )};
	size_t width{0};
	for ( const auto &v : value | std::views::split('\n') ) 
		width = ( (v.size() > width) ? v.size() : width );
	
	return FontChar{value, heigth, width};
}
