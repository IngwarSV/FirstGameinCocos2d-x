#pragma once

#include "Specification.h"
#include "Core.h"

using namespace cocos2d;

//class Core;

class BadGuy : public Sprite
{
private:
	float _radius = 0.0f;
	Color _color = Color::None;
	Core* _core = Core::sharedCore();

	void destroyMe();

public:
	bool _isMoving = false;

	virtual bool init();
	virtual void update(float);

	void move(float);
	void prepare();

	BadGuy();
	~BadGuy();

	//void removeBadGuy(Sound);

	float getRadius();

	Color getColor();
	void setColor(Color color);

	//bool getMoving();
	void triggerIsMoving();

	ActionInterval* getRepeatAction();
	FiniteTimeAction* getMoveAction();

	CREATE_FUNC(BadGuy);
};


inline float calcRadius(Sprite* s)
{
	return s->getScale() * s->getContentSize().width * 0.5f;
}


inline bool isCollide(Vec2 p1, float r1, Vec2 p2, float r2)
{
	const float a = r1 + r2;
	const float dx = p1.x - p2.x;
	const float dy = p1.y - p2.y;

	return a * a > (dx * dx + dy * dy);
}
