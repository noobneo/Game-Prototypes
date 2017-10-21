/*
 * LayoutHandler.cpp
 *
 *  Created on: 26-Dec-2016
 *      Author: ajay
 */

#include "LayoutHandler.h"
#include "GameGlobal.h"
#include "ui/UIScale9Sprite.h"
#include "external/json/document.h"
#include "ViewManager.h"


LayoutHandler* LayoutHandler::layout_handler_ref_ = nullptr;

LayoutHandler::LayoutHandler() {
	// TODO Auto-generated constructor stub
	x_scale_factor_ = 0.0f;
	y_scale_factor_ = 0.0f;
	button_ = nullptr;
	is_parent_selected_ = false;
	btn_layer_ = 0;

}

LayoutHandler::~LayoutHandler() {
	// TODO Auto-generated destructor stub
}

LayoutHandler* LayoutHandler::GetInstance() {

	if(!layout_handler_ref_) {

		layout_handler_ref_ = new LayoutHandler();
	}

	return layout_handler_ref_;
}

void LayoutHandler::ParseAndAddLayout(std::string layout_name , cocos2d::Node* layer , bool apply_scale , bool converto_node_space) {

	const std::string filestring  = cocos2d::FileUtils::getInstance()->getStringFromFile(layout_name);

	GAMELOG("This is the file string %s" ,filestring.c_str());

	rapidjson::Document document;

	document.Parse(filestring.c_str());

	GAMELOG("This is the size of the document %d" , document.Size());

	std::string button_name = "";
	btn_name_ = "";

	x_scale_factor_ = .67f;//1280.0f/1920.0f;
	y_scale_factor_ = 800.0f/1080.0f;

	for(int i = 0 ; i <document.Size() ; i++) {

		std::string name;
		float x;
		float y;
		float width;
		float height;
		int layer_no;
		float is_layout = false;
		float is_sprite = false;


		cocos2d::Vec2 node_pos;

		if(document[i].HasMember("name")) {

			name = document[i]["name"].GetString();

			is_sprite = true;
		}

		if(document[i].HasMember("x")) {

			x = document[i]["x"].GetDouble();

			if(apply_scale) {

				x *= x_scale_factor_;
			}

			if(converto_node_space) {
				node_pos.x = x;
			}

		}

		if(document[i].HasMember("y")) {

			y = document[i]["y"].GetDouble();

			if(apply_scale) {

				y *= x_scale_factor_;
			}

			if(converto_node_space) {
				node_pos.y = y;
			}
		}

		if(document[i].HasMember("layer")) {

			layer_no = document[i]["layer"].GetDouble();
		}

		if(document[i].HasMember("width")) {

			width = document[i]["width"].GetDouble();
			if(apply_scale) {

				width *= x_scale_factor_;
			}
		}

		if(document[i].HasMember("height")) {

			height = document[i]["height"].GetDouble();
			if(apply_scale) {

				height *= x_scale_factor_;
			}
		}


		if(converto_node_space) {

			node_pos = layer->convertToWorldSpace((node_pos));

			x = node_pos.x;
			y = node_pos.y;
		}


		GAMELOG("This the name of the Member : %s , has x : %2.f , y : %.2f on layer : %d" , name.c_str(),x,y,layer_no);


		if(strcmp("frame_gameplay" , name.c_str())==0) {

			cocos2d::Vec2 pos(x,y);
			ViewManager::GetInstance()->set_puzzle_frame_position(pos);
		} else if(strcmp("btn_hint_n" , name.c_str())==0) {

			cocos2d::Vec2 pos(x,y);
			ViewManager::GetInstance()->set_hint_btn_pos(pos);
		}

		if(strstr(name.c_str() , "spr_")) {

			std::size_t pos = name.find("spr_");
			name = name.substr(pos+4);


			if(strstr(name.c_str() ,"ic_")) {

				std::size_t pos = name.find("ic_");
				std::string btn_name = name.substr(pos+3);
				GAMELOG("Changing the button name: %s" , btn_name.c_str());

//
				if(converto_node_space) {
					CreateButton(name , x , y , layer_no , layer->getParent() , button_name);
				} else {

					CreateButton(name , x , y , layer_no , layer,button_name);
				}


			}

			else if(strstr(name.c_str() ,"resume_")) {


				if(converto_node_space) {
					CreateButton(name , x , y , layer_no , layer->getParent() , button_name);
				} else {

					CreateButton(name , x , y , layer_no , layer,button_name);
				}

			}

			else {

				if(converto_node_space) {
					CreateSprite(name , x , y , layer_no , layer->getParent());
				} else {

					CreateSprite(name , x , y , layer_no , layer);
				}
			}
		}

		else if(strstr(name.c_str() ,"ic_")) {

			CreateSprite(name , x , y , layer_no , button_);
		}

		else if(strstr(name.c_str() , "btn")) {


			if(strstr(name.c_str(),"cap")) {

				if(converto_node_space) {
					CreateSprite(name , x , y , layer_no , layer->getParent() );
				} else {

					CreateSprite(name , x , y , layer_no , layer );
				}
			} else {

				btn_name_  = name;
				btn_pos_.x = x;
				btn_pos_.y = y;
				btn_layer_ = layer_no;
			}

		}

		else if(strstr(name.c_str() , "lyt_")) {

			std::size_t pos = name.find("lyt_");
			std::string layout_file = name.substr(pos+4);
			std::string layout = cocos2d::StringUtils::format("%s.json",layout_file.c_str());

			cocos2d::Node* layoutnode = cocos2d::Node::create();//(cocos2d::Color4B::BLACK);//(c);
			layoutnode->setName(name);
			layoutnode->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
			layoutnode->setContentSize(cocos2d::Size(width,height));
			layoutnode->setPosition(((cocos2d::Vec2(x,y))));
			layoutnode->setIgnoreAnchorPointForPosition(false);
			layer->addChild(layoutnode);

			is_parent_selected_ = false;
			ParseAndAddLayout(layout , layoutnode , true , true);
		}

		else if(strstr(name.c_str() , "frame_")) {

//			CreateFrames

			std::size_t pos = name.find("frame_");
			name = name.substr(pos+6);
			GAMELOG("this is the fram name %s",name.c_str());
			cocos2d::Node* layoutnode = cocos2d::Node::create();//(c);
			layoutnode->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
			layoutnode->setContentSize(cocos2d::Size(width,height));
			layoutnode->setPosition(((cocos2d::Vec2(x,y))));
			layoutnode->setIgnoreAnchorPointForPosition(true);
			layoutnode->setName(name);

			layer->addChild(layoutnode);

			if(converto_node_space) {
				layer->getParent()->addChild(layoutnode);
			} else {

				layer->addChild(layoutnode);
			}


		}

		else if(strstr(name.c_str() , "node_")) {

//			CreateNode

			std::size_t pos = name.find("node_");
			name = name.substr(pos+5);
			cocos2d::Node* layoutnode = cocos2d::Node::create();//(c);
			layoutnode->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
			layoutnode->setContentSize(cocos2d::Size(width,height));
			layoutnode->setPosition(((cocos2d::Vec2(x,y))));
			layoutnode->setName(name);

			cocos2d::LayerColor* bglayer = cocos2d::LayerColor::create(cocos2d::Color4B::RED);//(c);
			bglayer->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
			bglayer->setContentSize(cocos2d::Size(width,height));
			layoutnode->addChild(bglayer);

			layer->addChild(layoutnode);
		}

		else if(strstr(name.c_str() , "lbl_")) {

//			CreateLabel
			std::size_t pos = name.find("lbl_");
			name = name.substr(pos+4);

			if(converto_node_space) {
				CreateLabel(name,x,y,layer_no , layer->getParent());
			} else {

				CreateLabel(name,x,y,layer_no , layer);
			}

		}

		else {

			std::size_t pos = name.find("spr_");
			name = name.substr(pos+4);


			if(converto_node_space) {
				CreateSprite(name , x , y , layer_no , layer->getParent());
			} else {

				CreateSprite(name , x , y , layer_no , layer);
			}


		}


	}

}

