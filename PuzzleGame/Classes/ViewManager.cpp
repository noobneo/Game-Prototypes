/*
 * ViewManager.cpp
 *
 *  Created on: 26-Dec-2016
 *      Author: ajay
 */

#include "ViewManager.h"
#include "GameManager.h"
#include "Settings.h"
#include "LayoutHandler.h"
#include "GameSceneManager.h"

ViewManager* ViewManager::view_manager_ref_ = nullptr;

ViewManager::ViewManager() {
	// TODO Auto-generated constructor stub

	game_scene_ = nullptr;
	game_layer_ = nullptr;
	puzzle_board_layer_ = nullptr;
	settings_layer_ = nullptr;
	selected_row_ = -1;
	selected_col_ = -1;
	puzzle_board_layer_ = nullptr;
	puzzle_sprite_width_  = 0.0f;
	puzzle_sprite_height_ = 0.0f;
	piece_height_ = 0.0f;
	piece_width_ = 0.0f;
	offset_ = 0.0f;
	time_delay_ = 0.0;
	is_moving_ = false;
	is_direction_selected_ = false;
	is_horizontal_swipe_ = false;
	is_vertical_swipe_ = false;
	is_animating_  = false;
	memset(directions_ , 0 , sizeof(directions_));
}

ViewManager* ViewManager::GetInstance() {

	if(!view_manager_ref_) {

		view_manager_ref_ = new ViewManager();
	}

	return view_manager_ref_;
}


void ViewManager::Init(cocos2d::Scene* game_scene) {

	game_scene_ = game_scene;

	CreateGameLayer();
	CreatePuzzleLayer();
	CreateSettingsLayer();

}

void ViewManager::LoadLevel(short level_no) {

	CreatePuzzlePieces();
	ShufflePuzzle();
}

void ViewManager::CreateGameLayer() {

	game_layer_ = cocos2d::Layer::create();
	game_layer_->setName("GameLayer");
	game_scene_->addChild(game_layer_);

	LayoutHandler::GetInstance()->ParseAndAddLayout("gameworld.json" , game_layer_ , true);

	auto closeItem = cocos2d::MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(ViewManager::MenuButtonCallBack, this));
	closeItem->setPosition(cocos2d::Vec2(50,750));

	auto menu = cocos2d::Menu::create(closeItem, NULL);
	menu->setPosition(cocos2d::Vec2::ZERO);
	game_layer_->addChild(menu, 999);


}

void ViewManager::CreatePuzzleLayer() {

	puzzle_board_layer_ = cocos2d::ClippingRectangleNode::create();
	game_layer_->addChild(puzzle_board_layer_);

}

void ViewManager::CreateSettingsLayer() {

	settings_layer_ = Settings::create();
	game_scene_->addChild(settings_layer_);
	settings_layer_->CreateHud(game_layer_ , kGameWorldScene);
}

void ViewManager::CreatePuzzlePieces() {



	std::string filename = cocos2d::StringUtils::format("level_0%d",GameManager::GetInstance()->get_current_level_no());
	auto sprite  = cocos2d::Sprite::createWithSpriteFrameName(filename);

	int total_pieces =  ROWS*COLS;

	puzzle_sprite_width_ = sprite->getContentSize().width;
	puzzle_sprite_height_ = sprite->getContentSize().height;


	piece_width_ = puzzle_sprite_width_/COLS;
	piece_height_ = puzzle_sprite_height_/ROWS;


	float start_x = puzzle_frame_position_.x-15;
	float start_y = puzzle_frame_position_.y + piece_height_/6;

	puzzle_board_layer_->setClippingRegion(cocos2d::Rect(0 , 0 , puzzle_sprite_width_ , puzzle_sprite_height_));
	puzzle_board_layer_->setAnchorPoint(cocos2d::Vec2(cocos2d::Vec2::ANCHOR_MIDDLE));
	puzzle_board_layer_->setContentSize(sprite->getContentSize());
	puzzle_board_layer_->setPosition(cocos2d::Vec2(start_x ,start_y));

	GAMELOG("Total pieces : %d , sprite's dimensions width : %.2f , height : %.2f" , total_pieces , puzzle_sprite_width_ , puzzle_sprite_height_);
	GAMELOG("pieces's dimensions width : %.2f , height : %.2f" ,piece_width_ , piece_height_);

	short row_counter =0;
	short col_counter =0;
	short tag = 0;

	for(int i = 0 ; i <total_pieces ; i++) {

		cocos2d::Sprite* spr = cocos2d::Sprite::create();
		spr->initWithTexture(sprite->getTexture() , cocos2d::Rect(piece_width_*col_counter ,piece_height_*row_counter,piece_width_ , piece_height_));
		spr->setPosition(cocos2d::Vec2(piece_width_/2+(piece_width_*col_counter),puzzle_sprite_height_ - piece_height_/2-(piece_height_*row_counter)));

		tag = GameGlobal::GetInstance()->GetIndexFromRowCol(col_counter , row_counter);
		spr->setTag(tag);

		puzzle_board_layer_->addChild(spr);
		puzzle_piece_container_[tag] = spr;

		GameManager::GetInstance()->UpdatePuzzleOriginalBoardState(tag);

		initial_position_.push_back(spr->getPosition());

		col_counter++;

		if(col_counter==COLS) {
			col_counter = 0;
			row_counter++;

		}

		if(row_counter==ROWS) {
			row_counter = 0;
		}
	}

	//one empty at the end
	GameManager::GetInstance()->UpdatePuzzleOriginalBoardState(EMPTY);

}

