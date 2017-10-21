/*
 * GameManager.h
 *
 *  @Created on: 9-jan-2017
 *  @Author: ajay
 *  @fileName: GameManager
 *  @brief : this is the game manager of the game , it maintains the puzzle board's state. and checks if the puzzle is solved or not
 *  Its a singleton class
 */

#pragma once
#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "cocos2d.h"
#include "GameGlobal.h"


class Level;
class CurrentMove;

class GameManager {
public:
	GameManager();
	virtual ~GameManager();

	/* @function : Init()
	 * @brief : Inits the GameManager
	 */
	void Init();


	/* @function : CreateLevel()
	 * @brief : Creates the current level
	 */
	void CreateLevel();


	/* @function : PrintPuzzleBoardState()
	 * @brief : Clears the GameManager and its containers
	 */
	void Clear();

	/* @function : FillUpEmptySpaces()
	 * @brief : Asks Level to fill mpty spaces once the chain is broken
	 */
	void FillUpEmptySpaces();

	/* @function : SwapCookieValue()
	 * @brief : Calls level's SwapCookiesValueToEmptySpace;
	 */
	void SwapCookiesValueToEmptySpace();

	/* @function : IsValidMove()
	 * @brief : Asks Level if the Move played is valid or not
	 * @return : bool based on whether the move played is valid or not
	 */
	bool IsValidMove();

	/* @function : RemoveChain(std::set<short>& )
	 * @param chain_container is container for indices in the chain
	 * @brief : Asks Level to remove the Chain
	 * * @return : bool depending on if any chain was removed
	 */
	bool RemoveChain(std::set<short>& chain_container);

	/* @function : CheckIfCanMove(short , short  , Direction)
	 * @param row of the cookie being moved
	 * @param col of the cookie being moved
	 * @param direction is the swipe direction
	 * @param current_cookie_index is the index of the selected cookie
	 * @param adjacent_cookie_index is the index of the cookie being exchanged with
	 * @brief : Checks if a cookie can be moved or not
	 * @return : returns bool based on whether a cookie can be moved or not
	 */
	bool CheckIfCanMove(short row ,short col , Direction direction,short& selected_cookie_index, short& adjacent_cookie_index);


	/* @function : get_current_move()
	 * @brief : Gets the CurrentMove
	 * @return : returns the CurrentMove
	 */
	CurrentMove* get_current_move() { return current_move_;};

	/* @function : get_current_level_no()
	 * @brief : Gets the Current level no
	 * @return : returns the int value for variable current_level_no
	 */
	int get_current_level_no() { return current_level_no_;};

	/* @function : set_current_level_no(int)
	 * @param current_level_no is the current level.
	 * @brief : Sets the value for variable current_level_no_
	 */
	void set_current_level_no(int current_level_no) { current_level_no_ = current_level_no;};

	/* @function : GetInstance()
	 * @brief : Creates the instance for the ViewManager if called for the first time else returns already
	 * created instance
	 * @return : returns the instance of the ViewManager
	 */
	static GameManager* GetInstance();


private:

	static GameManager* game_manager_ref_;
	short current_level_no_;

	Level* current_level_;
	CurrentMove* current_move_;

};

#endif /* GAMEMANAGER_H_ */
