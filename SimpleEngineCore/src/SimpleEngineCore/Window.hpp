#pragma once
#include <string>

class GLFWwindow;

namespace SimpleEngine {
	struct Window {
#pragma region hide
		Window(const Window &) = delete;
		Window(Window &&) = delete;
		Window &operator=(const Window &) = delete;
		Window &operator=(Window &&) = delete;

#pragma endregion
	public:
		Window(std::string title, const unsigned int width, const unsigned int height) noexcept;
		~Window() noexcept;
		void on_update() noexcept;
		unsigned int get_width() const noexcept;
		unsigned int get_height() const noexcept;
	private:
		int init() noexcept;
		void shutdown() noexcept;

		GLFWwindow *m_pWin;
		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;
	};
}