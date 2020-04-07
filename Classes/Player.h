#pragma once

#include "Core.h"
#include "Specification.h"

class Player : public cocos2d::Sprite {
private:
	const float kPlayerRadius = 10.0f;
	// Actions
	cocos2d::Action *_redAnimation;
	cocos2d::Action* _greenAnimation;
	cocos2d::Action* _blueAnimation;

	Core* _core = Core::sharedCore();

	cocos2d::Sequence* _mainSequence;

	Color getRandomColor(Color c);

public:
	Player();
	virtual ~Player(); //? virtual

	

	virtual bool init();

	//Color getColor();
	void changeColor();

	int getRadius();

	virtual void update(float deltaTime);

	CREATE_FUNC(Player);


};
