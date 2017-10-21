/*
 * GameManager.cpp
 *
 *  Created on: 26-Dec-2016
 *      Author: ajay
 */

#include "GameManager.h"
#include "GameGlobal.h"

GameManager* GameManager::game_manager_ref_ = nullptr;

GameManager::GameManager() {
	// TODO Auto-generated constructor stub
	current_level_no_ = 1;
}

GameManager* GameManager::GetInstance() {

	if(!game_manager_ref_) {

		game_manager_ref_ = new GameManager();
	}

	return game_manager_ref_;

}

void GameManager::Init() {

	GAMELOG("Inside the init of the GameManager");

}


void GameManager::UpdatePuzzleOriginalBoardState(int tag) {

	puzzle_board_start_state_.push_back(tag);
}


void GameManager::UpdatePuzzleCurrentBoardState(int tag) {

	puzzle_board_current_state_.push_back(tag);
}

void GameManager::UpdatePuzzleCurrentBoardState(int index , int tag) {

	puzzle_board_current_state_.at(index) = tag;
}

void GameManager::ShuffleTempContainer(std::vector<cocos2d::Node*>& temp_container) {

	int total_pieces = (ROWS*COLS) ;//- 1;
	 for(int i = 0 ; i < total_pieces; i++){

		int random = rand() % 100;

		int row = i/COLS;
		int col = i - (COLS *row) ;

		GAMELOG("Row : %d , Col : %d , for index : %d" , row ,col , i);

		if(random % 2==0) {

			cocos2d::Node* val_at_first ;
			val_at_first =  temp_container.at((0 * COLS) + col);

			moves_container_.push_back(MOVE_COL);
			for(int row_no = 0 ; row_no < ROWS ; row_no++) {

				int current_index = (row_no * COLS) + col;
				int next_index = ((row_no+1) * COLS) + col;

				if(row_no == ROWS-1) {
					//last element swap with the first

					temp_container.at(current_index) = val_at_first;
				} else {

					temp_container.at(current_index) = temp_container.at(next_index);
				}
			}
		} else {

			cocos2d::Node* val_at_first ;
			val_at_first =  temp_container.at((row * COLS) + 0);

			moves_container_.push_back(MOVE_ROW);

			for(int col_no = 0 ; col_no < COLS ; col_no++) {

				int current_index = (row * COLS) + col_no;
				int next_index = (row * COLS) + (col_no+1);

				if(col_no == COLS-1) {
					//last element swap with the first

					temp_container.at(current_index) = val_at_first;
				} else {

					temp_container.at(current_index) = temp_container.at(next_index);
				}
			}

		}
	}


	for(int m = 0 ;  m< moves_container_.size() ; m++) {

		GAMELOG("%s<--" ,moves_container_.at(m).c_str());
	}

}


void GameManager::SelectRowColToMove(short& tag , short& selected_col , short& selected_row) {


	auto it = std::find(puzzle_board_current_state_.begin() ,puzzle_board_current_state_.end() , tag);
	short indx = it - puzzle_board_current_state_.begin() ;

	GameGlobal::GetInstance()->GetRowColFromIndex(indx , selected_col , selected_row);
}

int GameManager::GetCurrentBoardStateAtIndex(int index) {

	if(!puzzle_board_current_state_.size()) {

		return -1;
	}

	return puzzle_board_current_state_.at(index);
}
bool GameManager::CheckIfPuzzleSolved() {

	PrintPuzzleBoardState();

	if(puzzle_board_current_state_ == puzzle_board_start_state_) {

		cocos2d::log("PUZZLE SOLVED");
		return true;
	}


	return false;
	cocos2d::log("PUZZLE NOT YET SOLVED");
}

void GameManager::PrintPuzzleBoardState() {

	GAMELOG("_______________ORIGINAL BOARD STATE_______________________________");

	for(auto indx : puzzle_board_start_state_) {

		GAMELOG("%d , " , indx);
	}
	GAMELOG("__________________________________________________________________");


	GAMELOG("________________CURRENT BOARD STATE_______________________________");

	for(auto new_indx : puzzle_board_current_state_) {

		GAMELOG("%d , " , new_indx);
	}
	GAMELOG("__________________________________________________________________");
}

void GameManager::Clear() {

	moves_container_.clear();
	puzzle_board_start_state_.clear();
	puzzle_board_current_state_.clear();
}

GameManager::~GameManager() {
	// TODO Auto-generated destructor stub
}

