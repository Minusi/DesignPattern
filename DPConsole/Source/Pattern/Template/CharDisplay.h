#pragma once

#include "AbstractDisplay.h"



class NCharDisplay : public NAbstractDisplay
{
private:
	char Char;
public:
	NCharDisplay(char InChar);

	void Open() override;

	void Print() override;

	void Close() override;

};