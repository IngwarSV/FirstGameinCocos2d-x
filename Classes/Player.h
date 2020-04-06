#pragma once

#include "cocos2d.h"
#include "Core.h"
#include "Specification.h"

//class Core;

class Player : public cocos2d::Sprite {
private:
	// Actions
	cocos2d::Action *_redAnimation;
	cocos2d::Action* _greenAnimation;
	cocos2d::Action* _blueAnimation;

	//Core* _core;

	cocos2d::Sequence* _mainSequence;

	Color getRandomColor(Color c);

public:
	Player();
	virtual ~Player(); //? virtual

	

	virtual bool init();

	//Color getColor();
	void changeColor();

	virtual void update(float deltaTime);

	CREATE_FUNC(Player);


};
