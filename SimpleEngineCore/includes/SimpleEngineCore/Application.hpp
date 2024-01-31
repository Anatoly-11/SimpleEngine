#pragma once
#include "SimpleEngineCore/Event.hpp"
#include "SimpleEngineCore/Camera.hpp"

#include <memory>

namespace SimpleEngine {

	class Window;

	class Application {
#pragma region hide
		Application(const Application &) = delete;
		Application(Application &&) = delete;
		Application &operator=(const Application &) = delete;
		Application &operator=(Application &&) = delete;

#pragma endregion
	public:
		Application() noexcept;
		virtual ~Application() noexcept;
		virtual int start(unsigned int window_width, unsigned int window_height, const char *title) noexcept;

		virtual void on_update() noexcept;

		virtual void on_ui_draw() noexcept;

		virtual void on_mouse_button_pressed(const MouseButton button_code, const double _x_pos, const double _y_pos, const bool pressed) noexcept;

		glm::vec2 get_current_cursor_position() const noexcept;

		float camera_position[3];
		float camera_rotation[3];
		bool perspective_camera;
		Camera camera;

	private:
		EventDispatcher m_event_dispatcher;
		bool m_bCloseWindow;

		std::unique_ptr<Window> m_pWindow;
	};
}