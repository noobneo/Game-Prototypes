/*
 * ValidMove.cpp
 *
 *  Created on: 12-Jan-2017
 *      Author: neo
 */

#include "CurrentMove.h"

CurrentMove::CurrentMove() {
	// TODO Auto-generated constructor stub


	selected_cookie_current_row_ = 0 ;
	selected_cookie_current_col_ = 0;
	selected_cookie_current_index_ = 0;
	selected_cookie_new_row_ = 0;
	selected_cookie_new_col_ = 0;
	selected_cookie_new_index_ = 0;

	selected_cookie_type_ = kNone;
	adjacent_cookie_type_ = kNone;
}


void CurrentMove::Clear() {

	selected_cookie_current_row_ = 0 ;
	selected_cookie_current_col_ = 0;
	selected_cookie_current_index_ = 0;
	selected_cookie_new_row_ = 0;
	selected_cookie_new_col_ = 0;
	selected_cookie_new_index_ = 0;

	selected_cookie_type_ = kNone;
	adjacent_cookie_type_ = kNone;
}

CurrentMove::~CurrentMove() {
	// TODO Auto-generated destructor stub
}

