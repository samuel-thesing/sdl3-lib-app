#include "mylib/core/Application.h"

#include "mylib/utils/Logger.h"

Application *Application::instance = nullptr;

Application *Application::create(Config config) {
	instance = new Application(config);
	return instance;
}

void Application::destroy() {
	delete instance;
	instance = nullptr;
}

Application::Application(const Config &config) {
	window = SDL_CreateWindow(config.title.c_str(), 800, 600, 0);
	if (window == nullptr) {
		Logger::critical("Failed to create window: {}", SDL_GetError());
		throw std::runtime_error("Failed to create window");
	}

	Logger::trace("Finished initializing application");
}

Application::~Application() {
	SDL_DestroyWindow(window);
}

void Application::onEvent(SDL_Event *event) {
	if (event->type == SDL_EVENT_QUIT) {
		quit = true;
		return;
	}

	if (event->type == SDL_EVENT_KEY_UP) {
		if (event->key.scancode == SDL_SCANCODE_ESCAPE) {
			quit = true;
		}
	}
}

void Application::onRender() {}
