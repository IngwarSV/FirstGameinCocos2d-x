#pragma once

#include "cocos2d.h"

#include "Specification.h"
#include "Player.h"

class Core {
private:
	//Player _player;
	Color _playerColor = Color::None;
	cocos2d::Vec2 _targetPosition = cocos2d::Vec2(0.0f, 0.0f);

	cocos2d::Vec2 _playerPreviousPosition = cocos2d::Vec2(0.0f, 0.0f);


	float _targetAngle = 0.0f;

	bool init();

public:
	static Core* sharedCore();

	void setPlayerColor(Color newColor);

	void setTargetPosition(cocos2d::Vec2 position);

	void setPlayerPreviousPosition(cocos2d::Vec2 position);

	void setTargetAngle(float angle);

	Color getPlayerColor();

	//Player getPlayer();

	cocos2d::Vec2 getTargetPosition();

	cocos2d::Vec2 getPlayerPreviousPosition();

	float getTargetAngle();


};
