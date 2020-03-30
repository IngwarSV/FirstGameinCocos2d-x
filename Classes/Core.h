#pragma once

#include "cocos2d.h"

#include "Specification.h"

class Core {
private:
	Color _playerColor = Color::None;


	bool init();

public:
	static Core* sharedCore();

	void setPlayerColor(Color newColor);

	Color getPlayerColor();
};
