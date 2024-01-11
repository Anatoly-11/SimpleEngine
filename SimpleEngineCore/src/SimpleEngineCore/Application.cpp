#include "SimpleEngineCore/Application.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
#include "SimpleEngineCore/Log.hpp"

namespace SimpleEngine {
	Application::Application() noexcept {
		LOG_INFO("Welcome to spdlog!");
		LOG_ERROR("Some error message with arg {}", 1);
		LOG_WARN("Easy padding in numbers like {:08d}", 12);
		LOG_CRITICAL("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
	};
	
	Application::~Application() noexcept {

	}
	
	int Application::start(unsigned int window_width, unsigned int window_height, const char *title) noexcept {
		GLFWwindow *pWin;
		if(!glfwInit()) {
			return -1;
		}
		//GLFWmonitor *pMon = glfwGetPrimaryMonitor();
		pWin = glfwCreateWindow(window_width, window_height, title, nullptr, nullptr);
		if(!pWin) {
			glfwTerminate();
			return -2;
		}

		glfwMakeContextCurrent(pWin); // Make the pWin's context current

		// Loop wile not closed pWin
		while(!glfwWindowShouldClose(pWin)) {
			glfwPollEvents();
			// glClear(GL_COLOR_BUFFER_BIT);
			on_update();

			glfwSwapBuffers(pWin);
		}
		glfwTerminate();
		return 0;
	}
	
	void Application::on_update() noexcept {
	}
}