#include "GameScene.h"

GameScene::GameScene() {

}

GameScene::~GameScene() {

}

bool GameScene::OnCreate(){
	Debug::Info("GameScene created", __FILE__, __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 8.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLight(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));

	CollisionHandler::GetInstance()->OnCreate();

	Model* blebModel = new Model("Resources/Models/Bleb_bru.obj", "Resources/Materials/Bleb_bru.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* appleModel = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(blebModel);
	SceneGraph::GetInstance()->AddModel(appleModel);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(blebModel, glm::vec3(0.0f)), "Bleb");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel, glm::vec3(0.0f, 4.0f, 0.0f)), "Apple");

	blebModel = nullptr;
	appleModel = nullptr;

	return true;
}

void GameScene::Update(const float deltaTime_){
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void GameScene::Render() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//wireframe
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}
