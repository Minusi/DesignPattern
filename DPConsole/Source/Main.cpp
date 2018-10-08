#include <gui/wvl.hpp>
#include <gui.hpp>
#include <gui/widgets/label.hpp>
#include <gui/widgets/button.hpp>

#include <system/platform.hpp>



#include "Pattern\IPatternExecutor.h"
#include "Pattern\IteratorExecutor.h"
#include "Pattern\AdapterExecutor.h"
#include "Pattern\TemplateExecutor.h"

#include "Syntax\SmartPointerExecutor.h"
#include "Syntax\RawPointerExecutor.h"
#include "Syntax\RValueRefExecutor.h"

using namespace nana;

#include <iostream>
#include <memory>




int main()
{
	std::unique_ptr<IPatternExecutor> SyntaxExecutor(new RValueRefExecutor());
	SyntaxExecutor->ExecutePattern();

	//std::cout << std::endl << std::endl << std::endl;
	
	//std::unique_ptr<IPatternExecutor> PatternExecutor{ new NTempalteExecutor() };
	//PatternExecutor->ExecutePattern();

	



} 
