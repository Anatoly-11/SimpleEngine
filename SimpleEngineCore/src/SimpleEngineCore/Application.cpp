#include "SimpleEngineCore/Application.hpp"
#include "SimpleEngineCore/Window.hpp"
#include <iostream>

#include "SimpleEngineCore/Log.hpp"

//#include "glad/glad.h"
//#include <GLFW/glfw3.h>

namespace SimpleEngine {
	Application::Application() noexcept {
		LOG_INFO("Starting Application");
	}

	Application::~Application() noexcept {
		LOG_INFO("Closing Application");
	}

	int Application::start(unsigned int window_width, unsigned int window_height, const char *title) noexcept {
		m_pWindow = std::make_unique<Window>(title, window_width, window_height);
		if(!m_pWindow) return -1;
		while(true) {
			m_pWindow->on_update();
			on_update();
		}
		return 0;
	}

	void Application::on_update() noexcept {
	}
}