#include "Engine/Core/CoreEngine.h"

int main(int argc, char* argv[]) {
	if (!CoreEngine::GetInstance()->Oncreate("Engine", 800, 600)) {
		std::cout << "Engine failed to initialize" << std::endl;
		return 0;
	}
	CoreEngine::GetInstance()->Run();
	return 0;
}