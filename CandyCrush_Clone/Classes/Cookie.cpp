/*
 * Cookie.cpp
 *
 *  Created on: 10-Jan-2017
 *  Author: Ajay
 */

#include "Cookie.h"
#include "ViewManager.h"

Cookie::Cookie() {
	// TODO Auto-generated constructor stub

	type_ = kNone;
	row_ = -1;
	col_ = -1;
}


void Cookie::CreateSprite() {


	ViewManager::GetInstance()->CreateCookie(normal_sprite_name_ , row_ , col_);
}


void Cookie::MoveCookieToEmptySpace(short new_row , short new_col ) {

	GAMELOG("this the type of the cookies being dropped : %d",type_);

	ViewManager::GetInstance()->MoveCookieToEmptySpace(row_ , col_ , new_row , new_col);

	row_ = new_row;
	col_ = new_col;

}


void Cookie::CreateSpriteAndAnimateToPosition(bool is_last) {

	ViewManager::GetInstance()->CreateCookieAndAnimateToPosition(normal_sprite_name_ , row_ , col_ , is_last);
}


Cookie::~Cookie() {
	// TODO Auto-generated destructor stub
	GAMELOG("Destructor Cookie");
}

