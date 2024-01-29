#include "SimpleEngineCore/Application.hpp"
#include "SimpleEngineCore/Window.hpp"
#include <iostream>

#include "SimpleEngineCore/Log.hpp"
#include "SimpleEngineCore/Input.hpp"

#include "SimpleEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "SimpleEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "SimpleEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "SimpleEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "SimpleEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp"

#include "SimpleEngineCore/Modules/UIModule.hpp"

#include "glm/mat3x3.hpp"
#include "glm/trigonometric.hpp"

//#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>


namespace SimpleEngine {
	
	GLfloat positions_colors2[]{
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f
	};

	GLuint indices[]{0, 1, 2, 3, 2, 1};

	const char* vertex_shader =
		R"(#version 460
		layout(location = 0) in vec3 vertex_position;
		layout(location = 1) in vec3 vertex_color;
		uniform mat4 model_matrix;
		uniform mat4 view_ptojection_matrix;
		out vec3 color;
		void main() {
		   color = vertex_color;
		   gl_Position = view_ptojection_matrix * model_matrix * vec4(vertex_position, 1.0);
		})";

	const char* fragment_shader =
		R"(#version 460
		in vec3 color;
		out vec4 frag_color;
		void main() {
		   frag_color = vec4(color, 1.0);
		})";

	std::unique_ptr<ShaderProgram> p_shader_program;
	std::unique_ptr<VertexBuffer> p_positions_colors_vbo;
	std::unique_ptr<IndexBuffer> p_index_buffer;
	std::unique_ptr<VertexArray> p_vao;
	float scale[3]{1.f, 1.f, 1.f};
	float rotate = 0.f;
	float translate[3]{0.f, 0.f, 0.f};
	float m_background_color[4]{0.33f, 0.33f, 0.33f, 0.f};
	

	Application::Application() noexcept : m_bCloseWindow(false),
		camera_position{0.f, 0.f, 1.f},
		camera_rotation{0.f, 0.f, 0.f},
		perspective_camera(true) {
		LOG_INFO("Starting Application");
	}

	void Application::on_ui_draw() noexcept {
	}

	Application::~Application() noexcept {
		LOG_INFO("Closing Application");
	}

	int Application::start(unsigned int window_width, unsigned int window_height, const char *title) noexcept {
		m_pWindow = std::make_unique<Window>(title, window_width, window_height);
		if(!m_pWindow) return -1;

		m_event_dispatcher.add_event_listener<EventMouseMoved>([](EventMouseMoved &event) {
			//LOG_INFO("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);
		});

		m_event_dispatcher.add_event_listener<EventWindowResize>([](EventWindowResize &event) {
			LOG_INFO("[Resized] Changed size to {0}x{1}", event.height, event.height);
		});

		m_event_dispatcher.add_event_listener<EventWindowClose>([&](EventWindowClose &event) {
			LOG_INFO("[WindowClose]");
			m_bCloseWindow = true;
		});

		auto keyToStr = [](const KeyCode key, char *buf) {
			if((int)KeyCode::KEY_SPACE <= (int)key && (int)key <= (int)KeyCode::KEY_GRAVE_ACCENT) {
				buf[0] = (char)key;
				buf[1] = '\0';
			} else switch(key) {
			case KeyCode::KEY_ESCAPE:
			strcpy(buf, "ESCAPE");
			break;
			case KeyCode::KEY_ENTER:
			strcpy(buf, "ENTER");
			break;
			case KeyCode::KEY_TAB:
			strcpy(buf, "TAB");
			break;
			case KeyCode::KEY_BACKSPACE:
			strcpy(buf, "BACKSPACE");
			break;
			case KeyCode::KEY_INSERT:
			strcpy(buf, "INSERT");
			break;
			case KeyCode::KEY_DELETE:
			strcpy(buf, "DELETE");
			break;
			case KeyCode::KEY_RIGHT:
			strcpy(buf, "RIGHT");
			break;
			case KeyCode::KEY_LEFT:
			strcpy(buf, "LEFT");
			break;
			case KeyCode::KEY_DOWN:
			strcpy(buf, "DOWN");
			break;
			case KeyCode::KEY_UP:
			strcpy(buf, "UP");
			break;
			case KeyCode::KEY_PAGE_UP:
			strcpy(buf, "ENTER");
			break;
			case KeyCode::KEY_PAGE_DOWN:
			strcpy(buf, "PAGE_UP");
			break;
			case KeyCode::KEY_HOME:
			strcpy(buf, "HOME");
			break;
			case KeyCode::KEY_END:
			strcpy(buf, "END");
			break;
			case KeyCode::KEY_CAPS_LOCK:
			strcpy(buf, "CAPS_LOCK");
			break;
			case KeyCode::KEY_SCROLL_LOCK:
			strcpy(buf, "SCROLL_LOCK");
			break;
			case KeyCode::KEY_NUM_LOCK:
			strcpy(buf, "NUM_LOCK");
			break;
			case KeyCode::KEY_PRINT_SCREEN:
			strcpy(buf, "PRINT_SCREEN");
			break;
			case KeyCode::KEY_PAUSE:
			strcpy(buf, "PAUSE");
			break;
			case KeyCode::KEY_F1:
			strcpy(buf, "F1");
			break;
			case KeyCode::KEY_F2:
			strcpy(buf, "F2");
			break;
			case KeyCode::KEY_F3:
			strcpy(buf, "F3");
			break;
			case KeyCode::KEY_F4:
			strcpy(buf, "F4");
			break;
			case KeyCode::KEY_F5:
			strcpy(buf, "F5");
			break;
			case KeyCode::KEY_F6:
			strcpy(buf, "F6");
			break;
			case KeyCode::KEY_F7:
			strcpy(buf, "F7");
			break;
			case KeyCode::KEY_F8:
			strcpy(buf, "F8");
			break;
			case KeyCode::KEY_F9:
			strcpy(buf, "F9");
			break;
			case KeyCode::KEY_F10:
			strcpy(buf, "F10");
			break;
			case KeyCode::KEY_F11:
			strcpy(buf, "F11");
			break;
			case KeyCode::KEY_F12:
			strcpy(buf, "F12");
			break;
			case KeyCode::KEY_F13:
			strcpy(buf, "F13");
			break;
			case KeyCode::KEY_F14:
			strcpy(buf, "F14");
			break;
			case KeyCode::KEY_F15:
			strcpy(buf, "F15");
			break;
			case KeyCode::KEY_F16:
			strcpy(buf, "F16");
			break;
			case KeyCode::KEY_F17:
			strcpy(buf, "ENTER");
			break;
			case KeyCode::KEY_F18:
			strcpy(buf, "F17");
			break;
			case KeyCode::KEY_F19:
			strcpy(buf, "F19");
			break;
			case KeyCode::KEY_F20:
			strcpy(buf, "F20");
			break;
			case KeyCode::KEY_F21:
			strcpy(buf, "F21");
			break;
			case KeyCode::KEY_F22:
			strcpy(buf, "F22");
			break;
			case KeyCode::KEY_F23:
			strcpy(buf, "F23");
			break;
			case KeyCode::KEY_F24:
			strcpy(buf, "F24");
			break;
			case KeyCode::KEY_F25:
			strcpy(buf, "F25");
			break;
			case KeyCode::KEY_KP_0:
			strcpy(buf, "KP_0");
			break;
			case KeyCode::KEY_KP_1:
			strcpy(buf, "KP_1");
			break;
			case KeyCode::KEY_KP_2:
			strcpy(buf, "KP_2");
			break;
			case KeyCode::KEY_KP_3:
			strcpy(buf, "KP_3");
			break;
			case KeyCode::KEY_KP_4:
			strcpy(buf, "KP_4");
			break;
			case KeyCode::KEY_KP_5:
			strcpy(buf, "KP_5");
			break;
			case KeyCode::KEY_KP_6:
			strcpy(buf, "KP_6");
			break;
			case KeyCode::KEY_KP_7:
			strcpy(buf, "KP_7");
			break;
			case KeyCode::KEY_KP_8:
			strcpy(buf, "KP_8");
			break;
			case KeyCode::KEY_KP_9:
			strcpy(buf, "KP_9");
			break;
			case KeyCode::KEY_KP_DECIMAL:
			strcpy(buf, "KP_DECIMAL");
			break;
			case KeyCode::KEY_KP_DIVIDE:
			strcpy(buf, "ENTER");
			break;
			case KeyCode::KEY_KP_MULTIPLY:
			strcpy(buf, "KP_DIVIDE");
			break;
			case KeyCode::KEY_KP_SUBTRACT:
			strcpy(buf, "KP_SUBTRACT");
			break;
			case KeyCode::KEY_KP_ADD:
			strcpy(buf, "KP_ADD");
			break;
			case KeyCode::KEY_KP_ENTER:
			strcpy(buf, "KP_ENTER");
			break;
			case KeyCode::KEY_KP_EQUAL:
			strcpy(buf, "KP_EQUA");
			break;
			case KeyCode::KEY_LEFT_SHIFT:
			strcpy(buf, "LEFT_SHIFT");
			break;
			case KeyCode::KEY_LEFT_CONTROL:
			strcpy(buf, "LEFT_CONTROL");
			break;
			case KeyCode::KEY_LEFT_ALT:
			strcpy(buf, "LEFT_ALT");
			break;
			case KeyCode::KEY_LEFT_SUPER:
			strcpy(buf, "LEFT_SUPER");
			break;
			case KeyCode::KEY_RIGHT_SHIFT:
			strcpy(buf, "RIGHT_SHIFT");
			break;
			case KeyCode::KEY_RIGHT_CONTROL:
			strcpy(buf, "RIGHT_CONTROL");
			break;
			case KeyCode::KEY_RIGHT_ALT:
			strcpy(buf, "RIGHT_ALT");
			break;
			case KeyCode::KEY_RIGHT_SUPER:
			strcpy(buf, "RIGHT_SUPER");
			break;
			case KeyCode::KEY_MENU:
			strcpy(buf, "MENU");
			break;
			default:
			strcpy(buf, "UNKNOWN");
			}
		};

		m_event_dispatcher.add_event_listener<EventKeyPressed>([&](EventKeyPressed &event) {
			char buf[16];
			keyToStr(event.key_code, buf);
			if(event.repeated) {
					LOG_INFO("Key pressed {0}, repeted", buf);
			} else {
				LOG_INFO("Key pressed {0}", buf);
			}
			Input::PressKey(event.key_code);
		});

		m_event_dispatcher.add_event_listener<EventKeyReleased>([&](EventKeyReleased &event) {
			char buf[16];
			keyToStr(event.key_code, buf);
			LOG_INFO("Key released {0}", buf);
			Input::ReleaseKey(event.key_code);
		});

		m_pWindow->set_event_callback([&](BaseEvent &event) {
			m_event_dispatcher.dispatch(event);
		});

		//-------------------------------------------------------------------//
		p_shader_program = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);
		if(!p_shader_program->isCompiled()) {
			return false;
		}

		BufferLayout buffer_layout{ShaderDataType::Float3, ShaderDataType::Float3};

		p_vao = std::make_unique<VertexArray>();
		p_positions_colors_vbo = std::make_unique<VertexBuffer>(positions_colors2, sizeof(positions_colors2), buffer_layout);
		p_index_buffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

		p_vao->add_vertex_buffer(*p_positions_colors_vbo);
		p_vao->set_index_buffer(*p_index_buffer);
		//-------------------------------------------------------------------//

		while(!m_bCloseWindow) {

			Render_OpenGL::set_clear_color(m_background_color[0], m_background_color[1], m_background_color[2], m_background_color[3]);
			Render_OpenGL::clear();

			p_shader_program->bind();

			glm::mat4 scale_matrix(
				scale[0], 0, 0, 0,
				0, scale[1], 0, 0,
				0, 0, scale[2], 0,
				0, 0, 0, 1
			);

			float rotate_in_rads = glm::radians(rotate);
			glm::mat4 rotate_matrix(
				cos(rotate_in_rads), sin(rotate_in_rads), 0, 0,
			-sin(rotate_in_rads), cos(rotate_in_rads), 0, 0,
													0, 0, 1, 0,
													0, 0, 0, 1
			);

			glm::mat4 translate_matrix(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				translate[0], translate[1], translate[2], 1
			);

			glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;

			p_shader_program->setMatrix4("model_matrix", model_matrix);
			camera.set_position_rotation(glm::vec3(camera_position[0], camera_position[1], camera_position[2]),
				glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
			camera.set_projection_mode(perspective_camera ? Camera::ProjectionMode::Perspective : Camera::ProjectionMode::Orthographic);
			p_shader_program->setMatrix4("view_ptojection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
			Render_OpenGL::draw(*p_vao);

			//-------------------------------------------------------------------//
			UIModule::on_ui_draw_begin();
			bool show = true;
			UIModule::ShowExampleAppDockSpace(&show);
			ImGui::ShowDemoWindow();
			ImGui::Begin("Background Color Window");
			ImGui::ColorEdit4("Background Color", m_background_color);
			ImGui::SliderFloat3("scale", scale, 0.f, 2.f);
			ImGui::SliderFloat("rotate", &rotate, 0.f, 360.f);
			ImGui::SliderFloat3("translate", translate, -1.f, 1.f);
			ImGui::SliderFloat3("Camera positon", camera_position, -10.f, 10.f);
			ImGui::SliderFloat3("Camera rotation", camera_rotation, -180.f, 180.f);
			ImGui::Checkbox("Perspective camera", &perspective_camera);
			ImGui::End();
			//-------------------------------------------------------------------//

			on_ui_draw();

			UIModule::on_ui_draw_end();

			m_pWindow->on_update();
			on_update();
		}
		m_pWindow = nullptr;
		return 0;
	}

	void Application::on_update() noexcept {
	}
}