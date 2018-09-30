#include "IteratorExecutor.h"

#include <iostream>



void IteratorExecutor::ExecutePattern()
{
	BookShelf SBookShelf = BookShelf();
	
	SBookShelf.AppendBook(Book("Around the World in 80 Days"));
	SBookShelf.AppendBook(Book("Bible"));
	SBookShelf.AppendBook(Book("Cinderella"));
	SBookShelf.AppendBook(Book("Daddy-Long-Legs"));

	IIterator<BookShelf, Book>* Iterator = new BookShelfIterator(SBookShelf);

	while (Iterator->HasNext())
	{
		Book book = Iterator->Next();
		std::cout << book.GetName() << std::endl;
	}
}
