#include <iostream>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>
// #include <SDL.h>
// #include <SDL_syswm.h>

#include <bgfx/platform.h>
#include <bgfx/bgfx.h>

void ErrorCallback(int error, const char* description)
{
	std::cerr << "Error: " << description << std::endl;
}

int main()
{
    if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	glfwSetErrorCallback(ErrorCallback);

    std::cout << "Hello world!" << std::endl;

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Project", NULL, NULL);
    if (!window)
	{
		std::cerr << "Failed to create window" << std::endl;
		exit(-1);
	}

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	bgfx::PlatformData pd;
    pd.nwh = glfwGetCocoaWindow(window);

    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer
    bgfxInit.resolution.width = width;
    bgfxInit.resolution.height = height;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
	bgfxInit.platformData = pd;

	bgfx::renderFrame();
    bgfx::init(bgfxInit);
	
	bgfx::setViewRect(0, 0, 0, width, height);

    while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
		bgfx::touch(0);
		bgfx::frame();
	}

	bgfx::shutdown();
    glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

// int main() {
// 	if(SDL_Init( SDL_INIT_VIDEO ) != 0) {
//     	std::cerr << "Failed to initialize SDL. " << SDL_GetError() << std::endl;
//  		exit(-1);
// 	}
// 	int width = 800;
// 	int height = 600;
// 	SDL_Window* window = SDL_CreateWindow(
// 		"My Project",
// 		SDL_WINDOWPOS_UNDEFINED,
// 		SDL_WINDOWPOS_UNDEFINED,
// 		width,
// 		height,
// 		SDL_WINDOW_SHOWN);
	
// 	if(window == nullptr) {
// 		std::cerr << "Failed to create window" << std::endl;
// 		exit(-1);
// 	}
	
// 	SDL_SysWMinfo wmi;
// 	SDL_VERSION(&wmi.version);
// 	if (!SDL_GetWindowWMInfo(window, &wmi)) {
// 		return 1;
// 	}

// 	bgfx::PlatformData pd;
// 	pd.nwh = (void*)wmi.info.cocoa.window;

// 	bgfx::Init bgfxInit;
//     bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer
//     bgfxInit.resolution.width = width;
//     bgfxInit.resolution.height = height;
//     bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
// 	bgfxInit.platformData = pd;

// 	bgfx::renderFrame();
//     bgfx::init(bgfxInit);

// 	bool quit = false;
// 	SDL_Event currentEvent;
// 	while(!quit) {
// 		while(SDL_PollEvent(&currentEvent) != 0) {
// 			if(currentEvent.type == SDL_QUIT) {
// 				quit = true;
// 			}
// 		}
// 		bgfx::setViewRect(0, 0, 0, width, height);
// 		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
// 		bgfx::touch(0);
// 		bgfx::frame();
// 	}
// 	bgfx::shutdown();
// 	SDL_DestroyWindow(window);
// 	SDL_Quit();
// 	return 0;
// }
