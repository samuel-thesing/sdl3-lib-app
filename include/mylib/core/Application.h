#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL3/SDL.h>

#include "mylib/export.h"
#include "mylib/utils/Arguments.h"

class MYLIB_EXPORT Application {
public:
	struct Config {
		std::string title;
	};

private:
	SDL_Window *window;

	bool quit = false;

private:
	static Application *instance;

	Application(const Config &config);
	~Application();

public:
	static Application *create(Application::Config config);
	static void destroy();

	void onEvent(SDL_Event *event);
	void onRender();

	bool shouldQuit() const { return quit; }
};

extern Application *createApplication(Arguments args);

#endif // APPLICATION_H
