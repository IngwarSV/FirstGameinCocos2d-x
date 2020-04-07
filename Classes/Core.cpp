#include "Core.h"

using namespace cocos2d;

static bool s_firstRun = true;
static Core s_sharedCore;

bool Core::init()
{
	_randomGenerator.seed(time(NULL));
	this->setPlayerSpeed(DEFAULT_SPEED);
	//* загрузка Sprite Sheet (создание SpriteFrameCache)
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("Images/game_sprites.plist", "Images/game_sprites.png");
	//* Наш .plist содержит имена всех спрайтов, находящихся в нем.

	////auto redSprite = Sprite::createWithSpriteFrameName("player_red_1.png");


	// Getting the explosion sprites
	Vector<SpriteFrame*> explosionFrames;
	explosionFrames.reserve(12);

	
	for (auto i = 1u; i <= explosionFrames.capacity(); ++i) {
		std::string spriteName = "explosion_";

		if (i < 10u) {
			spriteName = spriteName + '0' + std::to_string(i);
		}
		else {
			spriteName = spriteName + std::to_string(i);
		}
		spriteName += ".png";
		
		/*
		alternative version
		char s[100] = {0};
		sprintf(s, "explosion_%02d.png", i);
		*/

		explosionFrames.pushBack(spritecache->getSpriteFrameByName(spriteName));
	}

	auto explosionAnimation = Animation::createWithSpriteFrames(explosionFrames, 0.05f);
	AnimationCache::getInstance()->addAnimation(explosionAnimation, "EXPLOSION");

	// Getting the red/green/blue_player sprites
	Vector<SpriteFrame*> redPlayerFrames;
	redPlayerFrames.reserve(8);

	Vector<SpriteFrame*> greenPlayerFrames;
	greenPlayerFrames.reserve(8);

	Vector<SpriteFrame*> bluePlayerFrames;
	bluePlayerFrames.reserve(8);

	for (auto i = 1u; i <= redPlayerFrames.capacity(); ++i) {
		std::string frameName = std::to_string(i) + ".png";
		
		redPlayerFrames.pushBack(spritecache->getSpriteFrameByName("player_red_" + frameName));
		greenPlayerFrames.pushBack(spritecache->getSpriteFrameByName("player_green_" + frameName));
		bluePlayerFrames.pushBack(spritecache->getSpriteFrameByName("player_blue_" + frameName));
	}

	auto redAnimation = Animation::createWithSpriteFrames(redPlayerFrames, 0.2f);
	auto greenAnimation = Animation::createWithSpriteFrames(greenPlayerFrames, 0.2f);
	auto blueAnimation = Animation::createWithSpriteFrames(bluePlayerFrames, 0.2f);

	AnimationCache::getInstance()->addAnimation(redAnimation, "RED");
	AnimationCache::getInstance()->addAnimation(greenAnimation, "GREEN");
	AnimationCache::getInstance()->addAnimation(blueAnimation, "BLUE");

	// Getting the rogue sprites
	Vector<SpriteFrame*> rogueFrames;
	rogueFrames.reserve(14);

	for (auto i = 1u; i <= rogueFrames.capacity(); ++i) {
		std::string name = "rogue_";

		if (i < 10)
		{
			name = name + "0" + std::to_string(i);
		}
		else
		{
			name = name + std::to_string(i);
		}

		name += ".png";

		rogueFrames.pushBack(spritecache->getSpriteFrameByName(name));
	}

	Animation* rogueAnimation = Animation::createWithSpriteFrames(
		rogueFrames, 0.2f);


	AnimationCache::getInstance()->addAnimation(rogueAnimation, "ROGUE");

	return true;
}

Core* Core::sharedCore()
{
	if (s_firstRun) {
		s_sharedCore.init();
		s_firstRun = false;
	}
	return &s_sharedCore;
}

void Core::setPlayerColor(Color newColor)
{
	_playerColor = newColor;
}

void Core::setTargetPosition(Vec2 position)
{
	_targetPosition = position;
}

void Core::setPlayerPreviousPosition(cocos2d::Vec2 position)
{
	_playerPreviousPosition = position;
}

void Core::setTargetAngle(float angle)
{
	_targetAngle = angle;
}

void Core::setPlayerSpeed(size_t speed)
{
	_playerSpeed = speed;
}

Color Core::getPlayerColor()
{
	return _playerColor;
}

//Player Core::getPlayer()
//{
//	return _player;
//}

Vec2 Core::getTargetPosition()
{
	return _targetPosition;
}

cocos2d::Vec2 Core::getPlayerPreviousPosition()
{
	return _playerPreviousPosition;
}

float Core::getTargetAngle()
{
	return _targetAngle;
}

size_t Core::getPlayerSpeed()
{
	return _playerSpeed;
}

const std::vector<cocos2d::Sprite*>& Core::getBadGuys() const
{
	return _badGuys;
}

int Core::getRandom(int min, int max)
{
	assert(max >= min);

	std::uniform_int_distribution<int> uid(min, max);

	return uid(_randomGenerator);
}