void ViewManager::ShufflePuzzle() {


	std::srand(time(nullptr));

	std::vector<cocos2d::Node*> temp_container;

	int counter = 0;

	for(auto piece : puzzle_piece_container_) {

			temp_container.push_back(piece.second);
	}


	GameManager::GetInstance()->ShuffleTempContainer(temp_container);

	for(int i = 0 ; i <initial_position_.size() ; i++) {

		temp_container.at(i)->setPosition(initial_position_.at(i));

		GameManager::GetInstance()->UpdatePuzzleCurrentBoardState(temp_container.at(i)->getTag());
	}
	GameManager::GetInstance()->UpdatePuzzleCurrentBoardState(EMPTY);
	temp_container.clear();

}


void ViewManager::onTouchBegan(cocos2d::Touch* touch) {

	if(is_moving_ || is_animating_) {
		return;
	}


	if(settings_layer_->get_is_hint_on()) {
		return;
	}

	if(puzzle_board_layer_->getBoundingBox().containsPoint(touch->getLocation())) {

		GAMELOG("Hello inside onTouchesEnded x: %.2f , y: %.2f" , touch->getLocation().x , touch->getLocation().y);
		PuzzlePieceClicked(touch->getLocation());
	}

}

void ViewManager::onTouchMoved(cocos2d::Touch* touch) {


	if(!is_moving_) {

		return ;

	} else if(is_animating_) {

		return;
	}

	if(!is_direction_selected_) {

		//checks direction when just moved
		CheckSwipeDirection(touch);
		SelectPuzzlePiecesToBeMoved();
		AddWrapAroundImages();
	}

	else {

		//moves the puzzle
		offset_ = 0.0f;
		RepositionPuzzlePieces(false);
		MovePuzzle(touch);
	}
}

void ViewManager::onTouchEnded(cocos2d::Touch* touch) {

	if(!is_animating_) {
		is_animating_ = true;
	}
	RepositionPuzzlePieces(true);

	auto delay = cocos2d::DelayTime::create(.2f);
	auto callfunc = cocos2d::CallFuncN::create(CC_CALLBACK_1	(ViewManager::ResetIsMoving , this));
	game_layer_->runAction(cocos2d::Sequence::create(delay,callfunc,nullptr));

	ResetMoveRelatedInfo();

	if(GameManager::GetInstance()->CheckIfPuzzleSolved()) {
		Clear();

		GameSceneManager::GetInstance()->GoToLevelUpScene();
	}
}

void ViewManager::PuzzlePieceClicked(cocos2d::Vec2 position) {

	GAMELOG("Inside the puzzlePieceClickedMethod");

	for(auto item : puzzle_piece_container_) {

		GAMELOG("Checking if contains point : %d",item.first);
		if(item.second->getBoundingBox().containsPoint(puzzle_board_layer_->convertToNodeSpace(position))) {

			short tag = item.second->getTag();
			GAMELOG("tag-->: %d",tag);
			is_moving_ = true;
			GameManager::GetInstance()->SelectRowColToMove(tag , selected_col_ , selected_row_);
		}
	}
}

