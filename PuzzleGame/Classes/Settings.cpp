/*
 * Settings.cpp
 *
 *  Created on: 26-Dec-2016
 *      Author: ajay
 */

#include "Settings.h"
#include "GameSceneManager.h"
#include "GameManager.h"
#include "ViewManager.h"

Settings::Settings() {
	// TODO Auto-generated constructor stub

	timer_label_ = nullptr;
	scene_type_ = kSceneNone;
	secs_ = 0;
	mins_ = 0;
	is_hint_on_ = false;
	hint_btn_ = nullptr;
}


cocos2d::Layer* Settings::Create() {

	auto layer = Settings::create();
	return layer;
}


bool Settings::init() {

	if(!cocos2d::Layer::init()) {

		return false;
	}

	return true;

}

void Settings::CreateHud(cocos2d::Layer* parent_layer , SceneType scene_type) {


	scene_type_ = scene_type;

	CreateButtons(parent_layer);
}

void Settings::CreateButtons(cocos2d::Layer*parent_layer) {


	if(scene_type_ == kOpeningScene) {

		for(auto child : parent_layer->getChildren()) {

			GAMELOG("Name of the child : %s",child->getName().c_str());
		}

		CreateExitButton(parent_layer);
		CreatePlayButton(parent_layer);

	} else if(scene_type_ == kGameWorldScene) {

		CreateHintButton(parent_layer);
	}
}

void Settings::CreatePlayButton(cocos2d::Layer* parent_layer) {

	auto btn = ((cocos2d::extension::ControlButton *) (parent_layer->getChildByName("play")));
	parent_layer->removeChildByName("play");
	addChild(btn);

	btn->addTargetWithActionForControlEvents(this, cccontrol_selector(Settings::MenuButtonCallBack), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);

}

void Settings::CreateExitButton(cocos2d::Layer* parent_layer) {

	auto exit_btn = (cocos2d::extension::ControlButton *)parent_layer->getChildByName("exit");
	parent_layer->removeChildByName("exit");
	addChild(exit_btn);


	auto ver_btn = parent_layer->getChildByName("btn_cap_down");
	parent_layer->removeChildByName("btn_cap_down");
	exit_btn->addChild(ver_btn);

	exit_btn->setPositionY(cocos2d::Director::getInstance()->getWinSize().height - exit_btn->getContentSize().height/2);
	ver_btn->setPositionY(- ver_btn->getContentSize().height/2);
	ver_btn->setPositionX(ver_btn->getContentSize().width/2);

	exit_btn->addTargetWithActionForControlEvents(this, cccontrol_selector(Settings::ExitButtonCallBack), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);

}


void Settings::CreateResumeButtons(cocos2d::Layer* parent_layer) {


	auto resume_btn = parent_layer->getChildByName("resume_left");
	parent_layer->removeChildByName("resume_left");
	addChild(resume_btn);


	auto ver_btn = parent_layer->getChildByName("btn_cap_left");
	parent_layer->removeChildByName("btn_cap_left");
	resume_btn->addChild(ver_btn);

	resume_btn->setPositionX(cocos2d::Director::getInstance()->getWinSize().width - resume_btn->getContentSize().width/2);
	ver_btn->setPositionX(- ver_btn->getContentSize().width/2);
	ver_btn->setPositionY(ver_btn->getContentSize().height/2);

}


void Settings::MenuButtonCallBack(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType rEvent) {

    GameSceneManager::GetInstance()->GoToGameScene();
}


void Settings::CreateHintButton(cocos2d::Layer* parent_layer) {

	auto backgroundButton =	cocos2d::ui::Scale9Sprite::createWithSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("btn_hint_n"));
	auto titleButton = cocos2d::Sprite::createWithSpriteFrameName("btn_hint_n");
	titleButton->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
	titleButton->setPosition(cocos2d::Vec2(backgroundButton->getContentSize().width/2,backgroundButton->getContentSize().height/2));

	backgroundButton->addChild(titleButton);

	auto backgroundButtonSelected = cocos2d::ui::Scale9Sprite::createWithSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("btn_hint_h"));
	auto titleButton1 = cocos2d::Sprite::createWithSpriteFrameName("btn_hint_h");
	titleButton1->setAnchorPoint(cocos2d::Vec2(0.5,0.5));

	titleButton1->setPosition(cocos2d::Vec2(backgroundButtonSelected->getContentSize().width/2,backgroundButtonSelected->getContentSize().height/2));
	backgroundButtonSelected->addChild(titleButton1);

	hint_btn_ = cocos2d::extension::ControlButton::create( backgroundButton);
	hint_btn_->setBackgroundSpriteForState(backgroundButtonSelected,cocos2d::extension::Control::State::HIGH_LIGHTED);
	hint_btn_->setPosition(ViewManager::GetInstance()->get_hint_btn_pos());//(cocos2d::Vec2(x,y)));
	hint_btn_->addTargetWithActionForControlEvents(this, cccontrol_selector(Settings::HintButtonCallBack), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);

	hint_btn_->setName("hint");

	hint_btn_->setZoomOnTouchDown(false);
	parent_layer->addChild(hint_btn_);//3
}

