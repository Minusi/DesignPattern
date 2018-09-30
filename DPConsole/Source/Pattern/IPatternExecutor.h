#pragma once

#include <combaseapi.h>



interface IPatternExecutor
{
public:
	virtual void ExecutePattern() = 0;
};