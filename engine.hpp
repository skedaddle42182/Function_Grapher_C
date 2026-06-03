#pragma once

#include "renderer.hpp"
#include "window.hpp"
#include "grid.hpp"

class Engine
{
public:
	Engine(WindowProperties& window_properties, GridProperties& grid_properties);

	Window window;
	Renderer renderer;
	Grid grid;
};

