#include "Player.h"


#include <vector>


using namespace cocos2d;

Player::Player() {

}
Player::~Player() {

}

bool Player::init() {

	_core = Core::sharedCore();

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

	_mainSequence = Sequence::create(DelayTime::create(12.0f), Blink::create(1, 10),
		CallFunc::create(this, CC_CALLFUNC_SELECTOR(Player::changeColor)), nullptr);

	//redSprite->runAction(RepeatForever::create(animate));


	return true;
}

void Player::update(float deltaTime) {

}

void Player::changeColor() {

}