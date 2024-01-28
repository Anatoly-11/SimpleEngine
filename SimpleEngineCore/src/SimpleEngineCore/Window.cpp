#include "SimpleEngineCore/Window.hpp"
#include "SimpleEngineCore/Log.hpp"

#include "SimpleEngineCore/Modules/UIModule.hpp"

#include "SimpleEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp"

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

namespace SimpleEngine {

	
	Window::Window(std::string title, const unsigned int width, const unsigned int height) noexcept
		: m_pWindow(nullptr), m_data{std::move(title), width, height, nullptr} {
		int resultCode = init();
	}

	Window::~Window() noexcept {
		shutdown();
	}

	int Window::init() noexcept {

		LOG_INFO("Creating window '{0}' with size {1}x{2}", m_data.title, m_data.width, m_data.height);
		glfwSetErrorCallback([](int error_code, const char *description) {
			LOG_CRITICAL("GLFW error: {0}", description);
		});

		if(!glfwInit()) {
			LOG_CRITICAL("Failed to initialized GLFW");
			return -1;
		}
		
		m_pWindow = glfwCreateWindow(m_data.width, m_data.width, m_data.title.c_str(), nullptr, nullptr);
		if(!m_pWindow) {
			LOG_ERROR("Can't create GLFWwindow window '{0}' with size {1}x{2}", m_data.title, m_data.width, m_data.width);
			return -2;
		}

		if(!Render_OpenGL::init(m_pWindow)) {
			LOG_CRITICAL("Failed to initialized OpenGL renderer");
			return -3;
		}

		glfwSetWindowUserPointer(m_pWindow, &m_data);
		glfwSetWindowSizeCallback(m_pWindow,	[](GLFWwindow *pWindow, int width, int height) {
			WindowData &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
			data.width = width;
			data.height = height;
			EventWindowResize event(width, height);
			data.eventCallbackFn(event);
		});

		glfwSetCursorPosCallback(m_pWindow,	[](GLFWwindow *pWin, double x, double y) {
			WindowData &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWin));
			EventMouseMoved event(x, y);
			data.eventCallbackFn(event);
		});

		glfwSetWindowCloseCallback(m_pWindow, [](GLFWwindow *pWin) {
			WindowData &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWin));
			EventWindowClose event;
			data.eventCallbackFn(event);
		});

		glfwSetFramebufferSizeCallback(m_pWindow, [](GLFWwindow *pWindow, int width, int height) {
			Render_OpenGL::set_viewport(width, height);
		});

		UIModule::on_window_create(m_pWindow);

		return 0;
	}

	void Window::set_event_callback(const EventCallbackFn &callback) noexcept {
		m_data.eventCallbackFn = callback;
	}

	void Window::on_update() noexcept {
		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}

	unsigned int Window::get_width() const noexcept {
		return m_data.width;
	}

	unsigned int Window::get_height() const noexcept {
		return m_data.height;
	}

	void Window::shutdown() noexcept {
		UIModule::on_window_close();
		glfwDestroyWindow(m_pWindow);
		glfwTerminate();
	}
}