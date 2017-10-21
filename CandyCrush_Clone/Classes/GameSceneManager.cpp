/*
 * GameSceneHandler.cpp
 *
 *  Created on: 9-jan-2017
 *      Author: ajay
 */

#include "GameSceneManager.h"
#include "OpeningScene.h"
#include "GameScene.h"

GameSceneManager* GameSceneManager::game_scene_manager_ref_ = nullptr;
GameSceneManager::GameSceneManager() {
	// TODO Auto-generated constructor stub

	scene_transition_time_ = .5f;
}

GameSceneManager::~GameSceneManager() {
	// TODO Auto-generated destructor stub
}

GameSceneManager* GameSceneManager::GetInstance() {

	if(!game_scene_manager_ref_) {

		game_scene_manager_ref_ = new GameSceneManager();
	}

	return game_scene_manager_ref_;
}

void GameSceneManager::GoToOpeningScene() {

	auto scene = OpeningScene::Create();
	auto director = cocos2d::Director::getInstance();

	if(director->getRunningScene()) {

		director->replaceScene(cocos2d::TransitionFade::create(scene_transition_time_ , scene , cocos2d::Color3B::BLACK));
	} else {

		director->runWithScene(scene);
	}

}

void GameSceneManager::GoToGameScene() {

	auto scene = GameScene::Create();
	auto director = cocos2d::Director::getInstance();

	if(director->getRunningScene()) {

		director->replaceScene(cocos2d::TransitionFade::create(scene_transition_time_ , scene , cocos2d::Color3B::BLACK));
	} else {

		director->runWithScene(scene);
	}


}


