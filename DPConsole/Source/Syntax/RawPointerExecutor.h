#pragma once

#include "Pattern\IPatternExecutor.h"



class NRawPointerExecutor : public IPatternExecutor
{
public:
	void ExecutePattern() override;
};

