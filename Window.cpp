#include <iostream>
#include "Window.h"
#include "SDL.h"
#include "glew.h"

//Getters and setters
SDL_Window* Window::getWindow() { return this->window; }
SDL_GLContext Window::getGlContext() { return this->glContext; }
std::string Window::getName() { return this->name; }
int Window::getWidth() { return this->width; }
int Window::getHeight() { return this->height; }
int Window::getXMouse() { return this->xMouse; }
int Window::getYMouse() { return this->yMouse; }
bool Window::isClosed() { return this->closed; }
void Window::setWindow(SDL_Window* window) { this->window = window; }
void Window::setGlContext(SDL_GLContext glContext) { this->glContext = glContext; }
void Window::setName(std::string name) { this->name = name; }
void Window::setWidth(int width) { this->width = width; }
void Window::setHeight(int height) { this->height = height; }
void Window::setClosed(bool closed) { this->closed = closed; }

void Window::init() 
{
	//Initialize SDL for windowing purposes
	SDL_Init(SDL_INIT_EVERYTHING);

	//Initialize SDL color attributes: color buffers should be 8-bit (2^8 = 256 = 16^2 AKA standerd hex color + alpha channel), total buffer size is 32 bit
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	//Activate double buffering: SDL draws to one buffer while other buffer is active, each frame buffers are switched
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Get window handle from SDL
	setWindow(SDL_CreateWindow(getName().c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, getWidth(), getHeight(), SDL_WINDOW_OPENGL));

	//Get OpenGL context from SDL
	setGlContext(SDL_GL_CreateContext(getWindow()));

	//Initialize GLEW while checking for errors
	if(glewInit() != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize" << std::endl;
	}

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

void Window::update(Camera& camera) 
{
	//Swap buffers - remember, we're double buffering!
	SDL_GL_SwapWindow(getWindow());

	//Poll for SDL events
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		switch (e.type) 
		{
		case SDL_QUIT:
			setClosed(true);
			break;

		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&xMouse, &yMouse);
			camera.updateRotation(getXMouse(), getYMouse(), getWidth(), getHeight());
			break;

		case SDL_KEYDOWN:
			//Switch keycode and set direction
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				camera.updatePosition(0);
				break;
			case SDLK_a:
				camera.updatePosition(1);
				break;
			case SDLK_s:
				camera.updatePosition(2);
				break;
			case SDLK_d:
				camera.updatePosition(3);
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			std::cout << "Clicked!" << std::endl;
			break;

		case SDL_MOUSEBUTTONUP:
			std::cout << "Unclicked!" << std::endl;
			break;

		//Mouse wheel motion to mesh scale?
		}
	}
}

Window::Window(std::string name, int width, int height)
{
	//Set attributes given input args
	setName(name);
	setWidth(width);
	setHeight(height);

	//Call initialize function
	init();
}

Window::Window() 
{
	//Set default attributes
	setName("Default Window");
	setWidth(640);
	setHeight(480);

	//Call initialize function
	init();
}

Window::~Window() 
{
	//Destroy window and delete OpenGL context
	SDL_GL_DeleteContext(getGlContext());
	SDL_DestroyWindow(getWindow());

	//Close SDL upon window destruction
	SDL_Quit();
}