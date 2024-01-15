#include "SimpleEngineCore/Window.hpp"
#include "SimpleEngineCore/Log.hpp"
#include "SimpleEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "SimpleEngineCore/Rendering/OpenGL/VertexBuffer.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

namespace SimpleEngine {

	static bool s_GLFW_initialized = false;
	GLfloat points[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	const char *vertex_shader =
		"#version 460\n"
		"layout(location = 0) in vec3 vertex_position;"
		"layout(location = 1) in vec3 vertex_color;"
		"out vec3 color;"
		"void main() {"
		"   color = vertex_color;"
		"   gl_Position = vec4(vertex_position, 1.0);"
		"}";

	const char *fragment_shader =
		"#version 460\n"
		"in vec3 color;"
		"out vec4 frag_color;"
		"void main() {"
		"   frag_color = vec4(color, 1.0);"
		"}";

	std::unique_ptr<ShaderProgram> p_shader_program;
	std::unique_ptr<VertexBuffer> p_points_vbo;
	std::unique_ptr<VertexBuffer> p_colors_vbo;
	GLuint vao;

	Window::Window(std::string title, const unsigned int width, const unsigned int height) noexcept
		: m_pWindow(nullptr), m_data{std::move(title), width, height, nullptr}, m_background_color{0.33f, 0.33f, 0.33f, 0.f} {
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
			glViewport(0, 0, width, height);
		});

		p_shader_program = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);
		if(!p_shader_program->isCompiled()) {
			return false;
		}

		p_points_vbo = std::make_unique<VertexBuffer>(points, sizeof(points));
		p_colors_vbo = std::make_unique<VertexBuffer>(colors, sizeof(colors));

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		p_points_vbo->bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		p_colors_vbo->bind();
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		return 0;
	}

	void Window::set_event_callback(const EventCallbackFn &callback) noexcept {
		m_data.eventCallbackFn = callback;
	}

	void Window::on_update() noexcept {
		glClearColor(m_background_color[0], m_background_color[1], m_background_color[2], m_background_color[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		p_shader_program->bind();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);



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