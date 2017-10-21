/*
 * GameScene.cpp
 *
 *  Created on: 26-Dec-2016
 *      Author: ajay
 */

#include "GameScene.h"
#include "LayoutHandler.h"
#include "ViewManager.h"
#include "GameManager.h"

GameScene::GameScene() {
	// TODO Auto-generated constructor stub

	touch_started_= false;
}

GameScene::~GameScene() {
	// TODO Auto-generated destructor stub
}

cocos2d::Scene* GameScene::Create() {

	auto scene = GameScene::create();
	return scene;
}

bool GameScene::init() {

	if(!cocos2d::Scene::init()) {

		return false;
	}


	GameManager::GetInstance()->Init();
	ViewManager::GetInstance()->Init(this);

	ViewManager::GetInstance()->LoadLevel(1);

	RegisterTouchListener();
//	scheduleUpdate();
	return true;
}


void GameScene::RegisterTouchListener() {

	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan= CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}


bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

	if(touch_started_) {
		return false;
	}

	touch_started_ = true;
	ViewManager::GetInstance()->onTouchBegan(touch);


	return true;
}

void GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {

	ViewManager::GetInstance()->onTouchMoved(touch);
}

void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

	touch_started_ = false;
	ViewManager::GetInstance()->onTouchEnded(touch);
}
