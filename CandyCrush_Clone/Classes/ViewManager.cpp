/*
 * ViewManager.cpp
 *
 *  Created on: 9-jan-2017
 *      Author: ajay
 */

#include "ViewManager.h"
#include "GameManager.h"
#include "GameSceneManager.h"
#include "GameGlobal.h"
#include "GameScene.h"

ViewManager* ViewManager::view_manager_ref_ = nullptr;

ViewManager::ViewManager() {
	// TODO Auto-generated constructor stub


	anim_delay_ = 0.0f;

	min_x_ = START_X;
	max_x_ = START_X;
	min_y_ = START_Y;
	max_y_ = START_Y;

	puzzle_board_bounding_box_ = cocos2d::Rect::ZERO;

	game_scene_ = nullptr;
	hud_layer_ = nullptr;
	puzzle_layer_ = nullptr;
	tile_layer_ = nullptr;
	animation_node_ = nullptr;
	puzzle_clipping_node_=  nullptr;
}

ViewManager* ViewManager::GetInstance() {

	if(!view_manager_ref_) {

		view_manager_ref_ = new ViewManager();
	}

	return view_manager_ref_;
}


void ViewManager::Init(cocos2d::Scene* game_scene) {

	game_scene_ = game_scene;


	hud_layer_ = cocos2d::Layer::create();
	game_scene_->addChild(hud_layer_);
//
	tile_layer_ = cocos2d::Layer::create();
	game_scene_->addChild(tile_layer_);

	puzzle_clipping_node_ = cocos2d::ClippingRectangleNode::create();
	game_scene_->addChild(puzzle_clipping_node_);

	puzzle_layer_ = cocos2d::Layer::create();
	puzzle_clipping_node_->addChild(puzzle_layer_);

	animation_node_ = cocos2d::Node::create();
	puzzle_layer_->addChild(animation_node_);


	CreateBackGround();


    auto label = cocos2d::Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 24);
    label->setColor(cocos2d::Color3B::BLACK);

    auto menulabel = cocos2d::MenuItemLabel::create(label , CC_CALLBACK_1(ViewManager::MenuButtonCallBack , this));


    auto menu = cocos2d::Menu::create(menulabel, nullptr);
    menu->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getWinSize().width - 100 , cocos2d::Director::getInstance()->getWinSize().height - 100));
    hud_layer_->addChild(menu);

}

void ViewManager::CreateBackGround() {

	auto bg = cocos2d::Sprite::create("Images/Background@2x.png");
	bg->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getWinSize().width/2 , cocos2d::Director::getInstance()->getWinSize().height/2));

	hud_layer_->addChild(bg);
}



void ViewManager::CreateCookie(std::string normal_sprite_name , short row , short col) {

	auto cookie = CreateCookieSprite(normal_sprite_name , row , col);
	float x = START_X + (col*WIDTH);
	float y = START_Y - (row*HEIGHT);
	cookie->setPosition(cocos2d::Vec2(x,y));

	puzzle_layer_->addChild(cookie);

	auto tile = cocos2d::Sprite::create("Sprites.atlas/Tile@2x.png");
	tile->setPosition(cocos2d::Vec2(x,y));
	tile_layer_->addChild(tile);

	float minx = x - WIDTH/2;
	float maxx = x + WIDTH/2;
	float miny = y - HEIGHT/2;
	float maxy = y + HEIGHT/2;

	GameGlobal::GetInstance()->SwapifMaximum(maxx , max_x_);
	GameGlobal::GetInstance()->SwapifMaximum(maxy , max_y_);
	GameGlobal::GetInstance()->SwapifMinimum(minx , min_x_);
	GameGlobal::GetInstance()->SwapifMinimum(miny , min_y_);
}


