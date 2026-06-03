#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "function_grapher.hpp"
#include "engine.hpp"

double e = std::exp(1.0);

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define CELL_ROWS 10
#define CELL_COLUMNS 10

#undef main

int main()
{
	WindowProperties window_properties = {
		.width = SCREEN_WIDTH,
		.height = SCREEN_HEIGHT,
		.title = "Function_Grapher_C++"
	};

	GridProperties grid_properties = {
		.rows = CELL_ROWS,
		.columns = CELL_COLUMNS,
		.cell_scale_y = 5,
		.cell_scale_x = 5
	};

	std::function<double(double)> sin_function = [](double x)
	{
		return e * sin(x);
	};

	std::function<double(double)> sound_wave_function = [](double x)
	{
		return (pow(e, (-0.1 * x)) * sin(5 * x));
	};

	std::function<double(double)> atan_function = [](double x)
	{
		return e * atan(x);
	};

	std::function<double(double)> atan_cos_function = [](double x)
	{
		return e * acos(x);
	};

	Engine engine(window_properties, grid_properties);

	engine.grid.initialize_line(-100, 100, "pow(e, (-0.1 * x)) * sin(5 * x)");

	engine.grid.initialize_line(-100, 100, "e * sin(x)");

	engine.grid.initialize_line(-100, 100, "e * atan(x)");

	engine.grid.initialize_line(-100, 100, "e * acos(x)");

	FunctionGrapher grapher;

	grapher.loop(engine, [&]() {
		engine.grid.draw_cells(engine.renderer, Colors::red);
		
		engine.grid.draw_axis(engine.window, engine.renderer, Colors::blue);
		
		engine.grid.add_function(engine.renderer, engine.window, 0.001, sound_wave_function, Colors::white, "pow(e, (-0.1 * x)) * sin(5 * x)");
		
		engine.grid.add_function(engine.renderer, engine.window, 0.001, sin_function, Colors::white, "e * sin(x)");
		
		engine.grid.add_function(engine.renderer, engine.window, 0.001, atan_function, Colors::white, "e * atan(x)");
		
		engine.grid.add_function(engine.renderer, engine.window, 0.001, atan_cos_function, Colors::white, "e * acos(x)");
		
		engine.renderer.set_clear_color(Colors::black);
	});
}


