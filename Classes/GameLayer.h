#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "BadGuy.h"


class GameLayer : public cocos2d::Layer
{
private:
	Core* _core = Core::sharedCore();
	Player* _player = nullptr;
	float _gameTime = 0.0f;
	int _badGuysAmount = 0;
	cocos2d::Vector<Sprite*> _pool = cocos2d::Vector<Sprite*>(100);

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

	void updateBadGuys(float deltaTime);

	void addBadGuy();

	void processEvent(cocos2d::Event* event);
};