void ViewManager::CheckSwipeDirection(cocos2d::Touch* touch) {

	if(fabsf(touch->getStartLocation().x - touch->getLocation().x) >=MIN_X_SWIPE) {

		is_direction_selected_ = true;
		is_horizontal_swipe_ = true;
		GAMELOG("Okay Moving Horizontally");
	}
	else if(fabsf(touch->getStartLocation().y - touch->getLocation().y) >=MIN_Y_SWIPE) {

		is_direction_selected_ = true;
		is_vertical_swipe_ = true;
		GAMELOG("Okay Moving Vertically");
	}
}

void ViewManager::MovePuzzle(cocos2d::Touch* touch) {

	if(is_vertical_swipe_) {

		offset_ = 0.0f;
		offset_ = touch->getLocation().y - touch->getPreviousLocation().y;

		if(offset_ > 0) {

			offset_ = offset_ > MAX_OFFSET ? MAX_OFFSET : offset_;

			directions_[kRightDirection] = 0;
			directions_[kLeftDirection] = 0;
			directions_[kUpDirection] = 1;
			directions_[kDownDirection] = 0;

		} else {

			offset_ = offset_ < -MAX_OFFSET ? -MAX_OFFSET : offset_;

			directions_[kRightDirection] = 0;
			directions_[kLeftDirection] = 0;
			directions_[kUpDirection] = 0;
			directions_[kDownDirection] = 1;
		}

		GAMELOG("Moving with this offset %.2f",offset_);

		MovePuzzleVertically();

	}else if(is_horizontal_swipe_) {

		offset_ = 0.0f;
		offset_ =  touch->getLocation().x - touch->getPreviousLocation().x;

		if(offset_ > 0) {

			offset_ = offset_ > MAX_OFFSET ? MAX_OFFSET : offset_;

			directions_[kRightDirection] = 1;
			directions_[kLeftDirection] = 0;
			directions_[kUpDirection] = 0;
			directions_[kDownDirection] = 0;
		} else {

			offset_ = offset_ < -MAX_OFFSET ? -MAX_OFFSET : offset_;

			directions_[kRightDirection] = 0;
			directions_[kLeftDirection] = 1;
			directions_[kUpDirection] = 0;
			directions_[kDownDirection] = 0;
		}

		GAMELOG("Moving with this offset %.2f",offset_);
		MovePuzzleHorizontally();
	}
}

void ViewManager::MovePuzzleVertically() {

	for(auto puzzle_piece : moving_piece_container_) {

		puzzle_piece->setPositionY(puzzle_piece->getPositionY()+offset_);
	}

	for(auto puzzle_piece_1 : top_wraparound_piece_container_) {

		puzzle_piece_1->setPositionY(puzzle_piece_1->getPositionY()+offset_);
	}

	for(auto puzzle_piece_2 : bottom_wraparound_piece_container_) {

		puzzle_piece_2->setPositionY(puzzle_piece_2->getPositionY()+offset_);
	}


}

void ViewManager::MovePuzzleHorizontally() {

	for(auto puzzle_piece : moving_piece_container_) {

		puzzle_piece->setPositionX(puzzle_piece->getPositionX()+offset_);
	}

	for(auto puzzle_piece_1 : left_wraparound_piece_container_) {

		puzzle_piece_1->setPositionX(puzzle_piece_1->getPositionX()+offset_);
	}

	for(auto puzzle_piece_2 : right_wraparound_piece_container_) {

		puzzle_piece_2->setPositionX(puzzle_piece_2->getPositionX()+offset_);
	}

}

void ViewManager::SelectPuzzlePiecesToBeMoved() {

	if(is_horizontal_swipe_) {
		//select row elements
		for(short i = 0 ; i< COLS ; i++) {

			short indx = GameGlobal::GetInstance()->GetIndexFromRowCol(i , selected_row_);
			int tag = GameManager::GetInstance()->GetCurrentBoardStateAtIndex(indx);
			moving_piece_container_.push_back(puzzle_board_layer_->getChildByTag(tag));
		}

	} else if(is_vertical_swipe_) {
		//select col elements
		for(short i = 0 ; i< ROWS ; i++) {

			short indx = GameGlobal::GetInstance()->GetIndexFromRowCol(selected_col_ , i);
			int tag = GameManager::GetInstance()->GetCurrentBoardStateAtIndex(indx);
			moving_piece_container_.push_back(puzzle_board_layer_->getChildByTag(tag));
		}
	}
}


