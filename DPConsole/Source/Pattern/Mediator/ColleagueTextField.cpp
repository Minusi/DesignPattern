#include "ColleagueTextField.h"

#include <iostream>



ColleagueTextField::ColleagueTextField(std::string InText, int InColumns)
{
	std::cout << "CALL >> super(" << InText << ", " << InColumns << ");" << std::endl;
}

void ColleagueTextField::SetMediator(IMediator * InMediator)
{
	this->Mediator = InMediator;
}

void ColleagueTextField::SetColleagueEnabled(bool InEnabled)
{
	std::cout << "CALL >> SetEnabled(" << InEnabled << ");" << std::endl;

	std::cout << "CALL >> SetBackground(";

	if (InEnabled)
	{
		std::cout << "Color.white);" << std::endl;
	}
	else
	{
		std::cout << "Color.lightGray);" << std::endl;
	}
}
