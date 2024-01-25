#pragma once

struct GLFWwindow;

namespace SimpleEngine {

	class UIModule {
	public:
		static void on_window_create(GLFWwindow *pWindow) noexcept;
		static void on_window_close() noexcept;;
		static void on_ui_draw_begin() noexcept;;
		static void on_ui_draw_end() noexcept;;

		static void ShowExampleAppDockSpace(bool *p_open) noexcept;
	};
}