void ViewManager::AddWrapAroundImages() {


	float bound ;
	float position_offset;


	if(is_horizontal_swipe_) {

		bound = puzzle_sprite_width_;
		position_offset  = piece_width_/2;

		int counter= 0;
		//right side
		for(auto sprite : moving_piece_container_) {

			auto spr = cocos2d::Sprite::createWithSpriteFrame(((cocos2d::Sprite*)sprite)->getSpriteFrame());
			spr->setLocalZOrder(sprite->getLocalZOrder());
			spr->setTag(sprite->getTag());
			spr->setPositionY(sprite->getPositionY());
			spr->setPositionX(bound+position_offset+(position_offset*counter*2));
			counter++;
			puzzle_board_layer_->addChild(spr);
			right_wraparound_piece_container_.push_back(spr);
		}

		//left side
		counter = 0;
		for(auto sprite : moving_piece_container_) {

			auto spr = cocos2d::Sprite::createWithSpriteFrame(((cocos2d::Sprite*)sprite)->getSpriteFrame());
			spr->setLocalZOrder(sprite->getLocalZOrder());
			spr->setTag(sprite->getTag());
			spr->setPositionY(sprite->getPositionY());
			spr->setPositionX(-bound+position_offset+(position_offset*counter*2));
			counter++;
			puzzle_board_layer_->addChild(spr);
			left_wraparound_piece_container_.push_back(spr);
		}

	} else if(is_vertical_swipe_) {

		bound = puzzle_sprite_height_;
		position_offset  = piece_height_/2;

		int counter= 0;
		//top side
		for(auto sprite : moving_piece_container_) {

			auto spr = cocos2d::Sprite::createWithSpriteFrame(((cocos2d::Sprite*)sprite)->getSpriteFrame());
			spr->setLocalZOrder(sprite->getLocalZOrder());
			spr->setTag(sprite->getTag());
			spr->setPositionX(sprite->getPositionX());
			spr->setPositionY((bound*2)-position_offset - (position_offset*counter*2));
			counter++;
			puzzle_board_layer_->addChild(spr);
			top_wraparound_piece_container_.push_back(spr);
		}

		//bottom side
		counter = 0;
		for(auto sprite : moving_piece_container_) {

			auto spr = cocos2d::Sprite::createWithSpriteFrame(((cocos2d::Sprite*)sprite)->getSpriteFrame());
			spr->setLocalZOrder(sprite->getLocalZOrder());
			spr->setTag(sprite->getTag());
			spr->setPositionX(sprite->getPositionX());
			spr->setPositionY(-position_offset -(position_offset*counter*2));
			counter++;
			puzzle_board_layer_->addChild(spr);
			bottom_wraparound_piece_container_.push_back(spr);
		}

	}
}

