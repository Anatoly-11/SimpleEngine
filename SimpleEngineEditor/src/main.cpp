#include <iostream>
#include <memory>
#include <SimpleEngineCore/Application.hpp>
#include <imgui/imgui.h>

class SimpleEngineEditor : public SimpleEngine::Application {
	virtual void on_update() noexcept override {
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

	std::cin.get();

	return returnCode;
}