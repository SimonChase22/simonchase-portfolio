//Smart Home Automation Manager
//Proof of concept command line based system to model the functionality of the system

#include "progManager.h"

int main()
{

	std::unique_ptr<progManager> programManager = std::make_unique<progManager>();

	programManager->~progManager(); //deallocates all held in programManager(explained in destructor definition)
	programManager.reset(); //deallocates the memory the uniqueptr to programManager holds

	_CrtDumpMemoryLeaks();
	return 0;
}