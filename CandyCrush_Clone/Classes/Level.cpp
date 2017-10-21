/*
 * Level.cpp
 *
 *  Created on: 09-Jan-2017
 *      Author: ajay
 */

#include "Level.h"
#include "Cookie.h"
#include "GameManager.h"
#include "CurrentMove.h"


Level::Level(int level_no) {
	// TODO Auto-generated constructor stub

	row_ = -1;
	col_ = -1;
	total_moves_ = -1;
	target_score_ = -1;
	level_no_ = level_no;
}

void Level::Init() {

	ReadLevelFile();
//	CreateCookies();
}


void Level::ReadLevelFile() {

	auto filename = cocos2d::StringUtils::format("Levels/Level_%d.json" , level_no_);

	GameGlobal::GetInstance()->ReadLevel(filename , this);

	int index = 0;
	for (int i = 0; i < row_; i++) {

		for (int j = 0; j < col_ ; j++) {

			if(level_array_.at(index)) {

				bool is_last = index == ((row_*col_) -1) ? true : false;
				auto type = GameGlobal::GetInstance()->GetRandomCookieType(i,j,cookies_data_);
				CreateCookies(i,j,type,is_last,false);

			} else {

				cookies_data_.push_back(kNone);
			}

			index++;
		}
	}

	GAMELOG("This is the target_score: %d" , target_score_);
	GAMELOG("This is the total moves for level:  %d" , total_moves_);

}


Cookie* Level::InstantiateCookie(short row , short col ,CookieType type) {

		Cookie * cookie = new Cookie;
		cookie->set_type(type);
		cookie->set_row(row);
		cookie->set_col(col);
		cookie->set_normal_sprite_name(GameGlobal::GetInstance()->GetNormalSpriteNameForCookie(type));
		cookie->set_highlighted_sprite_name(GameGlobal::GetInstance()->GetHighlightedSpriteNameForCookie(type));
		short index  = GameGlobal::GetInstance()->GetIndexFromRowCol(col,row);
		cookies_container_.insert(std::pair<short , Cookie*>(index , cookie));

		if(index >= cookies_data_.size() ) {

			cookies_data_.push_back(type);

		} else {

			cookies_data_.at(index) = type;
		}

		return cookie;
}

void Level::CreateCookies(short row , short col ,CookieType type , bool is_last , bool animation_needed) {

	auto cookie = InstantiateCookie(row , col , type);

	if(animation_needed) {

		cookie->CreateSpriteAndAnimateToPosition(is_last);
	} else {

		cookie->CreateSprite();
	}
}


bool Level::IsValidMove(short row , short col , CookieType type , short current_index) {

	GAMELOG(" ");
	GAMELOG(" ");
	GAMELOG("______________________________________IsVALIDMOVE____________________________________________");
    GAMELOG("Checking from row %d-->" , row);
	GAMELOG("Checking from col %d-->" , col);
	GAMELOG(" ");
	GAMELOG(" ");
	CookieType current_type_ = kNone;

	/*
	 * this is the counter for total cookies of
	 * same type . its one at start which includes
	 * cookie being moved
	 */
	short counter=1;
	short temp_col = col;
	short temp_row = row;

	//check in left direction_;
	do{

		temp_col--;
		if(temp_col>=0) {

			short index = GameGlobal::GetInstance()->GetIndexFromRowCol(temp_col,temp_row);
			current_type_ = cookies_data_.at(index);

			/*
			 * if the new index is the previous location then stop looking in
			 * that direction
			 */
			if(current_index == index) {

				current_type_ = kNone;

			} else {

				if(current_type_ == type) {

					counter++;
					GAMELOG("Increenting Left");
				}
			}

		} else {

			current_type_ = kNone;
		}

		GAMELOG("checking the Left Diirection current_type : %d...target_type : %d",current_type_ , type);

	}while(current_type_ == type);


	if(counter>= MIN_MATCH) {
		return true;
	}

	//check in right direction
	temp_col = col;
	temp_row = row;
	do{

		temp_col++;
		if(temp_col<=COL-1) {

			short index = GameGlobal::GetInstance()->GetIndexFromRowCol(temp_col,temp_row);
			current_type_ = cookies_data_.at(index);

			/*
			 * if the new index is the previous location then stop looking in
			 * that direction
			 */
			if(current_index == index) {

				current_type_ = kNone;

			} else {

				if(current_type_ == type) {

					counter++;
					GAMELOG("Increenting Right");
				}
			}

		} else {

			current_type_ = kNone;
		}

		GAMELOG("checking the Right Diirection current_type : %d...target_type : %d",current_type_ , type);

	}while(current_type_ == type);


	if(counter>= MIN_MATCH) {
		return true;
	}

	//check in up direction

	/*
	 * for it be a valid move atleast a chain should be there in one direction
	 * so setting counter to 1
	 */
	counter = 1;
	temp_col = col;
	temp_row = row;
	do{

		temp_row--;
		if(temp_row>=0) {

			short index = GameGlobal::GetInstance()->GetIndexFromRowCol(temp_col,temp_row);
			current_type_ = cookies_data_.at(index);

			/*
			 * if the new index is the previous location then stop looking in
			 * that direction
			 */
			if(current_index == index) {

				current_type_ = kNone;

			} else {

				if(current_type_ == type) {

					counter++;
					GAMELOG("Increenting Up");
				}
			}

		} else {

			current_type_ = kNone;
		}

		GAMELOG("checking the Up Diirection current_type : %d...target_type : %d",current_type_ , type);

	}while(current_type_ == type);


	if(counter >= MIN_MATCH) {
		return true;
	}

	//check in down direction
	temp_col = col;
	temp_row = row;
	do{

		temp_row++;
		if(temp_row<=ROW-1) {

			short index = GameGlobal::GetInstance()->GetIndexFromRowCol(temp_col,temp_row);
			current_type_ = cookies_data_.at(index);

			/*
			 * if the new index is the previous location then stop looking in
			 * that direction
			 */
			if(current_index == index) {

				current_type_ = kNone;

			} else {

				if(current_type_ == type) {

					counter++;

					GAMELOG("Increenting Down");
				}
			}

		} else {

			current_type_ = kNone;
		}

		GAMELOG("checking the Down Diirection current_type : %d...target_type : %d",current_type_ , type);

	}while(current_type_ == type);


	if(counter >= MIN_MATCH) {
		return true;
	}



	return false;
}


