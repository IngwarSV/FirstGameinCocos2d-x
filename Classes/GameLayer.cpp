#include <cmath>

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
	// Getting windows size
	auto winSize = Director::getInstance()->getWinSize();

	// Setting position in the middle of the windows
	Vec2 position(winSize.width / 2, winSize.height / 2);
	

	// Adding game background
	auto background = Sprite::create("Images/game_background.png");
	this->addChild(background, -1000);

	// Adding blood overlay
	auto bloodOverlay = Sprite::create("Images/overlay.png");
	bloodOverlay->setOpacity(0);
	this->addChild(bloodOverlay, 1000);

	// Adding Player
	_player = Player::create();
	_player->setAnchorPoint(Vec2(0.5f, 0.5f));
	_player->setPosition(position);
	//auto player = new Player();
	this->addChild(_player, 100);


	// Handle mouse events
	auto listener = EventListenerMouse::create();

	listener->onMouseUp = CC_CALLBACK_1(GameLayer::onMouseUP, this);
	listener->onMouseDown = CC_CALLBACK_1(GameLayer::onMouseDown, this);
	listener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// launching update method every frame
	scheduleUpdate();

	return true;
}

void GameLayer::update(float deltaTime) {



}

bool GameLayer::onTouchesBegin(Touch*, Event*)
{
	return false;
}

bool GameLayer::onTouchesMoved(cocos2d::Touch*, cocos2d::Event*)
{
	return false;
}

bool GameLayer::onTouchesEnded(cocos2d::Touch*, cocos2d::Event*)
{
	return false;
}

void GameLayer::onMouseUP(Event* event) {

}

void GameLayer::onMouseDown(Event* event) {
	EventMouse* mouseEvent = static_cast<EventMouse*>(event);
	Vec2 point = mouseEvent->getLocation();
	Core::sharedCore()->setTargetPosition(point);



}

void GameLayer::onMouseMove(Event* event) {

}

void GameLayer::playerMove(float deltaTime)
{
	if (Core::sharedCore()->getTargetPosition().equals(Vec2::ZERO)) {
		return;
	}
	
	auto playerPosition = _player->getPosition();
	auto targetPosition = Core::sharedCore()->getTargetPosition();

	// Calculating angle between playerPosition and targetPosition

	float dY = targetPosition.y - playerPosition.y;
	float dX = targetPosition.x - playerPosition.x;

	Core::sharedCore()->setTargetAngle(atan2f(dY, dX));

	float distance = cocos2d::ccpDistance(Core::sharedCore()->getTargetPosition(), 
											Core::sharedCore()->getPlayerPreviousPosition());

}

