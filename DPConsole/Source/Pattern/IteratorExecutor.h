#pragma once

#include "IPatternExecutor.h"
#include "Iterator\BookShelf.h"
#include "Iterator\BookShelfIterator.h"



class IteratorExecutor : public IPatternExecutor
{
public:
	void ExecutePattern() override;
};