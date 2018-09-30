#pragma once

#include <string>

#include "Pattern\Mediator\IColleague.h"



class ColleagueTextField : public IColleague
{
private:
	IMediator * Mediator;

public:
	ColleagueTextField(std::string InText, int Columns);


	void SetMediator(IMediator* InMediator);


	void SetColleagueEnabled(bool InEnabled);
};