/*
 * Cookie.h
 *
 *  Created on: 10-Jan-2017
 *  @Author: Ajay
 *  @fileName  : Cookie
 *  @brief : This the class for the Cookie and contains the cookie related
 *  information
 */

#pragma once
#ifndef COOKIE_H_
#define COOKIE_H_

#include "GameGlobal.h"

class Cookie {
public:
	Cookie();
	virtual ~Cookie();

	/* @function : CreateSprite()
	 * @brief : this method Asks ViewManager to create sprite
	 */
	void CreateSprite();

	/*
	 * @function : MoveCookieToEmptySpace(short ,short)
	 * @param new_row is the new row of the cookie
	 * @param new_col is the new col of the cookie
	 * @brief: Asks ViewManager to Make Cookie Sprite Fall
	 */
	void MoveCookieToEmptySpace(short new_row , short new_col  );

	/* @function : CreateSpriteForEmptySpaceAndAnimateToPosition(bool)
	 * @param is_last if its the last cookie being created
	 * @brief : this method Asks ViewManager to create sprite and animate it to its position
	 */
	void CreateSpriteAndAnimateToPosition(bool is_last);


	CookieType get_type(){ return type_;};

	void set_type(CookieType type){type_ = type;};
	void set_col(int col) { col_ = col;};
	void set_row(int row) { row_ = row;};
	void set_normal_sprite_name(std::string normal_sprite_name) {normal_sprite_name_ = normal_sprite_name;};
	void set_highlighted_sprite_name(std::string highlighted_sprite_name) {highlighted_sprite_name_ = highlighted_sprite_name;};

	short get_row() {return row_;};
	short get_col() {return col_;};

private:

	short row_;
	short col_;

	std::string normal_sprite_name_;
	std::string highlighted_sprite_name_;

	CookieType type_;

};

#endif /* COOKIE_H_ */
