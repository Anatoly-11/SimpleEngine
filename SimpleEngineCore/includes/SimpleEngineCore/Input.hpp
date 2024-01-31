#pragma once

#include "Keys.hpp"

namespace SimpleEngine {

	class Input {
	public:
		static bool IsKeyPressed(const KeyCode key_code) noexcept;
		static void PressKey(const KeyCode key_code) noexcept;
		static void ReleaseKey(const KeyCode key_code) noexcept;
		static const char *KeyToStr(const KeyCode key_code) noexcept;

		static bool IsMouseButtonPressed(const MouseButton mouse_button) noexcept;
		static void PressMouseButton(const MouseButton mouse_button) noexcept;
		static void ReleaseMouseButton(const MouseButton mouse_button) noexcept;
		static const char *MousrButtonToStr(const MouseButton mouse_button) noexcept;
	private:
		static bool m_keys_pressed[];
		static bool m_mouse_buttons_pressed[];
	};
}