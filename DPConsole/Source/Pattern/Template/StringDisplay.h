#pragma once

#include <string>

#include "AbstractDisplay.h"



class NStringDisplay : public NAbstractDisplay
{
private:
	std::string String;

public:
	NStringDisplay(std::string InString);

private:
	void PrintLine() const;

public:
	virtual void Open() override;

	virtual void Print() override;

	virtual void Close() override;
};