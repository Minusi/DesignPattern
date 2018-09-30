#pragma once

#include "Pattern\Mediator\IColleague.h"
#include "Pattern\Mediator\IMediator.h"



class NColleagueButton : public IColleague
{
private:
	IMediator * Mediator;

public:
	void SetMediator(IMediator* InMediator);

	void SetColleagueEnabled(bool InEanbled);
};