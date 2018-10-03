#include "AbstractDisplay.h"

#include <string>



void NAbstractDisplay::Display()
{
	Open();

	for (int i = 0; i < 5; ++i)
	{
		Print();
	}

	Close();
}
