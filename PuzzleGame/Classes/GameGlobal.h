/*
 * GameGlobal.h
 *
 *  @Created on: 26-Dec-2016
 *  @Author: ajay
 *  @fileName : GameGlobal
 *  @brief : This is the GameGlobal contains the common data of the game. Its a singleton class
 */
#pragma once

#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_


#define DEBUG 1
#define ROWS 3
#define COLS 3
#define EMPTY -1
#define TOTAL_DIRECTION 4
#define MIN_X_SWIPE 5
#define MIN_Y_SWIPE 5
#define MIN_SWIPE_DISTANCE 2
#define MAX_OFFSET 35

#define MOVE_COL "move_col"
#define MOVE_ROW "move_row"

#if(DEBUG)
	#define GAMELOG(format, ...)      cocos2d::log(format, ##__VA_ARGS__)
#else
	#define GAMELOG(format, ...)
#endif

/*
 * @brief : Different scenes/ screen in the game
 * @kOpeningScene : Opening Scene or the MainMenu Scene
 * kGameWorldScene : This is the gameWorld Scene
 */
typedef enum {

	kSceneNone = 0,
	kOpeningScene ,
	kGameWorldScene,
}SceneType;


/*
 * @brief : Swipe Directions
 */
typedef enum
{
	kRightDirection = 0,
	kLeftDirection ,
	kUpDirection ,
	kDownDirection,
}Directions;


class GameGlobal
{
public:
	GameGlobal();
	virtual ~GameGlobal();

	/* @function : GetInstance()
	 * @brief : Creates the instance for the GameGlobal if called for the first time else returns already
	 * created instance
	 * @return : returns the instance of the GameGlobal
	 */
	static GameGlobal* GetInstance();

	/* @function : LoadPlistFiles()
	 * @brief : This method loads the plist files and add them to Cache.
	 */
	void LoadPlistFiles();

	/* @function : GetRowColFromIndex(short& , short& , short&)
	 * @param index is the index for which row and col is to be calculated
	 * @param col is column for the current index
	 * @param row is row for the current index
	 * @brief : This method loads the plist files and add them to Cache.
	 */
	void GetRowColFromIndex(short& indx , short& col , short& row);

	/* @function : GetIndexFromRowCol(short& , short&)
	 * @param col is column for the current index
	 * @param row is row for the current index
	 * @brief : Calculates the index for row and col
	 * @return : returns short which is the index for row and col.
	 */
	short GetIndexFromRowCol(short& col , short& row);

private:
	static GameGlobal* game_global_ref_;
};

#endif /* GAMEGLOBAL_H_ */
