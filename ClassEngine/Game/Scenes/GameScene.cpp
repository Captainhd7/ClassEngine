#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

bool GameScene::OnCreate(){
	Debug::Info("GameScene created", __FILE__, __LINE__);
	return true;
}

void GameScene::Update(const float deltaTime_){
	std::cout << deltaTime_ << std::endl;
}

void GameScene::Render()
{
}
