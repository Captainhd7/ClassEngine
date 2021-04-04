#include "GameScene.h"

GameScene::GameScene() {
	shape = nullptr;
}

GameScene::~GameScene() {
	model = nullptr;

	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate(){
	Debug::Info("GameScene created", __FILE__, __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 8.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLight(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));

	model = new Model("Resources/Models/Bleb_bru.obj", "Resources/Materials/Bleb_bru.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	//model = new Model("Resources/Models/smalleredit.obj", "Resources/Materials/smalleredit.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	//model = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_){
	shape->Update(deltaTime_);
}

void GameScene::Render() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//wireframe
	shape->Render(CoreEngine::GetInstance()->GetCamera());
}
