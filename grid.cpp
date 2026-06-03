#include "grid.hpp"

void Grid::draw_cells(Renderer& renderer, SDL_Color color)
{
	renderer.set_clear_color(color);

	int cell_width = get_cell_width();
	int cell_height = get_cell_height();

	for (int i = 0; i < cells.size(); i++)
	{
		SDL_Rect rect = {
			.x = cells[i].x,
			.y = cells[i].y,
			.w = cell_width,
			.h = cell_height
		};

		SDL_RenderDrawRect(renderer.get_renderer(), &rect);
	}
}

void Grid::recalculate(Window& window)
{
	if (!window.get_window_resized() && grid_initialized) /* Only recalculate if it isn't initialized or its size has changed. */
	{
		return;
	}

	double cell_width = window.get_width() / columns;
	double cell_height = window.get_height() / rows;

	for (int i = 0; i < rows * columns; i++)
	{
		int row = i / columns;
		int col = i % columns;

		Cell cell = {
			.x = static_cast<int>(cell_width * col),
			.y = static_cast<int>(cell_height * row),
			.width = static_cast<int>(cell_width),
			.height = static_cast<int>(cell_height)
		};

		cells[i] = cell;
	}

	grid_cell_width = static_cast<int>(cell_width);
	grid_cell_height = static_cast<int>(cell_height);
}

void Grid::create(Window& window, int rows, int columns, double cell_scale_y, double cell_scale_x)
{
	this->rows = rows;
	this->columns = columns;

	this->cell_scale_y = cell_scale_y;
	this->cell_scale_x = cell_scale_x;

	cells.resize(rows * columns);

	recalculate(window); /* Keep for one call to initialize everything. */
}

void Grid::destroy()
{
	if (!cells.empty())
	{
		cells.clear();
	}

	if (!lines.empty())
	{
		lines.clear();
	}

	rows = 0;
	columns = 0;
	rows = 0;
	columns = 0;
	grid_cell_width = 0;
	grid_cell_height = 0;
	grid_initialized = false;
	cell_scale_y = 0.0;
	cell_scale_x = 0.0;
}

Grid::~Grid()
{
	destroy();
}

Cell& Grid::cell_at(int row, int column)
{
	return cells[row * columns + column];
}

int Grid::get_columns() const
{
	return columns;
}

int Grid::get_rows() const
{
	return rows;
}

void Grid::draw(Renderer& renderer)
{
	for (int i = 0; i < rows * columns; i++)
	{
		SDL_Rect rect = {
			.x = cells[i].x,
			.y = cells[i].y,
			.w = cells[i].width,
			.h = cells[i].height
		};

		SDL_RenderFillRect(renderer.get_renderer(), &rect);
	}
}

void Grid::draw_axis(Window& window, Renderer& renderer, SDL_Color color)
{
	renderer.set_clear_color(color);

	int window_width = window.get_width();
	int window_height = window.get_height();

	SDL_Point y_bottom = { window_width / 2, window_height };
	SDL_Point y_top = { window_width / 2, 0 };
	SDL_Point x_bottom = { window_width, window_height / 2 };
	SDL_Point x_top = { 0, window_height / 2 };

	renderer.draw_line(y_top, y_bottom, renderer);

	renderer.draw_line(x_top, x_bottom, renderer);
}

void Grid::initialize_line(double x_start, double x_end, const std::string& equation)
{
	if (equation.empty())
	{
		std::cout << "Equation is empty." << std::endl;

		return;
	}

	Line line;

	line.x_start = x_start;
	line.x_end = x_end;
	line.equation = equation;

	lines[line.equation] = line;
}

void Grid::add_function(Renderer& renderer, Window& window, double target_precision, std::function<double(double)> function, SDL_Color color, const std::string& equation)
{
	if (!window.get_window_resized() && grid_initialized)
	{
		draw_function(renderer, window, color, equation);

		return;
	}

	int window_width = window.get_width();
	int window_height = window.get_height();

	auto& line = get_line_at(equation);

	line.points.clear();

	double start_position_x = window_width / 2;
	double start_position_y = window_height / 2;

	for (double i = line.x_start; i < line.x_end; i += target_precision)
	{
		line.y = function(i);

		double ratio_y = -line.y / cell_scale_y;
		double ratio_x = i / cell_scale_x;

		double calculated_x = start_position_x + ratio_x * grid_cell_width;
		double calculated_y = start_position_y + ratio_y * grid_cell_height;

		SDL_Point point = {
			.x = static_cast<int>(calculated_x),
			.y = static_cast<int>(calculated_y)
		};

		if (calculated_x < window_width && calculated_x > 0 && calculated_y < window_height && calculated_y > 0)
		{
			line.points.push_back(point);
		}
		else
		{
			continue;
		}
	}

	draw_function(renderer, window, color, equation);
}

void Grid::draw_function(Renderer& renderer, Window& window, SDL_Color color, const std::string& equation)
{
	auto& line = get_line_at(equation);
	
	if (line.points.empty())
	{
		std::cout << "The lines vector is empty." << std::endl;
	
		return;
	}
	
	renderer.set_clear_color(color);
	
	SDL_RenderDrawLines(renderer.get_renderer(), line.points.data(), line.points.size());
}

Line& Grid::get_line_at(const std::string& equation)
{
	if (equation.empty())
	{
		throw std::logic_error("Equation is empty.");
	}

	auto line = lines.find(equation);

	if (line == lines.end())
	{
		throw std::logic_error("Line with equation doesn't exist.");
	}
	else
	{
		return line->second;
	}
}

int Grid::get_cell_width() const
{
	return grid_cell_width;
}

int Grid::get_cell_height() const
{
	return grid_cell_height;
}

void Grid::set_initialized(bool is_initialized)
{
	grid_initialized = is_initialized;
}