void Level::CheckForHorizontalChain(std::set<short>& chain_container) {


	short counter = 0;
	CookieType type = kNone;
	std::vector<short> temp_container;

	for(short i = 0 ; i< row_ ; i++) {

		for(short j = 0 ; j< col_ ; j++) {

			short index = GameGlobal::GetInstance()->GetIndexFromRowCol(j,i);

			/*
			 * temp >0
			 */

			GAMELOG("HOrizontal cookie value : %d" , cookies_data_.at(index));
			if(cookies_data_.at(index)>0) {

				auto current_type = cookies_data_.at(index);

				if(current_type == type) {

					GAMELOG("Horizontal Chain");
					counter++;
					temp_container.push_back(index);
				} else {

					if(temp_container.size() >=MIN_MATCH) {

						for(auto cookie_index : temp_container) {

							chain_container.insert(cookie_index);
						}
					}

					temp_container.clear();
					type = current_type;
					temp_container.push_back(index);

				}

			} else {

				if(temp_container.size() >=MIN_MATCH) {

					for(auto cookie_index : temp_container) {

						chain_container.insert(cookie_index);
					}
				}
				temp_container.clear();
				type = kNone;
				temp_container.push_back(index);
			}
		}

		if(temp_container.size() >=MIN_MATCH) {

			for(auto cookie_index : temp_container) {

				chain_container.insert(cookie_index);
			}
		}
		temp_container.clear();
		type = kNone;
	}
}

void Level::CheckForVerticalChain(std::set<short>& chain_container) {

	short counter = 0;
	CookieType type = kNone;
	std::vector<short> temp_container;

	for(short i = 0 ; i< col_ ; i++) {

		for(short j = 0 ; j< row_ ; j++) {

			short index = GameGlobal::GetInstance()->GetIndexFromRowCol(i,j);

			if(cookies_data_.at(index)>0) {

				auto current_type = cookies_data_.at(index);

				if(current_type == type) {

					GAMELOG("Vertical Chain");
					counter++;
					temp_container.push_back(index);
				} else {

					if(temp_container.size() >=MIN_MATCH) {

						for(auto cookie_index : temp_container) {

							chain_container.insert(cookie_index);
						}
					}
					temp_container.clear();
					type = current_type;
					temp_container.push_back(index);

				}

			} else {

				if(temp_container.size() >=MIN_MATCH) {

					for(auto cookie_index : temp_container) {

						chain_container.insert(cookie_index);
					}
				}
				temp_container.clear();
				type = kNone;
				temp_container.push_back(index);
			}

		}

		if(temp_container.size() >=MIN_MATCH) {

			for(auto cookie_index : temp_container) {

				chain_container.insert(cookie_index);
			}
		}
		temp_container.clear();
		type = kNone;
	}
}

void Level::SwapCookieValue() {


	PrintCookieData();


	short selected_cookie_current_index = GameManager::GetInstance()->get_current_move()->get_selected_cookie_current_index();
	short selected_cookie_new_index = GameManager::GetInstance()->get_current_move()->get_selected_cookie_new_index();

	CookieType current_type = cookies_data_.at(selected_cookie_current_index);


	auto selected_cookie = cookies_container_.at(selected_cookie_current_index);
	auto adjacent_cookie = cookies_container_.at(selected_cookie_new_index);

	short selected_cookie_row = selected_cookie->get_row();
	short selected_cookie_col = selected_cookie->get_col();
	short adjacent_cookie_row = adjacent_cookie->get_row();
	short adjacent_cookie_col = adjacent_cookie->get_col();


	selected_cookie->set_row(adjacent_cookie_row);
	selected_cookie->set_col(adjacent_cookie_col);
	adjacent_cookie->set_row(selected_cookie_row);
	adjacent_cookie->set_col(selected_cookie_col);

	/*
	 * swap the cookie value
	 */
	cookies_data_.at(selected_cookie_current_index) = cookies_data_.at(selected_cookie_new_index);
	cookies_data_.at(selected_cookie_new_index) = current_type;

	/*
	 * swap the cookie
	 */
	cookies_container_.at(selected_cookie_current_index) = adjacent_cookie;
	cookies_container_.at(selected_cookie_new_index) = selected_cookie;

	PrintCookieData();
}


