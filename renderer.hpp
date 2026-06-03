#pragma once

#include <SDL2/SDL.h>
#include "window.hpp"

class Renderer
{
public:
	~Renderer();
	void draw_line(SDL_Point point_one, SDL_Point point_two, Renderer& renderer);
	void destroy();
	void clear();
	void present();
	void set_clear_color(SDL_Color color);
	void create(Window& window);
	SDL_Renderer* get_renderer();
private:
	SDL_Renderer* renderer = nullptr;
};