void ViewManager::CreateCookieAndAnimateToPosition(std::string normal_sprite_name , short row , short col , bool is_last) {

	auto cookie = CreateCookieSprite(normal_sprite_name , row , col);
	float x = START_X + (col*WIDTH);
	float y = START_Y - (row*HEIGHT);
	cookie->setPosition(cocos2d::Vec2(x , puzzle_clipping_node_->getBoundingBox().getMaxY()+HEIGHT));


	float dt = .3f;
	auto moveto = cocos2d::MoveTo::create(dt, cocos2d::Vec2(x,y));
	auto ease = cocos2d::EaseBounceOut::create(moveto);
	auto delay = cocos2d::DelayTime::create(anim_delay_);
	cocos2d::Sequence *seq = nullptr;

	if(is_last) {

		auto callfunc = cocos2d::CallFuncN::create(CC_CALLBACK_1(ViewManager::CookieFillAnimationCallBack ,this));
		seq= cocos2d::Sequence::create(delay , ease , callfunc ,nullptr);
	} else {

		seq= cocos2d::Sequence::create(delay , ease , nullptr);
	}

	cookie->runAction(ease);
	anim_delay_+= 0.02f;

	puzzle_layer_->addChild(cookie);
}

cocos2d::Sprite* ViewManager::CreateCookieSprite(std::string normal_sprite_name , short row , short col) {

	auto filename = cocos2d::StringUtils::format("Sprites.atlas/%s",normal_sprite_name.c_str());
	auto cookie = cocos2d::Sprite::create(filename);

	short index  = GameGlobal::GetInstance()->GetIndexFromRowCol(col,row);
	cookies_sprite_container_.insert (std::pair<short , cocos2d::Sprite*>(index , cookie));

	return cookie;
}


void ViewManager::MoveCookies(short selected_cookie_index,short adjacent_cookie_index ) {

	auto selected_cookie = cookies_sprite_container_.at(selected_cookie_index);
	auto adjacent_cookie = cookies_sprite_container_.at(adjacent_cookie_index);

	float dt = .3f;
	float delay = .4f;
	/*
	 * action for selected cookie
	 */
	auto moveto1 = cocos2d::MoveTo::create(dt, adjacent_cookie->getPosition());
	auto callfunc = cocos2d::CallFuncN::create(CC_CALLBACK_1(ViewManager::CookieMoveCallBack ,this , selected_cookie ,selected_cookie_index, adjacent_cookie ,adjacent_cookie_index));
	auto seq = cocos2d::Sequence::create(cocos2d::DelayTime::create(delay) , callfunc , nullptr);

	/*
	 * action for adjacent cookie
	 */
	auto moveto2 = cocos2d::MoveTo::create(dt, selected_cookie->getPosition());
//	auto seq1 = cocos2d::Sequence::create(moveto2 , nullptr);

	selected_cookie->runAction(moveto1);
	adjacent_cookie->runAction(moveto2);
	animation_node_->runAction(seq);
}


void ViewManager::CookieFillAnimationCallBack(cocos2d::Node* sender ) {

	RemoveChain();
}

void ViewManager::CookieMoveCallBack(cocos2d::Node* sender , cocos2d::Sprite* selected_cookie , short selected_cookie_index , cocos2d::Sprite* adjacent_cookie , short adjacent_cookie_index) {

	if(((GameScene*)game_scene_)->IsValidMove()) {

		//((GameScene*)game_scene_)->RemoveChain();

		/*
		 * swap the sprite index in the container
		 */
		cookies_sprite_container_.at(selected_cookie_index) = adjacent_cookie;
		cookies_sprite_container_.at(adjacent_cookie_index) = selected_cookie;

		RemoveChain();
		/*
		 * do this after animation
		 */
		((GameScene*)game_scene_)->ResetEnableTouch();

	} else {


		float dt = .3f;
		/*
		 * action for selected cookie
		 */
		auto moveto1 = cocos2d::MoveTo::create(dt, adjacent_cookie->getPosition());
		auto callfunc = cocos2d::CallFuncN::create(CC_CALLBACK_1(ViewManager::ResetEnableTouch ,this));
		auto seq = cocos2d::Sequence::create(moveto1 , callfunc , nullptr);

		/*
		 * action for adjacent cookie
		 */
		auto moveto2 = cocos2d::MoveTo::create(dt, selected_cookie->getPosition());
		auto seq1 = cocos2d::Sequence::create(moveto2 , callfunc , nullptr);

		selected_cookie->runAction(seq);
		adjacent_cookie->runAction(seq1);

	}
}

