#include "function_grapher.hpp"

void FunctionGrapher::loop(Engine& engine, std::function<void()> function)
{
	while (!engine.window.get_should_close())
	{
		engine.window.handle_events();

		engine.renderer.clear();

		engine.grid.recalculate(engine.window);

		engine.grid.draw(engine.renderer);

		function();

		engine.window.set_window_resized(false);

		engine.grid.set_initialized(true);

		engine.renderer.present();
	}
}

