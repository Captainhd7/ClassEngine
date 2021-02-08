#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

bool GameScene::OnCreate(){
	std::cout << "game scene" << std::endl;
	Debug::Info("GameScene created", __FILE__, __LINE__);
	return true;
}

void GameScene::Update(const float deltaTime_){
	std::cout << deltaTime_ << std::endl;
}

void GameScene::Render()
{
}
