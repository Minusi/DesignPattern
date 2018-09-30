#include "BookShelfIterator.h"
#pragma once



BookShelfIterator::BookShelfIterator(BookShelf InBookShelf) : TargetBookShelf(InBookShelf), Index(0)
{
	
}

bool BookShelfIterator::HasNext()
{
	if (Index < TargetBookShelf.GetLength())
	{
		return true;
	}

	return false;
}

Book BookShelfIterator::Next()
{
	Book OutBook = TargetBookShelf.GetBook(Index);
	++Index;

	return OutBook;
}
