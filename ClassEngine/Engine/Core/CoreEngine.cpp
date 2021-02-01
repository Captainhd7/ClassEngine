#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() {
	window = nullptr;
	isRunning = false;
	fps = 60;
}

CoreEngine::~CoreEngine() {
}

CoreEngine* CoreEngine::GetInstance() {
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new CoreEngine);
	}
	return engineInstance.get();
}

bool CoreEngine::Oncreate(std::string name_, int width_, int height_) {
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		std::cout << "Window failed to initialize" << std::endl;
		Ondestroy();
		return isRunning = false;
	}
	timer.Start();
	return isRunning = true;
}

void CoreEngine::Run() {
	while (isRunning) {
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
	Ondestroy();
}

bool CoreEngine::GetIsRunning() {
	return isRunning;
}

void CoreEngine::Update(const float deltaTime_) {
	std::cout << deltaTime_ << std::endl;
}

void CoreEngine::Render() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//call game render
	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::Ondestroy() {
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}