bool Level::RemoveChain(std::set<short>& chain_container) {

	bool chain_found = false;

	CheckForHorizontalChain(chain_container);
	CheckForVerticalChain(chain_container);

	/*
	 * Delete the cookies and remove
	 * from the containers
	 */
	for(auto index:chain_container) {

		auto cookie = cookies_container_.at(index);
		cookies_container_.erase(index);
		delete cookie;

		cookies_data_.at(index) = kEmpty;
	}

	if(chain_container.size()) {

		chain_found = true;
	}

	PrintCookieData();

	return chain_found;
}


void Level::SwapCookiesValueToEmptySpace() {


	short counter = 0;
	std::vector<short> temp_container;

	for(short i = 0 ; i< col_ ; i++) {

		for(short j = row_-1 ; j>= 1 ; j--) {

			short index = GameGlobal::GetInstance()->GetIndexFromRowCol(i,j);
//			short next_row = j-1;
			short next_row = j-1;
			short temp_row = j-1;
			CookieType type = kNone;
			short next_index;

			if(cookies_data_.at(index) == kEmpty) {


				while(type==kNone && temp_row >=0) {

					next_row = temp_row;
					next_index = GameGlobal::GetInstance()->GetIndexFromRowCol(i,next_row);
					type = cookies_data_.at(next_index);

					/*
					 * if its an empty block then go up
					 */
					if(type==kEmpty) {
						type = kNone;
					}

					temp_row--;
				}

				if(type!=kNone) {

					cookies_data_.at(index) = type;
					cookies_data_.at(next_index) = kEmpty;

					/*
					 * swap the mapping of the cookie w.r.t to index
					 */
					auto cookie = cookies_container_.at(next_index);
					cookie->MoveCookieToEmptySpace(j , i);
					cookies_container_[index] = cookie;
					cookies_container_.erase(next_index);
				}

			}
		}

	}
}


bool Level::CheckIfEmptyBlock(short index) {

	if(!cookies_data_.at(index)) {

		GAMELOG("this is the index of at index : %d",cookies_data_.at(index));
		return true;
	}

	return false;
}


void Level::FillUpEmptySpaces() {


	short total_empty_spaces = std::count(cookies_data_.begin() , cookies_data_.end() , kEmpty);
	short counter = 0;

	for(short i = 0 ; i< col_ ; i++) {

		for(short j = 0 ; j< row_ ; j++) {

			short index = GameGlobal::GetInstance()->GetIndexFromRowCol(i,j);

			if(cookies_data_.at(index)==kEmpty) {

				counter++;

				bool is_last = counter==total_empty_spaces ? true : false;

				auto type = GameGlobal::GetInstance()->GetRandomCookieType(j,i,cookies_data_);
				cookies_data_.push_back(type);
				CreateCookies(j,i,type , is_last , true);

			}
		}
	}
}

void Level::PrintCookieData() {


	GAMELOG(" ");
	GAMELOG(" ");
	GAMELOG("__________________________________________________________________ ");
	std::string coookies_data_str;

	int countr=0;
	for(auto indx : cookies_data_) {

		std::string inx_str= cocos2d::StringUtils::format(" %d ",indx);

		if(countr==COL){
			coookies_data_str+="\n";

			countr = 0;
		}
		countr++;
		coookies_data_str+=inx_str;
	}

	GAMELOG("This is the array status : %s",coookies_data_str.c_str());


	coookies_data_str.clear();

	 countr=0;
	for(auto cookie : cookies_container_) {

		std::string inx_str= cocos2d::StringUtils::format(" %d ",cookie.second->get_type());

		if(countr==COL){
			coookies_data_str+="\n";

			countr = 0;
		}
		countr++;
		coookies_data_str+=inx_str;
	}

	GAMELOG("This is the type status : %s",coookies_data_str.c_str());


}

CookieType Level::GetCookieTypeAtIndex(short index) {

	return cookies_data_.at(index);
}

void Level::Clear() {

	for(auto cookie : cookies_container_) {

		CC_SAFE_DELETE(cookie.second);
	}

	cookies_data_.clear();
	level_array_.clear();
	cookies_container_.clear();
	row_ = -1;
	col_ = -1;
	level_no_ = -1;
	total_moves_ = -1;
	target_score_ = -1;
}

Level::~Level() {
	// TODO Auto-generated destructor stub

	GAMELOG("Destructor Level");
}

