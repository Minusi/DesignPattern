#pragma once

#include <string>

#include "Product.h"



class AFactory
{
public:
	//
	virtual AProduct& Create(std::string& InString) final;

protected:
	//
	virtual AProduct& CreateProduct(std::string InString) = 0;

	// 
	virtual void RegisterProduct(AProduct InProduct) = 0;
};

