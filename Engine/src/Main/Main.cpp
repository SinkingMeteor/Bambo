#include "engpch.h"
#include "Main/Engine.h"
#include "json.hpp"

int main()
{
	Bambo::Engine engine{};

	engine.Initialize();
	
	int result = engine.Run();

	return result;
}