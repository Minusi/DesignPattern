#include "CharDisplay.h"

#include <iostream>



NCharDisplay::NCharDisplay(char InChar) : Char(InChar)
{
}



void NCharDisplay::Open()
{
	std::cout << "<<" << std::endl;
}

void NCharDisplay::Print()
{
	std::cout << Char << std::endl;
}

void NCharDisplay::Close()
{
	std::cout << ">>" << std::endl;
}
