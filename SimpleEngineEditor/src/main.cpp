#include <iostream>
#include <SimpleEngineCore/Utils/test.hpp>

int main(int argc, char *argv[]) {
	std::cout << "Hello from Simple Engine Editor" << std::endl;
	int res  = SimpleEngine::checkGLFW();
	std::cout << "Resutt is: " << res << std::endl;

	std::cin.get();
	return 0;
}