#include <iostream>
#include <SimpleEngineCore/Utils/test.hpp>

int main(int argc, char *argv[]) {
	std::cout << "Hello from Simple Engine Editor" << std::endl;
	SimpleEngine::sayHello();

	std::cin.get();
	return 0;
}