#pragma once

#include <vector>
#include "cocos2d.h"
#include <assert.h>
#include <random>
#include <ctime>

#include "Specification.h"
//#include "Player.h"

class Core {
private:
	std::mt19937 _randomGenerator;
	size_t _playerSpeed;
	bool _playerMoving = false;

	//Player _player;
	Color _playerColor = Color::None;
	cocos2d::Vec2 _targetPosition = cocos2d::Vec2(0.0f, 0.0f);

	cocos2d::Vec2 _playerPreviousPosition = cocos2d::Vec2(0.0f, 0.0f);

	std::vector<cocos2d::Sprite*> _badGuys{};

	float _targetAngle = 0.0f;


	bool init();

public:

	bool _playerIsMoving = false;

	

	static Core* sharedCore();

	void setPlayerColor(Color newColor);

	void setTargetPosition(cocos2d::Vec2 position);

	void setPlayerPreviousPosition(cocos2d::Vec2 position);

	void setTargetAngle(float angle);

	void setPlayerSpeed(size_t speed);

	Color getPlayerColor();

	//Player getPlayer();

	cocos2d::Vec2 getTargetPosition();

	cocos2d::Vec2 getPlayerPreviousPosition();

	float getTargetAngle();

	size_t getPlayerSpeed();

	const std::vector<cocos2d::Sprite*>& getBadGuys() const;

	int getRandom(int min, int max);

};
