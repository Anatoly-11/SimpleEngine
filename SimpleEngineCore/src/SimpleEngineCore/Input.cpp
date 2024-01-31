#include "SimpleEngineCore/Input.hpp"
#include <cstring>

namespace SimpleEngine {

	bool Input::m_keys_pressed[static_cast<size_t>(KeyCode::KEY_LAST) + 1]{};
	bool Input::m_mouse_buttons_pressed[static_cast<size_t>(MouseButton::MOUSE_BUTTON_LAST) + 1]{};

	bool Input::IsKeyPressed(const KeyCode key_code) noexcept {
		return m_keys_pressed[static_cast<size_t>(key_code)];
	}

	void Input::PressKey(const KeyCode key_code) noexcept	{
		m_keys_pressed[static_cast<size_t>(key_code)] = true;
	}

	void Input::ReleaseKey(const KeyCode key_code) noexcept {
		m_keys_pressed[static_cast<size_t>(key_code)] = false;
	}

	const char *Input::KeyToStr(const KeyCode key_code) noexcept {
		static char buf[16];
		if((int)KeyCode::KEY_SPACE <= (int)key_code && (int)key_code <= (int)KeyCode::KEY_GRAVE_ACCENT) {
			buf[0] = (char)key_code;
			buf[1] = '\0';
		} else switch(key_code) {
		case KeyCode::KEY_WORLD_1:
		strcpy(buf, "Word1");
		break;
		case KeyCode::KEY_WORLD_2:
		strcpy(buf, "Word2");
		break;
		case KeyCode::KEY_ESCAPE:
		strcpy(buf, "Esc");
		break;
		case KeyCode::KEY_ENTER:
		strcpy(buf, "Enter");
		break;
		case KeyCode::KEY_TAB:
		strcpy(buf, "Tab");
		break;
		case KeyCode::KEY_BACKSPACE:
		strcpy(buf, "Bksp");
		break;
		case KeyCode::KEY_INSERT:
		strcpy(buf, "Ins");
		break;
		case KeyCode::KEY_DELETE:
		strcpy(buf, "Del");
		break;
		case KeyCode::KEY_RIGHT:
		strcpy(buf, "Right");
		break;
		case KeyCode::KEY_LEFT:
		strcpy(buf, "Left");
		break;
		case KeyCode::KEY_DOWN:
		strcpy(buf, "Dn");
		break;
		case KeyCode::KEY_UP:
		strcpy(buf, "Up");
		break;
		case KeyCode::KEY_PAGE_UP:
		strcpy(buf, "PgUp");
		break;
		case KeyCode::KEY_PAGE_DOWN:
		strcpy(buf, "PgDn");
		break;
		case KeyCode::KEY_HOME:
		strcpy(buf, "Home");
		break;
		case KeyCode::KEY_END:
		strcpy(buf, "End");
		break;
		case KeyCode::KEY_CAPS_LOCK:
		strcpy(buf, "CpsLock");
		break;
		case KeyCode::KEY_SCROLL_LOCK:
		strcpy(buf, "ScrLock");
		break;
		case KeyCode::KEY_NUM_LOCK:
		strcpy(buf, "NumLock");
		break;
		case KeyCode::KEY_PRINT_SCREEN:
		strcpy(buf, "PrnScr");
		break;
		case KeyCode::KEY_PAUSE:
		strcpy(buf, "Pause");
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
		strcpy(buf, "F17");
		break;
		case KeyCode::KEY_F18:
		strcpy(buf, "F18");
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
		strcpy(buf, "Kp0");
		break;
		case KeyCode::KEY_KP_1:
		strcpy(buf, "Kp1");
		break;
		case KeyCode::KEY_KP_2:
		strcpy(buf, "Kp2");
		break;
		case KeyCode::KEY_KP_3:
		strcpy(buf, "Kp3");
		break;
		case KeyCode::KEY_KP_4:
		strcpy(buf, "Kp4");
		break;
		case KeyCode::KEY_KP_5:
		strcpy(buf, "Kp5");
		break;
		case KeyCode::KEY_KP_6:
		strcpy(buf, "Kp6");
		break;
		case KeyCode::KEY_KP_7:
		strcpy(buf, "Kp7");
		break;
		case KeyCode::KEY_KP_8:
		strcpy(buf, "Kp8");
		break;
		case KeyCode::KEY_KP_9:
		strcpy(buf, "Kp9");
		break;
		case KeyCode::KEY_KP_DECIMAL:
		strcpy(buf, "KpDec");
		break;
		case KeyCode::KEY_KP_DIVIDE:
		strcpy(buf, "KpDiv");
		break;
		case KeyCode::KEY_KP_MULTIPLY:
		strcpy(buf, "KpMul");
		break;
		case KeyCode::KEY_KP_SUBTRACT:
		strcpy(buf, "KpSub");
		break;
		case KeyCode::KEY_KP_ADD:
		strcpy(buf, "KpAdd");
		break;
		case KeyCode::KEY_KP_ENTER:
		strcpy(buf, "KpEnter");
		break;
		case KeyCode::KEY_KP_EQUAL:
		strcpy(buf, "KpEqual");
		break;
		case KeyCode::KEY_LEFT_SHIFT:
		strcpy(buf, "LfShift");
		break;
		case KeyCode::KEY_LEFT_CONTROL:
		strcpy(buf, "LfCtrl");
		break;
		case KeyCode::KEY_LEFT_ALT:
		strcpy(buf, "LfAlt");
		break;
		case KeyCode::KEY_LEFT_SUPER:
		strcpy(buf, "LfSuper");
		break;
		case KeyCode::KEY_RIGHT_SHIFT:
		strcpy(buf, "RtShift");
		break;
		case KeyCode::KEY_RIGHT_CONTROL:
		strcpy(buf, "RtCtrl");
		break;
		case KeyCode::KEY_RIGHT_ALT:
		strcpy(buf, "RtAlt");
		break;
		case KeyCode::KEY_RIGHT_SUPER:
		strcpy(buf, "RtSuper");
		break;
		case KeyCode::KEY_MENU:
		strcpy(buf, "Menu");
		break;
		default:
		strcpy(buf, "Unknown");
		}
		return buf;
	}

	bool Input::IsMouseButtonPressed(const MouseButton mouse_button) noexcept {
		return m_mouse_buttons_pressed[static_cast<size_t>(mouse_button)];
	}

	void Input::PressMouseButton(const MouseButton mouse_button) noexcept{
		m_mouse_buttons_pressed[static_cast<size_t>(mouse_button)] = true;
	}

	void Input::ReleaseMouseButton(const MouseButton mouse_button) noexcept{
		m_mouse_buttons_pressed[static_cast<size_t>(mouse_button)] = false;
	}

	const char *Input::MousrButtonToStr(const MouseButton mouse_button) noexcept{
		static char buf[24];
		switch(mouse_button) {
		case MouseButton::MOUSE_BUTTON_LEFT:
		strcpy(buf, "Left");
		break;
		case MouseButton::MOUSE_BUTTON_MIDDLE:
		strcpy(buf, "Middle");
		break;
		case MouseButton::MOUSE_BUTTON_RIGHT:
		strcpy(buf, "Right");
		break;
		default:
		strcpy(buf, "Unknown");
		}
		return buf;
	}
}