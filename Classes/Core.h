#pragma once

#include "cocos2d.h"

class Core {
private:
	bool init();

public:
	static Core* sharedCore();

};