void LayoutHandler::CreateSprite(std::string name , float x , float y , int layer_no , cocos2d::Node* layer) {

	auto sprite = cocos2d::Sprite::createWithSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	GAMELOG("CreateSprite 0...%s",name.c_str());

	cocos2d::Vec2 pos = layer->convertToNodeSpace(cocos2d::Vec2(x,y));

	if(!sprite) {

		//sprite frame not found look image by that name

		GAMELOG("CreateSprite 1...%s",name.c_str());
		std::string filename = cocos2d::StringUtils::format("%s.png" , name.c_str());

		sprite = cocos2d::Sprite::create(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename));
	}

	GAMELOG("CreateSprite 2...%s",name.c_str());
	if(!sprite) {

		sprite = cocos2d::Sprite::create();

		auto spr= cocos2d::LayerGradient::create(cocos2d::Color4B::RED , cocos2d::Color4B::RED);
		spr->setOpacity(10);
		sprite->addChild(spr);
	}


	GAMELOG("CreateSprite 3...%s",name.c_str());
	sprite->setAnchorPoint(cocos2d::Vec2(.5f,.5f));

	if(strstr(name.c_str() , "bg_")) {

		sprite->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getWinSize().width/2 , cocos2d::Director::getInstance()->getWinSize().height/2));
	} else{

		sprite->setPosition(pos);//(cocos2d::Vec2(x,y)));
	}

	sprite->setName(name);
	GAMELOG("CreateSprite 4...%s",name.c_str());
	layer->addChild(sprite);
	GAMELOG("CreateSprite 5...%s",name.c_str());
}

