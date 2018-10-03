#include "TemplateExecutor.h"

#include <iostream>
#include <string>

#include "Template\AbstractDisplay.h"
#include "Template\CharDisplay.h"
#include "Template\StringDisplay.h"



void NTempalteExecutor::ExecutePattern()
{
	NAbstractDisplay* AbstractDisplay1 = new NCharDisplay{ 'H' };

	NAbstractDisplay* AbstractDisplay2 = new NStringDisplay{ "Hello, World" };

	NAbstractDisplay* AbstractDisplay3 = new NStringDisplay{ "안녕하세요" };

	AbstractDisplay1->Display();
	AbstractDisplay2->Display();
	AbstractDisplay3->Display();
}