void ViewManager::RepositionPuzzlePieces(bool touch_ended) {

	time_delay_ = 0;
	if(is_vertical_swipe_) {

		if(touch_ended) {

			RePositionColPiecesOnTouchEnd(moving_piece_container_);
			RePositionColPiecesOnTouchEnd(top_wraparound_piece_container_);
			RePositionColPiecesOnTouchEnd(bottom_wraparound_piece_container_);

		} else {

			//on the top side
			if(moving_piece_container_.at(0)->getPositionY() + piece_height_/2 >= puzzle_sprite_height_ *3) {

				WrapThePiecesAroundTheVerticalBounds(moving_piece_container_ , 0 , piece_height_/2);

			} else if(top_wraparound_piece_container_.at(0)->getPositionY() + piece_height_/2 >= puzzle_sprite_height_ *3) {

				WrapThePiecesAroundTheVerticalBounds(top_wraparound_piece_container_ , 0 , piece_height_/2);

			} else if(bottom_wraparound_piece_container_.at(0)->getPositionY() + piece_height_/2 >= puzzle_sprite_height_ *3) {

				WrapThePiecesAroundTheVerticalBounds(bottom_wraparound_piece_container_ , 0 , piece_height_/2);

			} else if(moving_piece_container_.at(moving_piece_container_.size()-1)->getPositionY() - piece_height_/2 <= -puzzle_sprite_height_ *2) {

				//on the bottom side
				WrapThePiecesAroundTheVerticalBounds(moving_piece_container_ , puzzle_sprite_height_*2 , piece_height_/2);

			} else if(top_wraparound_piece_container_.at(top_wraparound_piece_container_.size()-1)->getPositionY() - piece_height_/2 <= -puzzle_sprite_height_ *2) {

				WrapThePiecesAroundTheVerticalBounds(top_wraparound_piece_container_ , puzzle_sprite_height_*2 , piece_height_/2);

			} else if(bottom_wraparound_piece_container_.at(bottom_wraparound_piece_container_.size()-1)->getPositionY() - piece_height_/2 <= -puzzle_sprite_height_ *2) {

				WrapThePiecesAroundTheVerticalBounds(bottom_wraparound_piece_container_ , puzzle_sprite_height_*2 , piece_height_/2);
			}
		}

	} else if(is_horizontal_swipe_) {

		if(touch_ended) {

			RePositionRowPiecesOnTouchEnd(moving_piece_container_);
			RePositionRowPiecesOnTouchEnd(left_wraparound_piece_container_);
			RePositionRowPiecesOnTouchEnd(right_wraparound_piece_container_);

		} else {

			//on the left side
			if(moving_piece_container_.at(0)->getPositionX() - piece_width_/2 <= -puzzle_sprite_width_ *2) {

				WrapThePiecesAroundTheHorizontalBounds(moving_piece_container_ , puzzle_sprite_width_ , piece_width_/2);

			} else if(left_wraparound_piece_container_.at(0)->getPositionX() - piece_width_/2 <= -puzzle_sprite_width_ *2) {

				WrapThePiecesAroundTheHorizontalBounds(left_wraparound_piece_container_ , puzzle_sprite_width_ , piece_width_/2);

			} else if(right_wraparound_piece_container_.at(0)->getPositionX() - piece_width_/2 <= -puzzle_sprite_width_ *2) {

				WrapThePiecesAroundTheHorizontalBounds(right_wraparound_piece_container_ , puzzle_sprite_width_ , piece_width_/2);

			} else if(moving_piece_container_.at(moving_piece_container_.size()-1)->getPositionX() + piece_width_/2 >= puzzle_sprite_width_ *3) {
				//on the right side
				WrapThePiecesAroundTheHorizontalBounds(moving_piece_container_ , -puzzle_sprite_width_ , piece_width_/2);

			} else if(left_wraparound_piece_container_.at(left_wraparound_piece_container_.size()-1)->getPositionX() + piece_width_/2 >= puzzle_sprite_width_ *3) {

				WrapThePiecesAroundTheHorizontalBounds(left_wraparound_piece_container_ , -puzzle_sprite_width_ , piece_width_/2);

			} else if(right_wraparound_piece_container_.at(right_wraparound_piece_container_.size()-1)->getPositionX() + piece_width_/2 >= puzzle_sprite_width_ *3) {

				WrapThePiecesAroundTheHorizontalBounds(right_wraparound_piece_container_ , -puzzle_sprite_width_ , piece_width_/2);
			}

		}
	}
}

void ViewManager::WrapThePiecesAroundTheHorizontalBounds(std::vector<cocos2d::Node*> puzzlepiece_container , float bound , float position_offset) {

	int counter = 0;
	for(auto spr : puzzlepiece_container) {

		spr->setPositionX(bound+position_offset+(position_offset*counter*2));
		counter++;
	}
}

void ViewManager::WrapThePiecesAroundTheVerticalBounds(std::vector<cocos2d::Node*> puzzlepiece_container , float bound , float position_offset) {

	int counter = 0;
	for(auto spr : puzzlepiece_container) {

		spr->setPositionY(bound-position_offset-(position_offset*counter*2));
		counter++;
	}
}

