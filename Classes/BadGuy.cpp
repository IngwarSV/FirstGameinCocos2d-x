#include "BadGuy.h"
#include <string>

void BadGuy::destroyMe()
{
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this);

	if (this->getParent())
	{
		this->getParent()->removeChild(this);
	}
}

bool BadGuy::init()
{
	// initializing our bad guy from SpriteFrameCache, not only the color, but dimensions
	this->initWithSpriteFrameName("cell_blue_1.png");
	// as our sprite is not finalized one - set it invisible!
	this->setVisible(false);

	return true;
}

void BadGuy::update(float)
{
}

void BadGuy::move(float)
{
}

void BadGuy::prepare()
{
	std::string image{};
	SpriteFrame* frame;

	Color color = static_cast<Color>(_core->getRandom(1, 3));

	if (color == Color::Red)
	{
		image = "cell_red_1.png";
		_color = Color::Red;
	}
	else if (color == Color::Green)
	{
		image = "cell_green_1.png";
		_color = Color::Green;
	}
	else
	{
		image = "cell_blue_1.png";
		_color = Color::Blue;
	}

	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(image);
	this->setSpriteFrame(frame);
	this->_radius = calcRadius(this);
	this->setVisible(true);

}

BadGuy::BadGuy()
{
	//init();
}

BadGuy::~BadGuy()
{
}

void BadGuy::removeBadGuy(/*Sound sound*/)
{
	//_core->playEffect(sound);

	Animation* explosion = AnimationCache::getInstance()->getAnimation("EXPLOSION");
	Animate* animate = Animate::create(explosion);

	auto sequence = Sequence::create(animate,
		CallFunc::create(this, CC_CALLFUNC_SELECTOR(BadGuy::destroyMe)), nullptr);

	this->stopAllActions();

	this->runAction(sequence);
}

float BadGuy::getRadius()
{
	return _radius;
}

Color BadGuy::getColor()
{
	return _color;
}

void BadGuy::setColor(Color color)
{
	_color = color;
}

//bool BadGuy::getMoving()
//{
//	return _isMoving;
//}

void BadGuy::triggerIsMoving()
{
	_isMoving = false;

	const auto v_badGuys = _core->getBadGuys();

	for (auto bad_guy: v_badGuys)
	{
		if (isCollide(this->getPosition(), 3, bad_guy->getPosition(), 3))
		{
			auto angle = _core->getRandom(0, 360);
			bad_guy->runAction(MoveTo::create(0.5f, bad_guy->getPosition() + Vec2(cos(angle) * 10, sin(angle) * 10))); // radians????
			angle = (angle + 180) % 360;
			this->runAction(MoveTo::create(0.5f, this->getPosition() + Vec2(cos(angle) * 10, sin(angle) * 10))); // radians????
		}
	}
}

// breathing of BGuy)
// all actions below inherit ActionInterval which in his turn inherits FiniteTimeAction
ActionInterval* BadGuy::getRepeatAction()
{
	ActionInterval* action = nullptr;

	ScaleBy* scale = ScaleBy::create(2.5f, 1.3f);
	ActionInterval* reverse = scale->reverse(); // ScaleBy?

	action = RepeatForever::create(Sequence::create(scale, reverse, NULL)); // nullptr?
	return action;
}

FiniteTimeAction* BadGuy::getMoveAction() // can it be Action, ActionInterval?
{
	this->_isMoving = true;

	// This is the bad guy's speed
	float modifiedBadGuySpeed = 4.0f;

	float distance = this->getPosition().getDistance(_core->getPlayerPreviousPosition());

	modifiedBadGuySpeed = distance / 500.0f * modifiedBadGuySpeed;

	FiniteTimeAction* move = MoveTo::create(modifiedBadGuySpeed, _core->getPlayerPreviousPosition());

	return Sequence::create(move, NULL); // why sequence, can't it be just an Action...?
}
