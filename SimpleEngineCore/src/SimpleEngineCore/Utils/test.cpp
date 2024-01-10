#include <iostream>
#include <SimpleEngineCore/Utils/test.hpp>
#include <GLFW/glfw3.h>

namespace SimpleEngine {
	int checkGLFW() {
		std::cout << "Hello from Simple Engine Core" << std::endl;

		GLFWwindow *pWin;
		if(!glfwInit()) {
			return -1;
		}
		//GLFWmonitor *pMon = glfwGetPrimaryMonitor();
		pWin = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
		if(!pWin) {
			glfwTerminate();
			return -2;
		}

		glfwMakeContextCurrent(pWin); // Make the pWin's context current

		// Loop wile not closed pWin
		while(!glfwWindowShouldClose(pWin)){
			glfwPollEvents();
		  // glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(pWin);
		}
  	glfwTerminate();
		return 0;
	}
}