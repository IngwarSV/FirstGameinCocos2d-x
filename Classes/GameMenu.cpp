#include "GameMenu.h"
#include <string>
//#include "audio/include/SimpleAudioEngine.h";
//
//using namespace CocosDenshion;
using namespace cocos2d;



cocos2d::Scene* GameMenu::createScene()
{
	cocos2d::Scene* scene = nullptr;

	scene = cocos2d::Scene::create();
	auto* layer = GameMenu::create();
	scene->addChild(layer);
	return scene;

}

void GameMenu::update(float deltaTime)
{

}

bool GameMenu::init()
{
	const auto winSize = cocos2d::Director::getInstance()->getWinSize();

	// Setting our background
	// if resource is situated in Resource - U don't have to write whole path to it
	auto background = cocos2d::Sprite::create("Images/loading.png");

	//Creating button sprites for menu
	auto buttons = "Images/button_sprites.png";

	auto newGameNormal = cocos2d::Sprite::create(buttons, cocos2d::Rect(0, 0, 210, 53));
	auto newGameSelected = cocos2d::Sprite::create(buttons, cocos2d::Rect(0, 53, 210, 53));
	auto newGameDisabled = cocos2d::Sprite::create(buttons, cocos2d::Rect(0, 106, 210, 53));
	
	//Creating MenuItem for NewGame button

	MenuItemSprite* newGame = MenuItemSprite::create(newGameNormal, newGameSelected, newGameDisabled, CC_CALLBACK_1(GameMenu::onNewGameClick, this));

	//background->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());

	auto menu = Menu::create(newGame, nullptr);


	this->addChild(background);
	this->addChild(menu);

	return true;
}

void GameMenu::onNewGameClick(cocos2d::Ref* sender)
{
	//auto gameScene = Scene::create();
	////gameScene->addChild(GameLayer::create());

	//Director::getInstance()->replaceScene(gameScene);
}
