#ifndef CMAKE_LIB_APP_MYLIB_MAIN_H
#define CMAKE_LIB_APP_MYLIB_MAIN_H

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include "mylib/core/Application.h"
#include "mylib/utils/Arguments.h"
#include "mylib/utils/Logger.h"

#ifdef WIN32
#include <windows.h>
#endif


SDL_AppResult SDL_AppInit(void **_context, int argc, char **argv) {
	Logger::init();

#ifdef WIN32
	if (AttachConsole(ATTACH_PARENT_PROCESS)) {
		FILE* fDummy;
		freopen_s(&fDummy, "CONOUT$", "w", stdout);
		freopen_s(&fDummy, "CONOUT$", "w", stderr);
		freopen_s(&fDummy, "CONIN$",  "r", stdin);

		setvbuf(stdout, nullptr, _IOLBF, 0);
		setvbuf(stderr, nullptr, _IOLBF, 0);
	}
#endif

	auto args = Arguments("sdl-cmake-lib");
	args.addOptionFlag("help", "Prints this help.", "h");
	args.addOptionFlag("version", "Prints the version.", "v");

	if (!args.parseArgs(argc, argv)) {
		Logger::error("Failed to parse arguments");
		return SDL_APP_FAILURE;
	}

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		Logger::error("Failed to initialize SDL: {}", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	auto app = createApplication(args);
	if (app == nullptr) {
		return SDL_APP_SUCCESS;
	}

	*_context = app;

	Logger::trace("Finished system initializion");
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *_app, SDL_Event *event) {
	auto app = static_cast<Application *>(_app);

	app->onEvent(event);

	return app->shouldQuit() ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *_app) {
	auto app = static_cast<Application *>(_app);

	app->onRender();

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *_app, SDL_AppResult result) {
	if (result == SDL_APP_FAILURE) {
		Logger::error("Exited with error");
	} else {
		Logger::trace("Exited successfully");
	}
	if (_app == nullptr)
		return;

	Application::destroy();
}

#endif // CMAKE_LIB_APP_MYLIB_MAIN_H
