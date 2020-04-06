#pragma once

#include "cocos2d.h"
#include "Player.h"
//#include "Baddie.h"


class GameLayer : public cocos2d::Layer
{
private:
	Player* _player = nullptr;
public:
	GameLayer();

	static cocos2d::Scene* createScene();

	virtual bool init() override;

	virtual void update(float deltaTime) override;

	CREATE_FUNC(GameLayer);

	bool onTouchesBegin(cocos2d::Touch*, cocos2d::Event*);
	bool onTouchesMoved(cocos2d::Touch*, cocos2d::Event*);
	bool onTouchesEnded(cocos2d::Touch*, cocos2d::Event*);

	void onMouseUP(cocos2d::Event*);
	void onMouseDown(cocos2d::Event*);
	void onMouseMove(cocos2d::Event*);

	void playerMove(float deltaTime);

	void processEvent(cocos2d::Event* event);
};