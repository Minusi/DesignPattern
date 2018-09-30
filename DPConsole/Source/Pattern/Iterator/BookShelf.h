#pragma once

#include <vector>

#include "Book.h"



class BookShelf
{
private:
	std::vector<Book> Books;
	int LastIndex;

public:
	BookShelf();

	// 입력받은 인덱스에 위치한 Book을 가져옵니다.
	Book GetBook(int InIndex);

	// 입력받은 Book을 BookShelf에 추가합니다.
	void AppendBook(Book InBook);

	// 현재 책장에서 가지고 있는 책의 갯수를 반환합니다.
	int GetLength();
};