void ViewManager::RePositionRowPiecesOnTouchEnd(std::vector<cocos2d::Node*> puzzlepiece_container ) {

	float dt = 0.2f;
	for(auto spr : puzzlepiece_container) {

		if(spr->isVisible()) {


			int count ;
			count = (int)(spr->getPositionX()/piece_width_);

			if(spr->getPositionX() < 0) {

				count--;
			}

			cocos2d::log("RowDir : this is the count : %d",count);
//right side
			if(directions_[kRightDirection]) {

				float x = count*piece_width_ + piece_width_/2;
				float final_x;

				if(spr->getPositionX() - piece_width_/2 >= x) {

					float new_x = x + piece_width_;
					final_x = new_x;
					cocos2d::log("if part --> this is the new_x : %.2f and current x : %.2f",final_x ,spr->getPositionX());

				} else {

					final_x = x;
					cocos2d::log("else part --> this is the new_x : %.2f and current x : %.2f",final_x ,spr->getPositionX());
				}

				bool is_inside = RowBoundaryCheck(final_x , spr->getPositionY() , spr->getTag() , spr);
				auto moveby = cocos2d::MoveTo::create(dt , cocos2d::Vec2(final_x , spr->getPositionY()));
				auto ease = cocos2d::EaseBackOut::create(moveby);
				auto delay = cocos2d::DelayTime::create(time_delay_);
				auto callfun = cocos2d::CallFuncN::create(CC_CALLBACK_1(ViewManager::RemoveOutOfBoundPieces, this,spr,is_inside));
				spr->runAction(cocos2d::Sequence::create(delay,ease,callfun,nullptr));

			} else if(directions_[kLeftDirection]) {
			//left side
				float x = count*piece_width_ + piece_width_/2;
				float final_x;
				if(spr->getPositionX() +piece_width_/2 <= x) {

					float new_x  = x - piece_width_;
					final_x = new_x;

				} else {

					final_x = x;
				}

				bool is_inside = RowBoundaryCheck(final_x , spr->getPositionY() , spr->getTag() , spr);
				auto moveby = cocos2d::MoveTo::create(dt , cocos2d::Vec2(final_x , spr->getPositionY()));
				auto ease = cocos2d::EaseBackOut::create(moveby);
				auto delay = cocos2d::DelayTime::create(time_delay_);
				auto callfun = cocos2d::CallFuncN::create(CC_CALLBACK_1(ViewManager::RemoveOutOfBoundPieces, this,spr,is_inside));
				spr->runAction(cocos2d::Sequence::create(delay,ease,callfun,nullptr));
			}
			time_delay_+= 0;
		}
	}
}

void ViewManager::RePositionColPiecesOnTouchEnd(std::vector<cocos2d::Node*> puzzlepiece_container ) {

	float dt = 0.2f;

	for(auto spr : puzzlepiece_container) {

		if(spr->isVisible()) {

			int count = (int)(spr->getPositionY()/piece_height_);

			if(spr->getPositionY() < 0) {

				count--;
			}

			cocos2d::log("ColDir : this is the count : %d",count);
			if(directions_[kUpDirection]) {

				float y = count*piece_height_ + piece_height_/2;
				float final_y;

				//moving down
				if(spr->getPositionY() - piece_height_/2 >= y) {

					float new_y = y + piece_height_;
					final_y = new_y;

				} else {

					final_y = y;
				}

				bool is_inside = ColBoundaryCheck(spr->getPositionX() , final_y , spr->getTag() , spr);
				auto moveby = cocos2d::MoveTo::create(dt , cocos2d::Vec2(spr->getPositionX() , final_y));
				auto ease = cocos2d::EaseBackOut::create(moveby);
				auto delay = cocos2d::DelayTime::create(time_delay_);
				auto callfun = cocos2d::CallFuncN::create(CC_CALLBACK_1(ViewManager::RemoveOutOfBoundPieces, this,spr,is_inside));
				spr->runAction(cocos2d::Sequence::create(delay,ease,callfun,nullptr));
//				spr->runAction(ease);

			} else if(directions_[kDownDirection]) {
			//moving up

				float y = count*piece_height_ + piece_height_/2;
				float final_y;
				if(spr->getPositionY() + piece_height_/2 <= y) {

					float new_y = y - piece_height_;
					final_y = new_y;

				} else {

					final_y = y;
				}

				bool is_inside = ColBoundaryCheck(spr->getPositionX() , final_y , spr->getTag() , spr);
				auto moveby = cocos2d::MoveTo::create(dt, cocos2d::Vec2(spr->getPositionX() , final_y));
				auto ease = cocos2d::EaseBackOut::create(moveby);
				auto delay = cocos2d::DelayTime::create(time_delay_);
				auto callfun = cocos2d::CallFuncN::create(CC_CALLBACK_1(ViewManager::RemoveOutOfBoundPieces, this,spr,is_inside));
				spr->runAction(cocos2d::Sequence::create(delay,ease,callfun,nullptr));
//				spr->runAction(ease);
			}

			time_delay_+=0;
		}
	}

}

