#include "renderer.hpp"

Renderer::~Renderer()
{
	if (renderer)
	{
		destroy();
	}
}

void Renderer::create(Window& window)
{
	renderer = SDL_CreateRenderer(window.get_window(), -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cout << "Couldn't initialize renderer: " << SDL_GetError();
		return;
	}
}

void Renderer::destroy()
{
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
}

void Renderer::clear()
{
	if (renderer)
	{
		SDL_RenderClear(renderer);
	}
}

void Renderer::set_clear_color(SDL_Color color)
{
	if (renderer)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	}
}

void Renderer::present()
{
	if (renderer)
	{
		SDL_RenderPresent(renderer);
	}
}

SDL_Renderer* Renderer::get_renderer() 
{
	return renderer;
}

void Renderer::draw_line(SDL_Point point_one, SDL_Point point_two, Renderer& renderer)
{
	SDL_RenderDrawLineF(renderer.get_renderer(), point_one.x, point_one.y, point_two.x, point_two.y);
}