void ViewManager::RemoveChain() {

	std::set<short> chain_container;

	if(((GameScene*)game_scene_)->RemoveChain(chain_container)) {

		for(auto index:chain_container) {
			auto cookie = cookies_sprite_container_.at(index);
			cookie->removeFromParentAndCleanup(true);
			cookies_sprite_container_.erase(index);

			GAMELOG("This is the key removed from ViewManager:%d",index);
		}
			((GameScene*)game_scene_)->SwapCookiesValueToEmptySpace();
			chain_container.clear();
			anim_delay_ = 0.0f;
			FillUpEmptySpaces();
	}
}


void ViewManager::FillUpEmptySpaces() {

	((GameScene*)game_scene_)->FillUpEmptySpaces();
	RemoveChain();
}


void ViewManager::MoveCookieToEmptySpace(short old_row , short old_col , short new_row , short new_col) {


	short old_index = GameGlobal::GetInstance()->GetIndexFromRowCol(old_col,old_row);
	short new_index = GameGlobal::GetInstance()->GetIndexFromRowCol(new_col,new_row);

	auto cookie = cookies_sprite_container_.at(old_index);

	/*
	 * swap cookies mapping w.r.t to index in the map
	 * used [] because already deleted that entry
	 * so [] creates new if not found
	 */

	cookies_sprite_container_[new_index] = cookie;
	cookies_sprite_container_.erase(old_index);

	float x = START_X + (new_col*WIDTH);
	float y = START_Y - (new_row*HEIGHT);

	float dt = .3f;
	auto moveto = cocos2d::MoveTo::create(dt, cocos2d::Vec2(x,y));
	auto ease = cocos2d::EaseBounceOut::create(moveto);
	auto delay = cocos2d::DelayTime::create(anim_delay_);
	auto seq = cocos2d::Sequence::create(delay , ease , nullptr);
	cookie->runAction(ease);
	anim_delay_+= 0.02f;
}


void ViewManager::ResetEnableTouch(cocos2d::Node* sender) {


	((GameScene*)game_scene_)->ResetEnableTouch();
}


void ViewManager::CreatePuzzleBoardBoundingBox() {

	puzzle_board_bounding_box_.origin.x = min_x_;
	puzzle_board_bounding_box_.origin.y = min_y_;

	float height =  max_y_ - min_y_;
	float width = max_x_ - min_x_;

	puzzle_board_bounding_box_.size.width =  width;
	puzzle_board_bounding_box_.size.height = height;


	puzzle_clipping_node_->setClippingRegion(cocos2d::Rect(min_x_ , min_y_ , width , height));
	puzzle_clipping_node_->setAnchorPoint(cocos2d::Vec2(cocos2d::Vec2::ANCHOR_MIDDLE));
}

bool ViewManager::ContainsPoint(cocos2d::Vec2 position) {

	if(puzzle_board_bounding_box_.containsPoint(position)) {

		return true;
	}

	return false;
}

void ViewManager::MenuButtonCallBack(cocos2d::Ref* sender) {

	GAMELOG("Going to GameScene");

	Clear();
	GameSceneManager::GetInstance()->GoToOpeningScene();
}

void ViewManager::Clear(){

	GameManager::GetInstance()->Clear();

	cookies_sprite_container_.clear();

	hud_layer_->removeAllChildrenWithCleanup(true);
	puzzle_layer_->removeAllChildrenWithCleanup(true);
	tile_layer_->removeAllChildrenWithCleanup(true);

	min_x_ = START_X;
	max_x_ = START_X;
	min_y_ = START_Y;
	max_y_ = START_Y;

	puzzle_board_bounding_box_ = cocos2d::Rect::ZERO;

	hud_layer_ = nullptr;
	puzzle_layer_ = nullptr;
	tile_layer_ = nullptr;
	game_scene_ = nullptr;


	CC_SAFE_DELETE(view_manager_ref_);
}

ViewManager::~ViewManager() {
	// TODO Auto-generated destructor stub

	GAMELOG("Destructor ViewManager");
}

