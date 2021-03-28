#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() {
	window = nullptr;
	isRunning = false;
	fps = 60;
	gameInterface = nullptr;
	currentSceneNum = 0;
}

CoreEngine::~CoreEngine() {
}

CoreEngine* CoreEngine::GetInstance() {
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new CoreEngine);
	}
	return engineInstance.get();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_) {
	Debug::OnCreate();
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Window failed to initialize", __FILE__, __LINE__);
		OnDestroy();
		return isRunning = false;
	}

	//ShaderHandler::GetInstance()->CreateProgram("colorShader", "Engine/Shader/ColorVertexShader.glsl", "Engine/Shader/ColorFragmentShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("basicShader", "Engine/Shader/VertexShader.glsl", "Engine/Shader/FragmentShader.glsl");

	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			std::cout << "Game failed to initialize" << std::endl;
			Debug::FatalError("Game failed to initialize", __FILE__, __LINE__);
			OnDestroy();
			return isRunning = false;
		}
	}

	Debug::Info("Everything worked", __FILE__, __LINE__);
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
	OnDestroy();
}

void CoreEngine::Exit() {
	isRunning = false;
}

bool CoreEngine::GetIsRunning() const {
	return isRunning;
}

int CoreEngine::GetCurrentScene() const
{
	return currentSceneNum;
}

float CoreEngine::GetScreenWidth() const
{
	return static_cast<float>(window->GetWidth());
}

float CoreEngine::GetScreenHeight() const
{
	return static_cast<float>(window->GetHeight());
}

Camera* CoreEngine::GetCamera() const {

	return camera;
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_) {
	gameInterface = gameInterface_;
}

void CoreEngine::SetCurrentScene(int sceneNum_) {
	currentSceneNum = sceneNum_;
}

void CoreEngine::SetCamera(Camera* camera_) {
	camera = camera_;
}

void CoreEngine::Update(const float deltaTime_) {
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}

}

void CoreEngine::Render() {
	//background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (gameInterface) {
		gameInterface->Render();
	}
	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy() {
	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstace()->OnDestroy();

	delete gameInterface;
	gameInterface = nullptr;

	delete camera; 
	camera = nullptr;

	delete window;
	window = nullptr;

	SDL_Quit();
	exit(0);
}
