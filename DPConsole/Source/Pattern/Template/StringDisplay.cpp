#include "StringDisplay.h"

#include <iostream>



NStringDisplay::NStringDisplay(std::string InString) : String(InString)
{
}

void NStringDisplay::PrintLine() const
{
	std::cout << "+";

	for (int i = 0; i < String.size(); ++i)
	{
		std::cout << "-";
	}

	std::cout << "+" << std::endl;
}

void NStringDisplay::Open()
{
	PrintLine();
	std::cout << std::endl;
}

void NStringDisplay::Print()
{
	std::cout << "|" << String << "|" << std::endl;
}

void NStringDisplay::Close()
{
	PrintLine();
	std::cout << std::endl;
}
