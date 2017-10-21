/*
 * GameManager.cpp
 *
 *  Created on: 9-jan-2017
 *      Author: ajay
 */

#include "GameManager.h"
#include "CurrentMove.h"
#include "Level.h"

GameManager* GameManager::game_manager_ref_ = nullptr;

GameManager::GameManager() {
	// TODO Auto-generated constructor stub
	current_level_no_ = 1;
	current_level_ = nullptr;
	current_move_ = nullptr;
}

GameManager* GameManager::GetInstance() {

	if(!game_manager_ref_) {

		game_manager_ref_ = new GameManager();
	}

	return game_manager_ref_;
}

void GameManager::Init() {


	GAMELOG("Inside the init of the GameManager");


	srand(time(0));
	CreateLevel();

	current_move_ = new CurrentMove;
}



void GameManager::CreateLevel() {

	current_level_ = new Level(3);
	current_level_->Init();
}


bool GameManager::CheckIfCanMove(short row, short col , Direction direction,short& selected_cookie_index, short& adjacent_cookie_index) {

	short index = GameGlobal::GetInstance()->GetIndexFromRowCol(col , row);

	short next_row  = row;
	short next_col = col ;
	short next_index ;

	if(direction == kLeftDirection ) {

		if(col==0) {

			GAMELOG("col 0 returning ");
			return false;
		}
		next_col = col-1;

	} else if(direction == kRightDirection ) {

		if(col==(COL-1)) {

			GAMELOG("col MAX returning ");
			return false;
		}
		next_col = col+1;

	} else if(direction == kUpDirection) {

		if(row==0) {

			GAMELOG("row 0 returning ");
			return false;
		}

		next_row = row-1;

	} else if(direction == kDownDirection ) {

		if(row == (ROW-1)) {

			GAMELOG("row MAX returning ");
			return false;
		}
		next_row = row+1;

	}



	next_index = GameGlobal::GetInstance()->GetIndexFromRowCol(next_col , next_row);

	 if(current_level_->CheckIfEmptyBlock(index)) {

		 GAMELOG("this index nil returning ");
		 return false;

	 } else if(current_level_->CheckIfEmptyBlock(next_index)) {

		 GAMELOG("next index nil returning ");
		 return false;
	 }



	 selected_cookie_index = index;
	 adjacent_cookie_index = next_index;

	 current_move_->set_selected_cookie_current_row(row);
	 current_move_->set_selected_cookie_current_col(col);
	 current_move_->set_selected_cookie_new_row(next_row);
	 current_move_->set_selected_cookie_new_col(next_col);
	 current_move_->set_selected_cookie_current_index(index);
	 current_move_->set_selected_cookie_new_index(next_index);
	 current_move_->set_selected_cookie_type(current_level_->GetCookieTypeAtIndex(index));
	 current_move_->set_adjacent_cookie_type(current_level_->GetCookieTypeAtIndex(next_index));



	 GAMELOG(" ");
	 GAMELOG(" ");
	 GAMELOG(" ");
	 GAMELOG("Selected row %d-->" , row);
	 GAMELOG("Selected col %d-->" , col);
	 GAMELOG("Adjacent row %d-->" , next_row);
	 GAMELOG("Adjacent col %d-->" , next_col);
	 GAMELOG("Selected CookieType %d-->" , current_level_->GetCookieTypeAtIndex(index));
	 GAMELOG("Adjacent CookieType %d-->" , current_level_->GetCookieTypeAtIndex(next_index));
	 GAMELOG(" ");
	 GAMELOG(" ");
	 GAMELOG(" ");

	 return true;
}


void  GameManager::SwapCookiesValueToEmptySpace() {

	current_level_->SwapCookiesValueToEmptySpace();
}

bool GameManager::RemoveChain(std::set<short>& chain_container) {

	bool chain_found =  current_level_->RemoveChain(chain_container);
	current_move_->Clear();
	return chain_found;
}

bool GameManager::IsValidMove() {


	short current_row =  current_move_->get_selected_cookie_current_row();
	short current_col = current_move_->get_selected_cookie_current_col();
	short new_row = current_move_->get_selected_cookie_new_row();
	short new_col = current_move_->get_selected_cookie_new_col();
	short current_index = current_move_->get_selected_cookie_current_index();
	short new_index = current_move_->get_selected_cookie_new_index();
	CookieType selcted_cookie_type = current_move_->get_selected_cookie_type();
	CookieType adjacent_cookie_type = current_move_->get_adjacent_cookie_type();

	if(current_level_->IsValidMove(new_row , new_col , selcted_cookie_type , current_index)) {

		current_level_->SwapCookieValue();
		return true;

	} else if(current_level_->IsValidMove(current_row , current_col , adjacent_cookie_type , new_index)) {

		current_level_->SwapCookieValue();
		return true;
	}

	return false;
}


void GameManager::FillUpEmptySpaces() {

	current_level_->FillUpEmptySpaces();
}

void GameManager::Clear() {

	current_level_no_ = 1;

	current_level_->Clear();

	CC_SAFE_DELETE(current_move_);
	CC_SAFE_DELETE(current_level_);
	CC_SAFE_DELETE(game_manager_ref_);
}

GameManager::~GameManager() {
	// TODO Auto-generated destructor stub
	GAMELOG("Destructor GameManager");
}