void ViewManager::ResetIsMoving(cocos2d::Node* sender) {

	set_is_moving(false);
	is_animating_ = false;
}

void ViewManager::ResetMoveRelatedInfo() {

	ResetMoveVars();
}

void ViewManager::RemoveOutOfBoundPieces(cocos2d::Node* sender , cocos2d::Node* spr, bool is_inside) {

	if(!is_inside) {

		spr->removeFromParentAndCleanup(true);
	}
}

void ViewManager::RemoveOutOfBoundColPieces(cocos2d::Node* sender , cocos2d::Node* spr , bool is_inside) {

	if(!is_inside) {

		spr->removeFromParentAndCleanup(true);
	}
}


bool ViewManager::RowBoundaryCheck(float final_x , float final_y , int tag , cocos2d::Node* spr) {

	bool is_inside = true;


	if(final_x < 0 || final_x > puzzle_sprite_width_) {

		GAMELOG("Removing the sprite");
//			spr->removeFromParentAndCleanup(true);
		is_inside = false;

	} else {

			short col = (int) (final_x / piece_width_);
			short row = (ROWS-1) - (int) (final_y / piece_height_);
			short current_index = GameGlobal::GetInstance()->GetIndexFromRowCol(col , row);

			GAMELOG("Not removing the sprite");
			GAMELOG("col : %d , row : %d , index : %d",col,row,current_index);

			UpdatePuzzleBoardState(current_index , spr->getTag());
			puzzle_piece_container_[tag] = spr;
		}


	return is_inside;
}

bool ViewManager::ColBoundaryCheck(float final_x , float final_y , int tag , cocos2d::Node* spr) {


	bool is_inside = true;

	if(final_y < 0 || final_y > puzzle_sprite_height_) {

		is_inside = false;

		} else {


				short col = (int) (final_x / piece_width_);
				short row = (ROWS-1) - (int) (final_y / piece_height_);
				short current_index = GameGlobal::GetInstance()->GetIndexFromRowCol(col , row);

				UpdatePuzzleBoardState(current_index , spr->getTag());
				puzzle_piece_container_[tag] = spr;
		}

	return is_inside;
}

void ViewManager::UpdatePuzzleBoardState(int index , int tag) {

	GameManager::GetInstance()->UpdatePuzzleCurrentBoardState(index , tag);
}

void ViewManager::MenuButtonCallBack(cocos2d::Ref* pSender) {

	Clear();
    GameSceneManager::GetInstance()->GoToOpeningScene();

}

void ViewManager::ResetMoveVars() {

//	is_moving_ = false;
	is_direction_selected_ = false;
	is_horizontal_swipe_ = false;
	is_vertical_swipe_ = false;
	selected_row_ = -1;
	selected_col_ = -1;
	moving_piece_container_.clear();
	right_wraparound_piece_container_.clear();
	left_wraparound_piece_container_.clear();
	top_wraparound_piece_container_.clear();
	bottom_wraparound_piece_container_.clear();
	memset(directions_ , 0 , sizeof(directions_));
}

void ViewManager::Clear(){

	GameManager::GetInstance()->Clear();

	ResetMoveRelatedInfo();

	puzzle_piece_container_.clear();
	initial_position_.clear();

	puzzle_board_layer_->removeAllChildrenWithCleanup(true);
	settings_layer_->removeAllChildrenWithCleanup(true);
	game_layer_->removeAllChildrenWithCleanup(true);

	game_scene_ = nullptr;
	game_layer_ = nullptr;
	puzzle_board_layer_ = nullptr;
	settings_layer_ = nullptr;
	puzzle_board_layer_ = nullptr;
	puzzle_sprite_width_  = 0.0f;
	puzzle_sprite_height_ = 0.0f;
	piece_height_ = 0.0f;
	piece_width_ = 0.0f;
	offset_ = 0.0f;
}

ViewManager::~ViewManager() {
	// TODO Auto-generated destructor stub
}

