#pragma once

#include "IPatternExecutor.h"



class NAdapterExecutor : public IPatternExecutor
{
public:
	void ExecutePattern() override;
};