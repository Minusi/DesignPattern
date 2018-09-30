#include "Book.h"



Book::Book(std::string InName) : Name(InName)
{
}

std::string Book::GetName() const
{
	return Name;
}
