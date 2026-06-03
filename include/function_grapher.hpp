#pragma once

#include "engine.hpp"

class FunctionGrapher
{
public:
	void loop(Engine& engine, std::function<void()> function);
};

