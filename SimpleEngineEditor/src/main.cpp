#include <iostream>
#include <memory>
#include <SimpleEngineCore/Application.hpp>
#include <SimpleEngineCore/Input.hpp>
#include <SimpleEngineCore/Keys.hpp>
#include <imgui/imgui.h>

class SimpleEngineEditor : public SimpleEngine::Application {
	virtual void on_update() noexcept override {
		glm::vec3 movement_delta{0.f, 0.f, 0.f};
		glm::vec3 rotation_delta{0.f, 0.f, 0.f};
		float dm = 0.005f, rm = 0.05f;
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_W)) {
			movement_delta.x += dm;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_S)) {
			movement_delta.x -= dm;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_A)) {
			movement_delta.y -= dm;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_D)) {
			movement_delta.y += dm;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_E)) {
			movement_delta.z += dm;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_Q)) {
			movement_delta.z -= dm;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_UP)) {
			rotation_delta.y -= rm;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_DOWN)) {
			rotation_delta.y += rm;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_RIGHT)) {
			rotation_delta.z -= rm;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_LEFT)) {
			rotation_delta.z += rm;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_P)) {
			rotation_delta.x += rm;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_O)) {
			rotation_delta.x -= rm;
		}
		if(SimpleEngine::Input::IsMouseButtonPressed(SimpleEngine::MouseButton::MOUSE_BUTTON_RIGHT)) {
			glm::vec2 current_cursor_position = get_current_cursor_position();
			if(SimpleEngine::Input::IsMouseButtonPressed(SimpleEngine::MouseButton::MOUSE_BUTTON_LEFT)) { 
				camera.move_right((current_cursor_position.x - static_cast<float>(m_initial_mouse_pos_x)) / 100.f);
				camera.move_up((current_cursor_position.y - static_cast<float>(m_initial_mouse_pos_y)) / 100.f);
			} else {
				rotation_delta.z += (current_cursor_position.x - static_cast<float>(m_initial_mouse_pos_x)) / 5.f;
				rotation_delta.y -= (current_cursor_position.y - static_cast<float>(m_initial_mouse_pos_y)) / 5.f;
			}
			m_initial_mouse_pos_x = current_cursor_position.x;
			m_initial_mouse_pos_y = current_cursor_position.y;
		}

		camera.add_movement_and_rotation(movement_delta, rotation_delta);
	}

	 void on_ui_draw() noexcept override {
		camera_position[0] = camera.get_camera_position().x;
		camera_position[1] = camera.get_camera_position().y;
		camera_position[2] = camera.get_camera_position().z;
		camera_rotation[0] = camera.get_camera_rotation().x;
		camera_rotation[1] = camera.get_camera_rotation().y;
		camera_rotation[2] = camera.get_camera_rotation().z;

		ImGui::Begin("Editor");
		if(ImGui::SliderFloat3("camera position", camera_position, -10.f, 10.f)) {
			camera.set_position(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
		}
		if(ImGui::SliderFloat3("camera rotation", camera_rotation, 0, 360.f)) {
			camera.set_rotation(glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
		}
		ImGui::Checkbox("Perspective camera", &perspective_camera);
		ImGui::End();
	}

	virtual void on_mouse_button_pressed(const SimpleEngine:: MouseButton button_code, const double _x_pos, const double _y_pos, const bool pressed) noexcept override {
		m_initial_mouse_pos_x = _x_pos;
		m_initial_mouse_pos_y = _y_pos;
	}

private:
	int frame = 0;
	double m_initial_mouse_pos_x = 0;
	double m_initial_mouse_pos_y = 0;
};

int main(int argc, char *argv[]) {

	auto pSimpleEngineEditor = std::make_unique<SimpleEngineEditor>();

	int returnCode = pSimpleEngineEditor->start(1440, 900, "SimpleEngine app");

	//system("pause");

	return returnCode;
}