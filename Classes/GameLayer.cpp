#include "GameLayer.h"


using namespace cocos2d;

GameLayer::GameLayer() {
	
}

cocos2d::Scene* GameLayer::createScene() {
	auto scene = Scene::create();
	//auto gameLayer = GameLayer::create();

	scene->addChild(GameLayer::create());

	return scene;
}

bool GameLayer::init() {

	// Adding game background
	auto background = Sprite::create("Images/game_background.png");
	this->addChild(background, -1000);

	// Adding blood overlay
	auto bloodOverlay = Sprite::create("Images/overlay.png");
	bloodOverlay->setOpacity(0);
	this->addChild(bloodOverlay, 1000);


	



	return true;
}

void GameLayer::update(float deltaTime) {

}