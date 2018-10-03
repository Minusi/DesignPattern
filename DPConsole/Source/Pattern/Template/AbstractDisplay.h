#pragma once



class NAbstractDisplay
{
public:
	virtual void Open() = 0;

	virtual void Print() = 0;

	virtual void Close() = 0;

	virtual void Display() final;
};