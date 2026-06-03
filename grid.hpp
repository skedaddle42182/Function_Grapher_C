#pragma once

#include <vector>
#include <functional>
#include <unordered_map>
#include "renderer.hpp"

namespace Colors
{
	inline constexpr SDL_Color red{ 255, 0, 0, 255 };
	inline constexpr SDL_Color green{ 0, 255, 0, 0 };
	inline constexpr SDL_Color blue{ 0, 0, 255, 255 };
	inline constexpr SDL_Color white{ 255, 255, 255, 255 };
	inline constexpr SDL_Color black{ 0, 0, 0, 0 };
}

struct GridProperties
{
	int rows, columns;
	double cell_scale_y, cell_scale_x;
};

struct Cell
{
	int x, y;
	int width, height;
};

struct Line
{
	std::string equation;
	std::vector<SDL_Point> points;
	int x_start, x_end;
	double y;
};

class Grid
{
public:
	~Grid();
	void initialize_line(double x_start, double x_end, const std::string& equation);
	void create(Window& window, int rows, int columns, double cell_scale_y, double cell_scale_x);
	void add_function(Renderer& renderer, Window& window, double target_precision, std::function<double(double)> function, SDL_Color color, const std::string& equation);
	void draw_cells(Renderer& renderer, SDL_Color color);
	Line& get_line_at(const std::string& equation);
	void draw_function(Renderer& renderer, Window& window, SDL_Color color, const std::string& equation);
	void recalculate(Window& window);
	void destroy();
	void draw(Renderer& renderer);
	Cell& cell_at(int row, int column);
	int get_rows() const;
	int get_columns() const;
	void draw_axis(Window& window, Renderer& renderer, SDL_Color color);
	void set_initialized(bool is_initialized);
	int get_cell_width() const;
	int get_cell_height() const;
private:
	std::vector<Cell> cells;
	std::unordered_map<std::string, Line> lines;
	int rows = 0;
	int columns = 0;
	int grid_cell_width = 0;
	int grid_cell_height = 0;
	bool grid_initialized = false;
	double cell_scale_y = 0.0;
	double cell_scale_x = 0.0;
};

