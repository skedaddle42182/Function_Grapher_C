#pragma once

#include <SDL2/SDL.h>
#include <iostream>

struct WindowProperties
{
	int width, height;
	const char* title;
};

class Window
{
public:
	~Window();
	void create(WindowProperties& properties);
	void destroy();
	bool get_window_resized();
	void set_window_resized(bool current_resized_flag);
	int get_width();
	int get_height();
	void handle_events();
	bool get_should_close();
	double get_fps();
	SDL_Window* get_window();
	double get_delta_time();
private:
	SDL_Window* window = nullptr;
	const char* title = nullptr;
	int width;
	int height;
	bool should_close = false;
	bool currently_resized = false;
	Uint64 current = 0.0;
	Uint64 last = 0.0;
	double delta_time = 0.0;
	double fps_time = 0.0;
	int frame_count = 0;
	double fps = 0.0;
};

