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
	//Re-Init Core
	//Core::sharedCore();

	// Getting windows size
	auto winSize = Director::getInstance()->getWinSize();

	// Setting position in the middle of the windows
	Vec2 position(winSize.width / 2, winSize.height / 2);
	

	// Adding game background
	auto background = Sprite::create("Images/game_background.png");
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(position);
	this->addChild(background, -1000);

	// Adding blood overlay
	auto bloodOverlay = Sprite::create("Images/overlay.png");
	bloodOverlay->setOpacity(0);
	bloodOverlay->setAnchorPoint(Vec2(0.5f, 0.5f));
	bloodOverlay->setPosition(position);
	this->addChild(bloodOverlay, 1000, "OVERLAY");


	// Adding Player
	_player = Player::create();
	_player->setAnchorPoint(Vec2(0.5f, 0.5f));
	_player->setPosition(position);
	_core->setPlayerPreviousPosition(position);

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

	//Add labels
	std::string health = "Health: " + std::to_string(_core->getPlayerHitpoints());

	_lblHealth = Label::createWithTTF(health, "fonts/chemrea.ttf", 16);
	_lblHealth->setColor(Color3B::RED);
	_lblHealth->setPosition(Vec2(winSize.width / 2 - 50, winSize.height - 20));
	this->addChild(_lblHealth, 10000);

	std::string score = "Score: " + std::to_string(_core->getPlayerScore());

	_lblScore = Label::createWithTTF(score, "fonts/chemrea.ttf", 16);
	_lblScore->setColor(Color3B::YELLOW);
	_lblScore->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 20));
	this->addChild(_lblScore, 10000);



	return true;
}

void GameLayer::update(float deltaTime) {
	this->playerMove(deltaTime);
	this->updateBadGuys(deltaTime);
	this->handleCollision(deltaTime);
	this->updateUi(deltaTime);
}

void GameLayer::handleCollision(float dt)
{
	if (_pool.empty())
	{
		return;
	}

	for (auto it = _pool.begin(); it != _pool.end(); )
	{
		BadGuy* baddie = static_cast<BadGuy*>(*it);
		bool flag = true;

		if (isCollide(baddie->getPosition(), baddie->getRadius(), _player->getPosition(), _player->getRadius()))
		{
			//Sound sound = Sound::None;

			if (baddie->getColor() == _core->getPlayerColor())
			{
				/*sound = Sound::Explosion_Good;*/
				_core->playerScored();
			}
			else
			{
				//Deduct one hitpoint from player
				/*sound = Sound::Explosion_Bad;*/
				_core->playerHit();
			}

			//Destroy the baddie
			if (_pool.contains(baddie)) {

				baddie->removeBadGuy(/*sound*/);

				//update iterator
				it = _pool.erase(it);
				flag = false;
			}

			//core->playEffect(sound);
		}

		if (flag)
		{
			it++;
		}
	}

	//Test if game over condition
	if (_core->getPlayerHitpoints() < 1)
	{
		//Game Over!
		Director::getInstance()->replaceScene(GameMenu::createScene());
	}
	else if (_core->getPlayerHitpoints() < 10)
	{
		auto hp = _core->getPlayerHitpoints();

		float damage = (1.0f - ((float)hp / 10.0f)) * 255.0f;

		auto overlay = this->getChildByName("OVERLAY");
		overlay->setOpacity(damage);
	}

	// Check our game win condition
	if (_core->getPlayerScore() >= 10)
	{
		//Win!
		Director::getInstance()->replaceScene(GameMenu::createScene());
	}
}

void GameLayer::updateUi(float dt)
{
	std::string score = "Score: " + std::to_string(_core->getPlayerScore());
	std::string health = "Health: " + std::to_string(_core->getPlayerHitpoints());

	_lblHealth->setString(health);
	_lblScore->setString(score);
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
	if (!_core->_playerIsMoving)
	{
		return;
	}

	/*if (core->getTargetPostion().equals(Vec2::ZERO))
	{
		return;
	}*/

	auto playerPrevPosition = _core->getPlayerPreviousPosition();
	auto playerPosition = _player->getPosition();
	auto targetPosition = _core->getTargetPosition();

	float distance = playerPrevPosition.getDistance(playerPosition);

	if (distance > 10)
	{
		CCLOG("CRAZY MOVE HAPPENED");
	}

	float previousDistance = playerPrevPosition.getDistance(targetPosition);
	float currentDistance = playerPosition.getDistance(targetPosition);

	if (currentDistance < 1 || previousDistance < 0)
	{
		_core->_playerIsMoving = false;
		return;
	}

	Vec2 newPosition = Vec2(playerPosition);

	// Set new position based on the elapsed time (dt) for this frame
	// As well we must take into account the angle at which the player
	// needs to move
	size_t speed = _core->getPlayerSpeed();
	newPosition.x = newPosition.x +
		(deltaTime * speed * cosf(_core->getTargetAngle()));
	newPosition.y = newPosition.y +
		(deltaTime * speed * sinf(_core->getTargetAngle()));

	_player->setPosition(newPosition);

	_core->setPlayerPreviousPosition(newPosition);

}

void GameLayer::updateBadGuys(float deltaTime)
{
	_gameTime += deltaTime;

	if (_gameTime > _badGuysAmount * 5) {
		_badGuysAmount += 1;
		this->addBadGuy();
	}

}

void GameLayer::addBadGuy()
{
	//if (_pool.empty())
	//{
	auto _badGuy = BadGuy::create();
	//auto _badGuy = new BadGuy();
	_pool.pushBack(_badGuy);
	//}
	BadGuy* badGuy = static_cast<BadGuy*>(_pool.back());
	//_pool.popBack();

	badGuy->prepare();

	Vec2 pos;

	Size window = Director::getInstance()->getWinSize();

	do
	{
		float x = _core->getRandom(0, window.width);
		float y = _core->getRandom(0, window.height);
		pos = Vec2(x, y);

		if (!isCollide(pos, badGuy->getRadius(), _player->getPosition(), _player->getRadius() * 3.0f))
		{
			break;
		}

	} while (true);

	badGuy->setPosition(pos);

	if (!badGuy->getParent())
	{
		this->addChild(badGuy, 900, "BADGUY");
	}

	ActionInterval* action = badGuy->getRepeatAction();
	if (action)
	{
		badGuy->runAction(action);
	}

	if (badGuy->getColor() != _core->getPlayerColor())
	{
		FiniteTimeAction* move = badGuy->getMoveAction();

		if (move)
		{
			badGuy->runAction(move);
		}
	}
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

	// angle в радианах
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

