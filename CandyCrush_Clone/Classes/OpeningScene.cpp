/*
 * OpeningScene.cpp
 *
 *  Created on: 9-jan-2017
 *      Author: ajay
 */

#include "OpeningScene.h"
#include "GameSceneManager.h"
#include "GameGlobal.h"

OpeningScene::OpeningScene() {
	// TODO Auto-generated constructor stub

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


    auto closeItem = cocos2d::MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(OpeningScene::ExitButtonCallBack, this));


    auto label = cocos2d::Label::createWithTTF("Start Game", "fonts/Marker Felt.ttf", 24);

    auto menulabel = cocos2d::MenuItemLabel::create(label , CC_CALLBACK_1(OpeningScene::PlayButtonCallBack , this));


    auto menu = cocos2d::Menu::create(closeItem,menulabel, nullptr);
    menu->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getWinSize().width/2 , cocos2d::Director::getInstance()->getWinSize().height/2));
    menu->alignItemsVerticallyWithPadding(40);
    this->addChild(menu, 1);

	return true;
}

void OpeningScene::PlayButtonCallBack(cocos2d::Ref* sender) {

	GAMELOG("Going to GameScene");

	GameSceneManager::GetInstance()->GoToGameScene();
}

void OpeningScene::ExitButtonCallBack(cocos2d::Ref* sender) {

	GAMELOG("Exiting Game");

    //Close the cocos2d-x game scene and quit the application
    cocos2d::Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

