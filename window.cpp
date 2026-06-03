#include "window.hpp"

Window::~Window()
{
	destroy();
}

SDL_Window* Window::get_window()
{
	return window;
}

double Window::get_delta_time()
{
	if (current == 0.0)
	{
		current = SDL_GetPerformanceCounter();
	}

	last = current;
	current = SDL_GetPerformanceCounter();
	delta_time = (double)(current - last) / (double)SDL_GetPerformanceFrequency();

	return delta_time;
}

int Window::get_height()
{
	return height;
}

int Window::get_width()
{
	return width;
}

void Window::destroy()
{
	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_Quit();
	}
}

bool Window::get_window_resized()
{
	return currently_resized;
}

void Window::set_window_resized(bool current_resized_flag)
{
	currently_resized = current_resized_flag;
}

void Window::handle_events()
{
	SDL_Event event;

	while (SDL_PollEvent(&event) > 0)
	{
		switch (event.type)
		{
			case SDL_QUIT:
				should_close = true;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					SDL_GetWindowSize(window, &width, &height);
					currently_resized = true;
				}
				break;
			default:
				break;
		}
	}
}

bool Window::get_should_close()
{
	return should_close;
}

void Window::create(WindowProperties& window_properties)
{
	if (!window_properties.width || !window_properties.height)
	{
		std::cout << "Window height or width weren't initialized." << std::endl;
		return;
	}

	if (!window_properties.title)
	{
		std::cout << "Window title wasn't initialized." << std::endl;
		return;
	}

	width = window_properties.width;
	height = window_properties.height;

	title = window_properties.title;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Couldn't initialize SDL: " << SDL_GetError();
		return;
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (!window)
	{
		std::cout << "Couldn't create SDL window: " << SDL_GetError();
		return;
	}
}

double Window::get_fps()
{
	fps_time += delta_time;
	frame_count++;

	if (fps_time >= 1.0)
	{
		fps = frame_count / fps_time;
		frame_count = 0;
		fps_time = 0.0;
	}

	return fps;
}


