#pragma once

#include "cocos2d.h"
#include "Player.h"
//#include "Baddie.h"


class GameLayer : public cocos2d::Layer
{
private:

public:
	GameLayer();

	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float deltaTime);

	CREATE_FUNC(GameLayer);

};