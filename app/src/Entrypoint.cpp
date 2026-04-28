
#include <mylib/mylib.h>
#include <mylib/mylib_main.h>

Application *createApplication(Arguments args) {
	UNUSED(args)

#if APP_CONSOLE
	if (args.hasFlag("help")) {
		args.printHelp();
		return nullptr;
	}
	if (args.hasFlag("version")) {
		args.printVersion();
		return nullptr;
	}
#endif

	auto app = Application::create({"sdl-cmake-lib"});

	return app;
}
