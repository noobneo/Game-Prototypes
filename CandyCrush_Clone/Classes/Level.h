/*
 * Level.h
 *
 *  Created on: 09-Jan-2017
 *      Author: ajay
 */

#pragma once
#ifndef LEVEL_H_
#define LEVEL_H_

#include "cocos2d.h"
#include "external/json/document.h"
#include "GameGlobal.h"

class Cookie;

class Level {
public:
	Level(int level_no);

	/* @function : Init()
	 * @brief : Inits the current level
	 */
	void Init();

	/* @function : Clear()
	 * @brief : Clears the level data , and releases cookies_data_
	 */
	void Clear();

	/* @function : PrintCookieData()
	 * @brief :Prints the cookie array
	 */
	void PrintCookieData();

	/* @function : SwapCookieValue()
	 * @brief : Swaps and updates the CookieValues in the cookie_data_;
	 */
	void SwapCookieValue();

	/* @function : FillUpEmptySpaces()
	 * @brief : Fill up the empty spaces once the chain is broken
	 */
	void FillUpEmptySpaces();

	/* @function : SwapCookieValue()
	 * @brief : Swaps cookies value to down if its a valid empty spot;
	 */
	void SwapCookiesValueToEmptySpace();

	/* @function : CheckForHorizontalChain(std::set<short>&)
	 * @param chain_container is container for indices in the chain
	 * @brief : Checks for the horizontal chain and pushes the index into the container;
	 */
	void CheckForHorizontalChain(std::set<short>& chain_container);

	/* @function : CheckForVerticalChain(std::set<short>&)
	 * @param chain_container is container for indices in the chain
	 * @brief : Checks for the vertical chain and pushes the index into the container;
	 */
	void CheckForVerticalChain(std::set<short>& chain_container);

	/* @function : CreateCookies(short , short , CookieType)
	 * @param row is the row of the cookie
	 * @param col is the col of the cookie
	 * @param type is the CookieType to be created
	 * @param is_last is bool if the cookie being created i slast cookie being created
	 * @param animation_needed is bool if cookie needs to be animated
	 * @brief : Instantiates Cookie and asks to create sprite and animation if needed
	 */
	void CreateCookies(short row , short col ,CookieType type , bool is_last , bool animation_needed);

	/* @function : InstantiateCookie(short , short , CookieType)
	 * @param row is the row of the cookie
	 * @param col is the col of the cookie
	 * @param type is the CookieType to be created
	 * @brief :Creates the cookies and stores in the container
	 * @return Cookie* returns the cookie object created
	 */
	Cookie* InstantiateCookie(short row , short col ,CookieType type);

	/* @function : RemoveChain(std::set<short>& )
	 * @param chain_container_ is container for indices in the chain
	 * @brief : Removes the Chain
	 * @return : bool depending on if any chain was removed
	 */
	bool RemoveChain(std::set<short>& chain_container);

	/* @function : GetCookieTypeAtIndex(short)
	 * @param index is the location for which cookie type is needed
	 * @brief :returns the cookietype at index
	 * @return CookieType is the type of the cookie at the index
	 */
	CookieType GetCookieTypeAtIndex(short index);

	/* @function : CheckIfEmptyBlock(short)
	 * @param index of to be queried
	 * @brief :Checks if the index contains a cookie or is empty
	 * @return : bool depending on whether the block is empty or contains a cookie
	 */
	bool CheckIfEmptyBlock(short index);

	/* @function : IsValidMove(short , short , CookieType , short)
	 * @param row is the row for the cookie for which MoveNeed to be checked
	 * @param col is the col for the cookie for which MoveNeed to be checked
	 * @param current_index is the index of the cookie for which MoveNeed to be checked
	 * @brief :Checks if the move being playes is valid or not
	 * @return : bool depending on whether the move is valid or not
	 */
	bool IsValidMove(short row , short col , CookieType type , short current_index);
	/*
	 * @brief setters for the variables of the Level
	 */

	void set_col(short col){ col_ = col;};
	void set_row(short row){ row_ = row;};
	void set_total_moves(short total_moves){ total_moves_ = total_moves;};
	void set_target_score(short target_score){ target_score_ = target_score;};
	void set_level_array(std::vector<int>level_array){ level_array_ = level_array;};


	virtual ~Level();



private:

	/* @function : ReadLevelFile()
	 * @brief : Calls GameGlobal ReadMethod to read the current level
	 */
	void ReadLevelFile();


	short level_no_;
	short total_moves_;
	short row_;
	short col_;
	int target_score_;
	std::vector<int> level_array_;
	std::vector<CookieType> cookies_data_;
	std::map<short , Cookie*> cookies_container_;

};

#endif /* LEVEL_H_ */