void Settings::ExitButtonCallBack(cocos2d::Ref* pSender, cocos2d::extension::Control::EventType rEvent) {

    cocos2d::Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif

}


void Settings::HintButtonCallBack(cocos2d::Ref* pSender, cocos2d::extension::Control::EventType rEvent) {

	if(is_hint_on_) {

		return;
	}

	hint_btn_->setEnabled(false);
	is_hint_on_ = true;
	cocos2d::log("Hint pressed");

	auto hintlayer = cocos2d::LayerColor::create(cocos2d::Color4B::BLACK);
	hintlayer->setOpacity(10);

	std::string filename = cocos2d::StringUtils::format("level_0%d",GameManager::GetInstance()->get_current_level_no());
	auto ref_image  = cocos2d::Sprite::createWithSpriteFrameName(filename);
	ref_image->setAnchorPoint(cocos2d::Vec2(cocos2d::Vec2::ANCHOR_MIDDLE));
	ref_image->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getWinSize().width/2 , cocos2d::Director::getInstance()->getWinSize().height/2));
	ref_image->setScale(.7);
	ref_image->setOpacity(10);

	hintlayer->addChild(ref_image);

	addChild(hintlayer);

	auto fadein  = cocos2d::FadeTo::create(.3, 200);
	auto delay = cocos2d::DelayTime::create(2);
	auto fadeout = cocos2d::FadeTo::create(.3, 0);
	auto callfun = cocos2d::CallFuncN::create(CC_CALLBACK_1(Settings::HintFadeOutCallBack, this));
	auto removeself = cocos2d::RemoveSelf::create();
	auto seq = cocos2d::Sequence::create(fadein , delay , fadeout , callfun , removeself,nullptr);
	auto seq1 = cocos2d::Sequence::create(fadein->clone() , delay->clone() , fadeout->clone(),nullptr);

	hintlayer->runAction(seq);
	ref_image->runAction(seq1);

}


void Settings::HintFadeOutCallBack(cocos2d::Node* sender) {

	is_hint_on_ = false;
	hint_btn_->setEnabled(true);
}




void Settings::CreateTimerLabel(cocos2d::Layer* parent_layer) {

	timer_label_ = (cocos2d::Label*)parent_layer->getChildByName("timer");
	parent_layer->removeChildByName("timer");

	addChild(timer_label_);
}


void Settings::SetTimer() {

	auto delay = cocos2d::DelayTime::create(1);
	auto callfunc = cocos2d::CallFuncN::create(CC_CALLBACK_1(Settings::UpdateTimer , this));

	auto seq = cocos2d::Sequence::createWithTwoActions(delay , callfunc);
	auto repeat = cocos2d::RepeatForever::create(seq);
	timer_label_->runAction(repeat);
}

void Settings::UpdateTimer(cocos2d::Node* sender) {

	secs_++;

	std::string secs_str;
	std::string mins_str;

	if(secs_>=60) {

		secs_ = 0;
		mins_++;
	}

	if(secs_>=10) {

		secs_str = (cocos2d::StringUtils::format("%d",secs_));
	} else {

		secs_str = (cocos2d::StringUtils::format("0%d",secs_));
	}

	if(mins_>=10) {

		mins_str = (cocos2d::StringUtils::format("%d",mins_));
	} else {

		mins_str = (cocos2d::StringUtils::format("0%d",mins_));
	}


	timer_label_->setString(cocos2d::StringUtils::format("%s : %s",mins_str.c_str(),secs_str.c_str()));
}

Settings::~Settings() {
// TODO Auto-generated destructor stub

	GAMELOG("Settings Destructir called");
}

