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
	this->playerMove(deltaTime);


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
	this->processEvent(event);
}

void GameLayer::onMouseMove(Event* event) {

}

void GameLayer::playerMove(float deltaTime)
{
	auto core = Core::sharedCore();

	if (!core->_playerIsMoving)
	{
		return;
	}

	/*if (core->getTargetPostion().equals(Vec2::ZERO))
	{
		return;
	}*/

	auto playerPrevPosition = core->getPlayerPreviousPosition();
	auto playerPosition = _player->getPosition();
	auto targetPosition = core->getTargetPosition();

	float distance = playerPrevPosition.getDistance(playerPosition);

	if (distance > 10)
	{
		CCLOG("CRAZY MOVE HAPPENED");
	}

	float previousDistance = playerPrevPosition.getDistance(targetPosition);
	float currentDistance = playerPosition.getDistance(targetPosition);

	if (currentDistance < 1 || previousDistance < 0)
	{
		core->_playerIsMoving = false;
		return;
	}

	Vec2 newPosition = Vec2(playerPosition);

	// Set new position based on the elapsed time (dt) for this frame
	// As well we must take into account the angle at which the player
	// needs to move
	size_t speed = core->getPlayerSpeed();
	newPosition.x = newPosition.x +
		(deltaTime * speed * cosf(core->getTargetAngle()));
	newPosition.y = newPosition.y +
		(deltaTime * speed * sinf(core->getTargetAngle()));

	_player->setPosition(newPosition);

	core->setPlayerPreviousPosition(newPosition);

}

void GameLayer::processEvent(Event* event)
{
	if (!event) {
		return;
	}

	Vec2 locationInView = Vec2::ZERO;

	switch (event->getType())
	{
	case Event::Type::MOUSE:
	{
		auto mouseEvent = static_cast<EventMouse*>(event);
		locationInView = mouseEvent->getLocationInView();
	}
	break;

	case Event::Type::GAME_CONTROLLER:
	case Event::Type::TOUCH:
	case Event::Type::KEYBOARD:
	{
		CCLOG("WE DONT HANDLE YET");
		return;
	}
	default:
		CCLOG("WE WONT HANDLE");
		return;

	}

	Core* core = Core::sharedCore();

	// Get the angle between p1 & click location
	Vec2 playerPosition = _player->getPosition();
	float dY = locationInView.y - playerPosition.y;
	float dX = locationInView.x - playerPosition.x;

	// angle � ��������
	float angle = atan2f(dY, dX);
	core->setTargetAngle(angle);

	Size size = Director::getInstance()->getWinSize();

	//setting the bounds in which touch event has to be.
	// if locationInView > Vec2(size.width, size.height) -> locationInView = Vec2(size.width, size.height);
	// if locationInView < Vec2::ZERO -> locationInView = Vec2::ZERO;
	auto clampPoint = locationInView.getClampPoint(Vec2::ZERO, Vec2(size.width, size.height));
	core->setTargetPosition(clampPoint);

	core->_playerIsMoving = true;

}

