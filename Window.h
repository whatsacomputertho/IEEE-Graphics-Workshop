#pragma once
#include <string>
#include "SDL.h"
#include "glew.h"

class Window
{
private:
	SDL_Window* window;
	SDL_GLContext glContext;
	std::string name;
	int width;
	int height;
	bool closed;
	void setClosed(bool closed);
	void init();

public:
	Window(std::string name, int width, int height);
	Window();
	~Window();
	void update();
	SDL_Window* getWindow();
	SDL_GLContext getGlContext();
	std::string getName();
	int getWidth();
	int getHeight();
	bool isClosed();
	void setWindow(SDL_Window* window);
	void setGlContext(SDL_GLContext glContext);
	void setName(std::string name);
	void setWidth(int width);
	void setHeight(int height);
};

