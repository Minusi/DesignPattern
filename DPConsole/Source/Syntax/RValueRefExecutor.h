#pragma once

#include "Pattern\IPatternExecutor.h"



class RValueRefExecutor : public IPatternExecutor
{
public:
	void ExecutePattern() override;
};

