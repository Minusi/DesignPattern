#include "PrintBanner.h"



NPrintBanner::NPrintBanner(std::string InString) : Banner(new NBanner(InString))
{
}



void NPrintBanner::PrintWeak() const
{
	Banner->ShowWithParen();
}

void NPrintBanner::PrintStrong() const
{
	Banner->ShowWithAster();
}
