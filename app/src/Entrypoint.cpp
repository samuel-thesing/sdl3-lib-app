
#include <mylib/mylib.h>
#include <mylib/mylib_main.h>

Application *createApplication(Arguments args) {
	UNUSED(args)

	auto app = Application::create({"sdl-cmake-lib"});

	return app;
}
