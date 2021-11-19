
#include "Main.h"
//#include "EngineComponents.cpp"

#include <iostream>
#include <string>
#include "EngineComponents.h"

int main(int argc, char** argv)
{
	std::cout << "test " << std::endl;

	EngineComponents::Application app;

	app.Run(argc, argv);
}

namespace EngineComponents {
	
	
	CurrentTestApplication::CurrentTestApplication()
	{
	}

	CurrentTestApplication::~CurrentTestApplication()
	{
	}
}

