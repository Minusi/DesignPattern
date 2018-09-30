#pragma once

#include "Pattern\Mediator\IMediator.h"



class IColleague
{

	virtual void SetMediator() = 0;

	virtual void SetColleaueEnabled(bool InEnabled) = 0;

};