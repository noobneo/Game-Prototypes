/*
 * OpeningScene.cpp
 *
 *  Created on: 26-Dec-2016
 *      Author: ajay
 */

#include "OpeningScene.h"
#include "LayoutHandler.h"
#include "GameGlobal.h"
#include "GameSceneManager.h"

OpeningScene::OpeningScene() {
	// TODO Auto-generated constructor stub

	hud_layer_ = nullptr;
	settings_layer_ = nullptr;
}

OpeningScene::~OpeningScene() {
	// TODO Auto-generated destructor stub
}


cocos2d::Scene* OpeningScene::Create() {

	auto scene = OpeningScene::create();
	return scene;
}

bool OpeningScene::init() {

	if(!cocos2d::Scene::init()) {

		return false;
	}

	hud_layer_ = cocos2d::Layer::create();
	addChild(hud_layer_);


	LayoutHandler::GetInstance()->ParseAndAddLayout( "opening.json", hud_layer_ , true);


	settings_layer_ = Settings::create();
	addChild(settings_layer_);

	settings_layer_->CreateHud(hud_layer_ , kOpeningScene);


	GAMELOG("OpeningScene Init Done!");


	return true;
}
