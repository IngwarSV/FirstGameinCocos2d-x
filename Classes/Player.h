#pragma once

#include "cocos2d.h"
#include "Core.h"

class Player : public cocos2d::Sprite {
private:
	// Actions
	cocos2d::Action *_redAnimation;
	cocos2d::Action* _greenAnimation;
	cocos2d::Action* _blueAnimation;

	Core* _core;

	Sequence* _mainSequence;

	void changeColor();

public:
	Player();
	virtual ~Player(); //? virtual

	virtual bool init();

	virtual void update(float deltaTime);

	CREATE_FUNC(Player);


};
