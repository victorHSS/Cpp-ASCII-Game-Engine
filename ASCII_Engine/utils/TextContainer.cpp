#include "TextContainer.hpp"

#include <iostream>
#include <fstream>


std::ostream &operator<<(std::ostream &out, const TextContainer &tc)
{
	for (auto item : tc.textMap)
	{
		out << "Titulo chave: " << item.first << "\n\"";
		out << item.second;
		out << "\"\n----------------" << std::endl;
	}
	
	return out;
}


void TextContainer::addText(std::string title, std::string text)
{
	textMap[title] = text;
}

void TextContainer::addFromFile(std::string nameFile, std::string title)
{
	std::ifstream fsprt(nameFile.c_str(),std::ios::in);
	
	std::string line, textTitle = "empty";
	bool textFlag = false;
	
	while (getline(fsprt,line))
	{
		if (line.starts_with(title))
			textFlag = false;
		else if (textTitle == "empty")
			throw std::runtime_error("TextContainer: Arquivo mal formatado. Faltou titulo.");
		
		if (textFlag)
		{
			textMap[textTitle] += (line + "\n");
		}
		else	//tratando título
		{
			//textMap[textTitle].erase(textMap[textTitle].find_last_not_of(" \t\n") + 1); //?? //APAGAR
			line.erase(0,title.length());
			textTitle = line.substr(line.find_first_not_of(" \t"));
			//textTitle = textTitle.substr(0,textTitle.find_last_not_of(" \t")); // VERIFICAR
			textFlag = true;
		}
	}
	
	//textMap[textTitle].pop_back(); //apaga o último \n inserido
	
	if (rTrim)
		textMap[textTitle].erase(textMap[textTitle].find_last_not_of(" \t\n") + 1);
	
	fsprt.close();
}
	
const std::string &TextContainer::getText(std::string title)// const
{
	if (textMap.find(title) == textMap.end())
		return textMap["empty"];
	
	return textMap[title];
}