void LayoutHandler::CreateButton(std::string name , float x , float y , int layer_no , cocos2d::Node* layer , std::string button_name) {


	GAMELOG("this is the button name: %s" , btn_name_.c_str());

	GAMELOG("WHILE CREATING THE BUTTON this is the Name of sprite : %s",name.c_str());
	auto backgroundButton =	cocos2d::ui::Scale9Sprite::createWithSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(btn_name_));
	auto titleButton = cocos2d::Sprite::createWithSpriteFrameName(name);
	titleButton->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
	titleButton->setPosition(cocos2d::Vec2(backgroundButton->getContentSize().width/2,backgroundButton->getContentSize().height/2));

	if(strcmp(name.c_str()  ,"play")==0) {

		titleButton->setColor(cocos2d::Color3B::BLACK);
	} else {

		titleButton->setColor(cocos2d::Color3B::WHITE);
	}

	backgroundButton->addChild(titleButton);

	auto backgroundButtonSelected = cocos2d::ui::Scale9Sprite::createWithSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(btn_name_));
	auto titleButton1 = cocos2d::Sprite::createWithSpriteFrameName(name);
	titleButton1->setAnchorPoint(cocos2d::Vec2(0.5,0.5));

	if(strcmp(name.c_str()  ,"play")==0) {

		titleButton1->setColor(cocos2d::Color3B::WHITE);
	} else {

		titleButton1->setColor(cocos2d::Color3B::BLACK);
	}
	titleButton1->setPosition(cocos2d::Vec2(backgroundButtonSelected->getContentSize().width/2,backgroundButtonSelected->getContentSize().height/2));
	backgroundButtonSelected->addChild(titleButton1);

	button_ = cocos2d::extension::ControlButton::create( backgroundButton);
	button_->setBackgroundSpriteForState(backgroundButtonSelected,cocos2d::extension::Control::State::HIGH_LIGHTED);
	button_->setPosition(btn_pos_);//(cocos2d::Vec2(x,y)));

	if(strstr(name.c_str() , "ic_")) {

		std::size_t pos = name.find("ic_");
		name = name.substr(pos+3);
	}


	button_->setName(name);

	button_->setZoomOnTouchDown(false);
	layer->addChild(button_,btn_layer_);//3
}


void LayoutHandler::CreateLabel(std::string name , float x , float y , int layer_no , cocos2d::Node* layer) {


	GAMELOG("Creating this label %s",name.c_str());

	auto label = cocos2d::Label::createWithBMFont("timer.fnt" , "00 : 00" , cocos2d::TextHAlignment::CENTER , 400 , cocos2d::Vec2::ZERO);

	label->setScale(x_scale_factor_);
	label->setName(name);
	label->setPosition((cocos2d::Vec2(x , y)));
	layer->addChild(label);
}

