#include "Font.hpp"

#include <string_view>
#include <algorithm>
#include <ranges>
#include <format>

Font::Font(std::string fontFile)
{
	font.addFromFile(fontFile, "<key>");
}

Font::FontChar Font::operator[](std::string key)
{
	std::string value{font.getText(key)};
	
	if (value.empty())
		throw std::runtime_error{std::format("Char '{}' da fonte não encontrado...", key)};
	
	size_t height{std::ranges::count(value, '\n') + 1ul};
	
	size_t width{0};
	for ( const auto &v : value | std::views::split('\n') ) 
		width = ( (v.size() > width) ? v.size() : width );
	
	return FontChar{value, height, width};
}
