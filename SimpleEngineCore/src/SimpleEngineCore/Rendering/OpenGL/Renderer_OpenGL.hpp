#pragma once

struct GLFWwindow;

namespace SimpleEngine {

	class VertexArray;

	class Render_OpenGL {
	public:
		static bool init(GLFWwindow *pWindow) noexcept;

		static void draw(const VertexArray &vertex_array) noexcept;
		static void set_clear_color(const float r, const float g, const float b, const float a) noexcept;
		static void clear() noexcept;
		static void set_viewport(const unsigned int width, const unsigned int height, const unsigned int left_offset = 0,
			const unsigned int bottom_offset = 0)noexcept;

		static const char *get_vendor_str() noexcept;
		static const char *get_renderer_str() noexcept;
		static const char *get_version_str() noexcept;
	};
}