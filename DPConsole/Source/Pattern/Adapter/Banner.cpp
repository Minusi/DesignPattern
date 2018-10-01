#include "Banner.h"



NBanner::NBanner(std::string InString) : String(InString)
{
}

NBanner::~NBanner()
{
}



void NBanner::ShowWithParen() const
{
	std::cout << "( " << String << " )" << std::endl;
}

void NBanner::ShowWithAster() const
{
	std::cout << "* " << String << " *" << std::endl;
}

