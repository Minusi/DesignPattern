#include "BookShelf.h"



BookShelf::BookShelf() : LastIndex(0), Books()
{
}

Book BookShelf::GetBook(int InIndex)
{
	if (InIndex < LastIndex)
	{
		return Books[InIndex];
	}
}

void BookShelf::AppendBook(Book InBook)
{
	Books.push_back(InBook);
	++LastIndex;
}

int BookShelf::GetLength()
{
	return LastIndex;
}
