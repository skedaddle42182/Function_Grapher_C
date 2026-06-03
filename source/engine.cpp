#include "Engine.hpp"

Engine::Engine(WindowProperties& window_properties, GridProperties& grid_properties)
{
	window.create(window_properties);
	renderer.create(window);
	grid.create(window, grid_properties.rows, grid_properties.columns, grid_properties.cell_scale_y, grid_properties.cell_scale_x);
}
