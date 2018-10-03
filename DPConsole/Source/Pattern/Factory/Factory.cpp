#include "Factory.h"



AProduct& AFactory::Create(std::string& InString)
{
	AProduct& Product = CreateProduct(InString);
	RegisterProduct(Product);

	return Product;
}
