#pragma once
#include "SimpleEngineCore/Event.hpp"
#include <string>
#include <functional>
struct GLFWwindow;

namespace SimpleEngine {
	struct Window {
#pragma region hide
		Window(const Window &) = delete;
		Window(Window &&) = delete;
		Window &operator=(const Window &) = delete;
		Window &operator=(Window &&) = delete;

#pragma endregion
	public:
		using EventCallbackFn = std::function<void(BaseEvent &)>;
		Window(std::string title, const unsigned int width, const unsigned int height) noexcept;
		~Window() noexcept;
		void on_update() noexcept;
		unsigned int get_width() const noexcept;
		unsigned int get_height() const noexcept;

		void set_event_callback(const EventCallbackFn &callback) noexcept;
	private:
		struct WindowData {
			std::string title;
			unsigned int width;
			unsigned int height;
			EventCallbackFn eventCallbackFn;
		};

		int init() noexcept;
		void shutdown() noexcept;

		GLFWwindow *m_pWindow;
		WindowData m_data;
	};
}