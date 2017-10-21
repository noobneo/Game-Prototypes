/*
 * CurrentMove.h
 *
 *  @Created on: 12-Jan-2017
*   @Author: Ajay
*   @fileName : CurrentMove
*   @brief : contains the data of the Current Move
 */

#pragma once
#ifndef CLASSES_CURRENTMOVE_H_
#define CLASSES_CURRENTMOVE_H_

#include "GameGlobal.h"

class CurrentMove {
public:
	CurrentMove();
	virtual ~CurrentMove();

	/* @function : Clear()
	 * @brief : Clears the ValidMove vars
	 */
	void Clear();

	/*
	 * @brief : setters of the vars of the CurrentMove
	 */

	void set_selected_cookie_current_row(short selected_cookie_current_row) {selected_cookie_current_row_ = selected_cookie_current_row;};
	void set_selected_cookie_current_col(short selected_cookie_current_col) {selected_cookie_current_col_ = selected_cookie_current_col;};
	void set_selected_cookie_new_row(short selected_cookie_new_row) {selected_cookie_new_row_ = selected_cookie_new_row;};
	void set_selected_cookie_new_col(short selected_cookie_new_col) {selected_cookie_new_col_ = selected_cookie_new_col;};
	void set_selected_cookie_current_index(short selected_cookie_current_index) {selected_cookie_current_index_ = selected_cookie_current_index;};
	void set_selected_cookie_new_index(short selected_cookie_new_index) {selected_cookie_new_index_ = selected_cookie_new_index;};
	void set_selected_cookie_type(CookieType selected_cookie_type) {selected_cookie_type_ = selected_cookie_type;};
	void set_adjacent_cookie_type(CookieType adjacent_cookie_type) {adjacent_cookie_type_ = adjacent_cookie_type;};

	/*
	 * @brief : getters of the vars of the CurrentMove
	 */

	short get_selected_cookie_current_row() { return selected_cookie_current_row_;};
	short get_selected_cookie_current_col() { return selected_cookie_current_col_;};
	short get_selected_cookie_new_row() { return selected_cookie_new_row_;};
	short get_selected_cookie_new_col() { return selected_cookie_new_col_;};
	short get_selected_cookie_current_index() { return selected_cookie_current_index_;};
	short get_selected_cookie_new_index() { return selected_cookie_new_index_;};
	CookieType get_selected_cookie_type() { return selected_cookie_type_;};
	CookieType get_adjacent_cookie_type() { return adjacent_cookie_type_;};


private :

	short selected_cookie_current_row_;
	short selected_cookie_current_col_;
	short selected_cookie_current_index_;
	short selected_cookie_new_row_;
	short selected_cookie_new_col_;
	short selected_cookie_new_index_;

	CookieType selected_cookie_type_;
	CookieType adjacent_cookie_type_;

};

#endif /* CLASSES_CURRENTMOVE_H_ */
