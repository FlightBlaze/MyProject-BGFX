#include <iostream>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>
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

    bgfx::init(bgfxInit);

    while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		bgfx::touch(0);
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
		bgfx::setViewRect(0, 0, 0, width, height);
		bgfx::frame();
	}

    glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
