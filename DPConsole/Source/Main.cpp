#include <gui/wvl.hpp>
#include <gui.hpp>
#include <gui/widgets/label.hpp>
#include <gui/widgets/button.hpp>

#include <system/platform.hpp>



#include "Pattern\IPatternExecutor.h"
#include "Pattern\IteratorExecutor.h"
#include "Pattern\AdapterExecutor.h"


using namespace nana;

#include <iostream>
#include <memory>

int main()
{
	std::unique_ptr<IPatternExecutor> PatternExecutor(new NAdapterExecutor());
	PatternExecutor->ExecutePattern();

	return 0;
} 