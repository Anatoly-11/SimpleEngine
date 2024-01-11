#include <iostream>
#include <memory>
#include <SimpleEngineCore/Application.hpp>

class MyApp : public SimpleEngine::Application {
	virtual void on_update() noexcept override {
		//std::cout << "Upfdate frame: " << frame++ << std::endl;
	}
private:
	int frame = 0;
};

int main(int argc, char *argv[]) {
	auto myApp = std::make_unique<MyApp>();
	int res = myApp->start(640, 480, "My first app");
	return res;
}