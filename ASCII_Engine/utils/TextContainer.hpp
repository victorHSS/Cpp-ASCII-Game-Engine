#ifndef TEXTCONTAINER_HPP
#define TEXTCONTAINER_HPP

#include <iostream>
#include <string>
#include <unordered_map>

class TextContainer
{
	friend std::ostream &operator<<(std::ostream &, const TextContainer &);
public:
	TextContainer() : textMap{ {"empty",""} } {}
	
	void addText(std::string , std::string);
	void addFromFile(std::string , std::string = "<title>");
	
	const std::string &getText(std::string); //const;
	
private:
	std::unordered_map< std::string , std::string > textMap;
};

#endif