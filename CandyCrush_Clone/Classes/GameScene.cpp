/*
 * GameScene.cpp
 *
 *  Created on: 9-jan-2017
 *      Author: ajay
 */

#include "GameScene.h"
#include "GameManager.h"
#include "ViewManager.h"
#include "GameGlobal.h"

GameScene::GameScene() {
	// TODO Auto-generated constructor stub

	hud_layer_ = nullptr;
	touch_started_= false;
	touch_moved_ = false;
	cookie_moved_ = false;
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

	ViewManager::GetInstance()->Init(this);
	GameManager::GetInstance()->Init();
	ViewManager::GetInstance()->CreatePuzzleBoardBoundingBox();

	RegisterTouchListener();

	scheduleUpdate();
	return true;
}


void GameScene::update(float dt) {

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

	if(ViewManager::GetInstance()->ContainsPoint(touch->getStartLocation())) {

		touch_started_ = true;
	}

	return true;
}

void GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {

	if(!touch_started_ || touch_moved_) {
		return;
	}

	short selected_cookie_index;
	short adjacent_cookie_index;

	if(fabsf(touch->getStartLocation().x - touch->getLocation().x) >=MIN_SWIPE_DISTANCE) {


		short row;
		short col;

		GameGlobal::GetInstance()->GetRowColFromPosition(row, col , touch->getStartLocation().x , touch->getStartLocation().y);


		Direction direction;

		if(touch->getStartLocation().x - touch->getLocation().x >0) {

			direction = kLeftDirection;

		} else {

			direction = kRightDirection;
		}

		if(!cookie_moved_ && GameManager::GetInstance()->CheckIfCanMove(row ,col , direction,selected_cookie_index,adjacent_cookie_index)) {

			cookie_moved_ = true;
			GAMELOG("YES CAN BE MOVED");
			ViewManager::GetInstance()->MoveCookies(selected_cookie_index,adjacent_cookie_index);
		}
		touch_moved_ = true;

	}

	if(fabsf(touch->getStartLocation().y - touch->getLocation().y) >=MIN_SWIPE_DISTANCE) {

		short row;
		short col;
		GameGlobal::GetInstance()->GetRowColFromPosition(row, col , touch->getStartLocation().x , touch->getStartLocation().y);

		Direction direction;

		if(touch->getStartLocation().y - touch->getLocation().y >0) {

			direction = kDownDirection;

		} else {

			direction = kUpDirection;
		}
		if(!cookie_moved_ &&  GameManager::GetInstance()->CheckIfCanMove(row ,col,direction,selected_cookie_index,adjacent_cookie_index)) {

			cookie_moved_  = true;
			ViewManager::GetInstance()->MoveCookies(selected_cookie_index,adjacent_cookie_index);
			GAMELOG("YES CAN BE MOVED");
		}

		touch_moved_ = true;
	}
}

void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

	if(!cookie_moved_) {

		ResetEnableTouch();
	}
}


bool GameScene::RemoveChain(std::set<short>& chain_container) {

	return GameManager::GetInstance()->RemoveChain(chain_container);
}

void GameScene::FillUpEmptySpaces() {

	GameManager::GetInstance()->FillUpEmptySpaces();
}

void  GameScene::SwapCookiesValueToEmptySpace() {

	GameManager::GetInstance()->SwapCookiesValueToEmptySpace();
}

bool GameScene::IsValidMove() {

	return GameManager::GetInstance()->IsValidMove();
}

void GameScene::ResetEnableTouch() {

	touch_started_ = false;
	touch_moved_ = false;
	cookie_moved_ = false;
}
