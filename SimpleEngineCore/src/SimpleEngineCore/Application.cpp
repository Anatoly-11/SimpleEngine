#include "SimpleEngineCore/Application.hpp"
#include <iostream>
#include <GLFW/glfw3.h>


namespace SimpleEngine {
	Application::Application() noexcept {

	};
	
	Application::~Application() noexcept {

	}
	
	int Application::start(unsigned int window_width, unsigned int window_height, const char *title) noexcept {
		std::cout << "Hello from Simple Engine Core" << std::endl;

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