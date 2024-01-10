#pragma once

namespace SimpleEngine {
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
		virtual void on_update()  noexcept;
	};
}