#pragma once

#include "IPatternExecutor.h"


class FactoryExecutor : public IPatternExecutor
{
public:
	void ExecutePattern() override;
};

