#include "SimpleEngineCore/Window.hpp"
#include "SimpleEngineCore/Log.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

namespace SimpleEngine {

	static bool s_GLFW_initialized = false;

	Window::Window(std::string title, const unsigned int width, const unsigned int height) noexcept
		: m_pWindow(nullptr), m_data{std::move(title), width, height, nullptr}, m_background_color{1.f, 0.f, 0.f, 0.f} {
		int res = init();
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplOpenGL3_Init();
		ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
	}

	Window::~Window() noexcept {
		shutdown();
	}

	int Window::init() noexcept {
		LOG_INFO("Creating window '{0}' with size {1}x{2}", m_data.title, m_data.width, m_data.height);
		if(!s_GLFW_initialized) {
			if(!glfwInit()) {
				LOG_CRITICAL("Failed to initialized GLFW");
				return -1;
			}
			s_GLFW_initialized = true;
		}

		//GLFWmonitor *pMon = glfwGetPrimaryMonitor();
		m_pWindow = glfwCreateWindow(m_data.width, m_data.width, m_data.title.c_str(), nullptr, nullptr);
		if(!m_pWindow) {
			glfwTerminate();
			LOG_ERROR("Can't create GLFWwindow window '{0}' with size {1}x{2}", m_data.title, m_data.width, m_data.width);
			s_GLFW_initialized = false;
			return -2;
		}

		glfwMakeContextCurrent(m_pWindow); // Make the pWin's context current

		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			LOG_CRITICAL("Failed to initialized GLAD");
			return -3;
		}
		glfwSetWindowUserPointer(m_pWindow, &m_data);
		glfwSetWindowSizeCallback(m_pWindow,
			[](GLFWwindow *pWindow, int width, int height) {
				WindowData &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
				data.width = width;
				data.height = height;
				EventWindowResize event(width, height);
				data.eventCallbackFn(event);
			}
		);

		glfwSetCursorPosCallback(m_pWindow,
		[](GLFWwindow *pWin, double x, double y) {
			WindowData &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWin));
			EventMouseMoved event(x, y);
			data.eventCallbackFn(event);
		}
		);

		glfwSetWindowCloseCallback(m_pWindow,
			[](GLFWwindow *pWin) {
				WindowData &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWin));
				EventWindowClose event;
				data.eventCallbackFn(event);
			}
		);
		return 0;

	}

	void Window::set_event_callback(const EventCallbackFn &callback) noexcept {
		m_data.eventCallbackFn = callback;
	}

	void Window::on_update() noexcept {
		glClearColor(m_background_color[0], m_background_color[1], m_background_color[2], m_background_color[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGuiIO &io = ImGui::GetIO();
		io.DisplaySize.x = static_cast<float>(get_width());
		io.DisplaySize.y = static_cast<float>(get_height());
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Background color window");
		ImGui::ColorEdit4("Background Color", m_background_color);
		ImGui::End();

		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



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
		glfwDestroyWindow(m_pWindow);
		glfwTerminate();
	}
}