#include <gui/wvl.hpp>
#include <gui.hpp>
#include <gui/widgets/label.hpp>
#include <gui/widgets/button.hpp>

#include <system/platform.hpp>



#include "Pattern\IPatternExecutor.h"
#include "Pattern\IteratorExecutor.h"



using namespace nana;



int main()
{
	IPatternExecutor* PatternExecutor = new IteratorExecutor();
	PatternExecutor->ExecutePattern();

	return 0;
}