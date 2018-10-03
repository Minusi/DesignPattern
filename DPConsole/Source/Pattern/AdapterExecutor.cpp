#include "AdapterExecutor.h"

#include <iostream>
#include <memory>

#include "Adapter\Banner.h"
#include "Adapter\IPrint.h"
#include "Adapter\PrintBanner.h"



void NAdapterExecutor::ExecutePattern()
{
	std::unique_ptr<IPrint> Print(new NPrintBanner("Hello"));

	Print->PrintWeak();
	Print->PrintStrong();

}
