#include <iostream>
#include <memory>
#include <SimpleEngineCore/Application.hpp>
#include <SimpleEngineCore/Input.hpp>
#include <imgui/imgui.h>

class SimpleEngineEditor : public SimpleEngine::Application {
	virtual void on_update() noexcept override {
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_W)) {
			camera_position[2] -= 0.001f;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_S)) {
			camera_position[2] += 0.001f;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_A)) {
			camera_position[0] -= 0.001f;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_D)) {
			camera_position[0] += 0.001f;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_E)) {
			camera_position[1] -= 0.001f;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_Q)) {
			camera_position[1] += 0.001f;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_UP)) {
			camera_rotation[0] -= 0.05f;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_DOWN)) {
			camera_rotation[0] += 0.05f;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_RIGHT)) {
			camera_rotation[1] -= 0.05f;
		}
		if(SimpleEngine::Input::IsKeyPressed(SimpleEngine::KeyCode::KEY_LEFT)) {
			camera_rotation[1] += 0.05f;
		}
	}

	virtual void on_ui_draw() noexcept override {
		ImGui::Begin("Editor");
		ImGui::SliderFloat3("Camera positon", camera_position, -10.f, 10.f);
		ImGui::SliderFloat3("Camera rotation", camera_rotation, -180.f, 180.f);
		ImGui::Checkbox("Perspective camera", &perspective_camera);
		ImGui::End();
	}

private:
	int frame = 0;
};

int main(int argc, char *argv[]) {

	auto pSimpleEngineEditor = std::make_unique<SimpleEngineEditor>();

	int returnCode = pSimpleEngineEditor->start(640, 480, "SimpleEngine app");

	//system("pause");

	return returnCode;
}