#include "ColleagueButton.h"

#include <iostream>



void NColleagueButton::SetMediator(IMediator * InMediator)
{
	this->Mediator = InMediator;
}

void NColleagueButton::SetColleagueEnabled(bool InEnabled)
{
	std::cout << "CALL >> SetEnabled(" << InEnabled << ");" << std::endl;
}
