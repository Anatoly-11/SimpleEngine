#include "SimpleEngineCore/Window.hpp"
#include "SimpleEngineCore/Log.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace SimpleEngine {

	static bool s_GLFW_initialized = false;

	Window::Window(std::string title, const unsigned int width, const unsigned int height) noexcept
		: m_pWin(nullptr)
		, m_title(std::move(title))
		, m_width(width)
		, m_height(height) {
		int res = init();
	}

	Window::~Window() noexcept {
		shutdown();
	}

	int Window::init() noexcept {
		LOG_INFO("Creating window '{0}' with size {1}x{2}", m_title, m_width, m_height);
		if(!s_GLFW_initialized) {
			if(!glfwInit()) {
				LOG_CRITICAL("Failed to initialized GLFW");
				return -1;
			}
			s_GLFW_initialized = true;
		}

		//GLFWmonitor *pMon = glfwGetPrimaryMonitor();
		m_pWin = glfwCreateWindow(m_width, m_width, m_title.c_str(), nullptr, nullptr);
		if(!m_pWin) {
			glfwTerminate();
			LOG_ERROR("Can't create GLFWwindow window '{0}' with size {1}x{2}", m_title, m_width, m_width);
			s_GLFW_initialized = false;
			return -2;
		}

		glfwMakeContextCurrent(m_pWin); // Make the pWin's context current

		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			LOG_CRITICAL("Failed to initialized GLAD");
			return -3;
		}

		return 0;

	}

	void Window::on_update() noexcept {
		glClearColor(1, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
	  glfwSwapBuffers(m_pWin);
  	glfwPollEvents();
	}

	unsigned int Window::get_width() const noexcept {
		return m_width;
	}

	unsigned int Window::get_height() const noexcept {
		return m_height;
	}

	void Window::shutdown() noexcept {
		glfwDestroyWindow(m_pWin);
		glfwTerminate();
	}
}