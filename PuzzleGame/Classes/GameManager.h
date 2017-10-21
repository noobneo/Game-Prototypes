/*
 * GameManager.h
 *
 *  @Created on: 26-Dec-2016
 *  @Author: ajay
 *  @fileName: GameManager
 *  @brief : this is the game manager of the game , it maintains the puzzle board's state. and checks if the puzzle is solved or not
 *  Its a singleton class
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "cocos2d.h"

class GameManager {
public:
	GameManager();
	virtual ~GameManager();

	/* @function : Init()
	 * @brief : Inits the GameManager
	 */
	void Init();

	/* @function : PrintPuzzleBoardState()
	 * @brief : Clears the GameManager and its containers
	 */
	void Clear();

	/* @function : PrintPuzzleBoardState()
	 * @brief : Prints the state of the Puzzle Board
	 */
	void PrintPuzzleBoardState();

	/* @function : CheckIfPuzzleSolved()
	 * @brief : this method checks if the puzzle is solved or not
	 * @return  :return bool based on if the puzzle is solved or not
	 */
	bool CheckIfPuzzleSolved();


	/* @function : UpdatePuzzleOriginalBoardState(int)
	 * @param tag is the new value in the puzzle board state
	 * @brief : this method pushes the tag in the puzzle_board_start_state_
	 */
	void UpdatePuzzleOriginalBoardState(int tag);

	/* @function : UpdatePuzzleCurrentBoardState(int)
	 * @param tag is the new value in the puzzle board state
	 * @brief : this method pushes the tag in the puzzle_board_current_state_
	 */
	void UpdatePuzzleCurrentBoardState(int tag);

	/* @function : UpdatePuzzleCurrentBoardState(int,int)
	 * @param index of the puzzle _board_state .
	 * @param tag is the new value for the index
	 * @brief : this method updates the current puzzle board state for the index
	 */
	void UpdatePuzzleCurrentBoardState(int index , int tag);

	/* @function : ShuffleTempContainer(std::vector<cocos2d::Node*>&)
	 * @param temp_container is the container that needs to be shuffled.
	 * @brief : Shuffles the container
	 */
	void ShuffleTempContainer(std::vector<cocos2d::Node*>& temp_container);

	/* @function : SelectRowColToMove(int,int)
	 * @param tag is the tag of the puzzle piece clicked .
	 * @param selected_col is column of the clicked puzzle piece
	 * @param selected_row is row of the clicked puzzle piece
	 * @brief : This methods gets the row and col for the selected piece
	 */
	void SelectRowColToMove(short& tag , short& selected_col , short& selected_row);

	/* @function : GetCurrentBoardStateAtIndex(int)
	 * @param index for which puzzle board state is needed.
	 * @brief : Gets the puzzle board state at the index
	 * @return : returns int which is the board state at the index
	 */
	int GetCurrentBoardStateAtIndex(int index);


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

	std::vector<std::string> moves_container_;
	std::vector<int> puzzle_board_start_state_;
	std::vector<int> puzzle_board_current_state_;

};

#endif /* GAMEMANAGER_H_ */
