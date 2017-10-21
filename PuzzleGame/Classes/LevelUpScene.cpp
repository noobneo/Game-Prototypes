/*
 * LevelUpScene.cpp
 *
 *  Created on: 28-Dec-2016
 *      Author: ajay
 */

#include "LevelUpScene.h"
#include "GameManager.h"
#include "GameSceneManager.h"

LevelUpScene::LevelUpScene() {
	// TODO Auto-generated constructor stub

}

cocos2d::Scene* LevelUpScene::Create() {

	auto scene = LevelUpScene::create();
	return scene;
}

bool LevelUpScene::init() {

	if(!cocos2d::Scene::init()) {

		return false;
	}


	auto label = cocos2d::Label::createWithTTF("Level Up", "fonts/Marker Felt.ttf", 24);
	label->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getWinSize().width/2 , cocos2d::Director::getInstance()->getWinSize().height/2));
	addChild(label, 1);

	int level = GameManager::GetInstance()->get_current_level_no();
	level++;
	level = level >8 ? 1 : level;

	GameManager::GetInstance()->set_current_level_no(level);

	auto delaytime = cocos2d::DelayTime::create(1);
	auto callfun = cocos2d::CallFuncN::create(CC_CALLBACK_1(LevelUpScene::ChangeSceneToGame, this));
	auto seq = cocos2d::Sequence::create(delaytime,callfun,nullptr);
	runAction(seq);

	return true;
}

void LevelUpScene::ChangeSceneToGame(cocos2d::Node* sender) {

	GameSceneManager::GetInstance()->GoToGameScene();
}

LevelUpScene::~LevelUpScene() {
	// TODO Auto-generated destructor stub
}

