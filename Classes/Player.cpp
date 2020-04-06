#include <random>
#include <ctime>
#include <vector>

#include "Player.h"

using namespace cocos2d;

Player::Player() {
	init();
}
Player::~Player() {

}

Color Player::getRandomColor(Color currentColor)
{
	std::mt19937 gen(time(NULL));
	std::uniform_int_distribution<int> uid(1, 3);

	Color newColor = static_cast<Color>(uid(gen));
	
	/*for (; newColor == currentColor;) {
		newColor = static_cast<Color>(uid(gen));
	}
	*/
	return newColor;
}

void Player::changeColor() {

	Color newColor = getRandomColor(Core::sharedCore()->getPlayerColor());

	Core::sharedCore()->setPlayerColor(newColor);

	if (this->getNumberOfRunningActions() > 0)
	{
		this->stopAllActions();
	}

	this->runAction(_mainSequence);

	if (newColor == Color::Red)
	{
		this->runAction(_redAnimation);
	}

	if (newColor == Color::Green)
	{
		this->runAction(_greenAnimation);
	}

	if (newColor == Color::Blue)
	{
		this->runAction(_blueAnimation);
	}
}



bool Player::init() {

	

	auto redAnimate = Animate::create(
		AnimationCache::getInstance()->getAnimation("RED"));
	auto greenAnimate = Animate::create(
		AnimationCache::getInstance()->getAnimation("GREEN"));
	auto blueAnimate = Animate::create(
		AnimationCache::getInstance()->getAnimation("BLUE"));

	// m_uReference += 1
	_redAnimation = RepeatForever::create(redAnimate);
	_greenAnimation = RepeatForever::create(greenAnimate);
	_blueAnimation = RepeatForever::create(blueAnimate);

	_redAnimation->retain();
	_greenAnimation->retain();
	_blueAnimation->retain();

	_mainSequence = Sequence::create(DelayTime::create(2.0f), Blink::create(1.0f, 10),
		CallFunc::create(this, CC_CALLFUNC_SELECTOR(Player::changeColor)), nullptr);

	//_mainSequence->setTag(1000);

	//redSprite->runAction(RepeatForever::create(animate));

	changeColor();

	return true;
}

//Color Player::getColor() {
//	return Core::sharedCore()->getPlayerColor();
//}

void Player::update(float deltaTime) {

}

