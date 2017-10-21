/*
 * GameGlobal.cpp
 *
 *  Created on: 9-jan-2017
 *      Author: ajay
 */

#include "GameGlobal.h"
#include "cocos2d.h"
#include "external/json/document.h"
#include "Level.h"

/*#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

*/

GameGlobal* GameGlobal::game_global_ref_ = nullptr;

GameGlobal::GameGlobal() {
	// TODO Auto-generated constructor stub

}

GameGlobal::~GameGlobal() {
	// TODO Auto-generated destructor stub
}


GameGlobal* GameGlobal::GetInstance() {

	if(!game_global_ref_) {

		game_global_ref_ = new GameGlobal();
	}

	return game_global_ref_;

}


void GameGlobal::LoadPlistFiles() {

}


void GameGlobal::ReadLevel(std::string filename , Level* level) {


	const std::string filestring  = cocos2d::FileUtils::getInstance()->getStringFromFile(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename));

	rapidjson::Document document;


	GAMELOG("This is the string %s",filestring.c_str());

	document.Parse(filestring.c_str());

	GAMELOG("parsed json File");

	const rapidjson::Value& tiles = document["tiles"];
	std::vector<int> level_array;

	for (rapidjson::SizeType i = 0; i < tiles.Size(); i++) {

		for (rapidjson::SizeType j = 0; j < tiles[i].Size(); j++) {

			level_array.push_back(tiles[i][j].GetInt());
		}
	}

	level->set_level_array(level_array);
	level->set_col(document["col"].GetInt());
	level->set_row(document["row"].GetInt());
	level->set_target_score(document["targetScore"].GetInt());
	level->set_total_moves(document["moves"].GetInt());
}



CookieType GameGlobal::GetRandomCookieType(short row, short col , std::vector<CookieType> cookies_data_) {

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::array<CookieType , TOTAL_COOKIES> cookies{kCroissantCookie ,kCupcakeCookie,kDanishCookie,kDonutCookie,kMacaroonCookie,kSugarCookie};

	std::shuffle(cookies.begin(),cookies.end(),std::default_random_engine(seed));

	CookieType type;

	/*
	 * Checks if previous two are of the same type is yes regenerates the cookietype
	 */
	do {

		int index  = rand() % TOTAL_COOKIES + 0;
		type  = cookies.at(index);

	} while(Chain(row , col , type , cookies_data_));

	return type;
}

bool GameGlobal::Chain(short row , short col , CookieType type , std::vector<CookieType> cookies_data_) {


	short row1 = row-1;
	short row2 = row-2;
	short row_index1 = GetIndexFromRowCol(col , row1);
	short row_index2 = GetIndexFromRowCol(col , row2);

	short col1 = col-1;
	short col2 = col-2;
	short col_index1 = GetIndexFromRowCol(col1 , row);
	short col_index2 = GetIndexFromRowCol(col2 , row);

	if(row_index1 < 0 ||  row_index2 < 0 || col_index1 < 0  || col_index2 < 0) {

		return false;

	} else {

		if(cookies_data_.at(row_index1) == type && cookies_data_.at(row_index2) == type) {

			return true;
		}

		if(cookies_data_.at(col_index1) == type && cookies_data_.at(col_index2) == type) {

			return true;
		}
	}

	return false;
}


std::string GameGlobal::GetNormalSpriteNameForCookie(CookieType cookie_type) {


	switch(cookie_type) {

	case kCroissantCookie :

		return  "Croissant@2x.png";
		break;

	case kCupcakeCookie :

		return  "Cupcake@2x.png";
		break;

	case kDanishCookie :

		return  "Danish@2x.png";
		break;

	case kDonutCookie :

		return  "Donut@2x.png";
		break;

	case kMacaroonCookie :

		return  "Macaroon@2x.png";
		break;

	case kSugarCookie :

		return  "SugarCookie@2x.png";
		break;
	}

	return "not found";
}

std::string GameGlobal::GetHighlightedSpriteNameForCookie(CookieType cookie_type) {

	switch(cookie_type) {

	case kCroissantCookie :

		return  "Croissant-Highlighted@2x.png";
		break;

	case kCupcakeCookie :

		return  "Cupcake-Highlighted@2x.png";
		break;

	case kDanishCookie :

		return  "Danish-Highlighted@2x.png";
		break;

	case kDonutCookie :

		return  "Donut-Highlighted@2x.png";
		break;

	case kMacaroonCookie :

		return  "Macaroon-Highlighted@2x.png";
		break;

	case kSugarCookie :

		return  "SugarCookie-Highlighted@2x.png";
		break;
	}

	return "not found";
}


void GameGlobal::GetRowColFromPosition(short& row , short& col , float x , float y) {

	col = (x -START_X + WIDTH/2) / (WIDTH);
	row = (START_Y + HEIGHT/2 - y) / HEIGHT;

}

void GameGlobal::GetRowColFromIndex( short& indx , short& col , short& row) {

	row = indx/COL;
	col = indx - (COL *row) ;
}

short  GameGlobal::GetIndexFromRowCol(short& col , short& row) {

	short index = col + (row* COL);
	return index;
}

void GameGlobal::SwapifMinimum(float& copy_from,float& copy_to) {

	if(copy_from < copy_to) {

		copy_to = copy_from;
	}
}

void GameGlobal::SwapifMaximum(float& copy_from,float& copy_to) {

	if(copy_from > copy_to) {

		copy_to = copy_from;
	}
}
