#pragma once

#include "IIterator.h"
#include "BookShelf.h"



class BookShelfIterator : public IIterator<BookShelf, Book>
{
private:
	BookShelf TargetBookShelf;
	int Index;

public:
	BookShelfIterator(BookShelf InBookShelf);
	
	// BookShelf에 담긴 다음 Book이 존재한다면 true를 반환합니다.
	bool HasNext();

	// 현재 참조하는 Book을 반환하면서 다음 Book으로 이동합니다.
	Book Next();
};