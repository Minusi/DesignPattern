#pragma once

#include <string>



class Book
{
private:
	std::string Name;

public:
	Book(std::string InName);

	std::string GetName() const;
};
