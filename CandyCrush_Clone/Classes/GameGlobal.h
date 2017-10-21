/*
 * GameGlobal.h
 *
 *  @Created on: 9-jan-2017
 *  @Author: ajay
 *  @fileName : GameGlobal
 *  @brief : This is the GameGlobal contains the common data of the game. Its a singleton class
 */
#pragma once

#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_

#include <string>
#include <vector>

#define DEBUG 0

#if(DEBUG)
	#define GAMELOG(format, ...)      cocos2d::log(format, ##__VA_ARGS__)
#else
	#define GAMELOG(format, ...)
#endif


#define START_X 64
#define START_Y 800
#define MIN_SWIPE_DISTANCE 5
//#define WIDTH 32
//#define HEIGHT 36

#define WIDTH 64
#define HEIGHT 72


//#define ROW 9
//#define COL 9

#define ROW 4
#define COL 4


#define TOTAL_COOKIES 6
#define MIN_MATCH 3
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
}Direction;


/*
 * @brief : Different types of cookies
 */
typedef enum {

	kNone = 0,
	kEmpty =-1,
	kCroissantCookie = 1,
	kCupcakeCookie,
	kDanishCookie,
	kDonutCookie,
	kMacaroonCookie,
	kSugarCookie

}CookieType;

class Level;

class GameGlobal
{
public:
	GameGlobal();
	virtual ~GameGlobal();


	/* @function : SwapifMinimum()
	 * @param : copy_from value to be compared to
	 * @param copy_to is the value to which source need to be swapped
	 * @brief : Swaps target with source if source is minimum
	 */
	void SwapifMinimum(float& copy_from,float& copy_to);

	/* @function : SwapifMaximum()
	 * @param : copy_from value to be compared to
	 * @param copy_to the value to which source need to be swapped
	 * @brief : Swaps target with source if source is maximum
	 */
	void SwapifMaximum(float& copy_from,float& copy_to);

	/* @function : ReadLevel()
	 * @param : filename is json file to be parsed
	 * @param level is the current level
	 * @brief : Reads and parses the json level files
	 */
	void ReadLevel(std::string filename , Level* level);

	/* @function : GetRowColFromIndex(short& , short& , short&)
	 * @param index is the index for which row and col is to be calculated
	 * @param col is column for the current index
	 * @param row is row for the current index
	 * @brief : Calculates col and row from Index
	 */
	void GetRowColFromIndex(short& indx , short& col , short& row);

	/* @function : GetRowColFromPosition(short& , short& , float , float )
	 * @param col is column for the current cookie being moved
	 * @param row is row for the current cookie being moved
	 * @param x is the x'coordinate of the touch
	 * @param y is the y'coordinate of the touch
	 * @brief : Calculates col and row from touch position
	 */
	void GetRowColFromPosition(short& row , short& col , float x , float y);


	/* @function : NoChain(short , short , CookieType ,  std::vector<CookieType>)
	 * @param col is column for the current index
	 * @param row is row for the current index
	 * @param type is the cookietype to be checked for chain
	 * @param cookies_data_ is the already pushed cookies
	 * @brief : This method Checks if there is  a chain if so it returns true
	 * @return : returns bool based if the cahin is found or not;
	 */
	bool Chain(short row , short col , CookieType type , std::vector<CookieType> cookies_data_);


	/* @function : GetIndexFromRowCol(short& , short&)
	 * @param col is column for the current index
	 * @param row is row for the current index
	 * @brief : Calculates the index for row and col
	 * @return : returns short which is the index for row and col.
	 */
	short GetIndexFromRowCol(short& col , short& row);

	/* @function : GetRandomCookieType()
	 * @param row is the row at which cookie is being created
	 * @param col is the col at which cookie is being created
	 * @param cookies_data_ is the already pushed cookie_types
	 * @brief : This method returns random cookie type
	 * @return returns the CookieType
	 */
	CookieType GetRandomCookieType(short row, short col,std::vector<CookieType> cookies_data_);

	/* @function : GetHighlightedSpriteNameForCookie(CookieType)
	 * @param cookie_type is the cookie for which sprite name is needed
	 * @brief : This methods returns the name of highlighted sprite for the cookie
	 * @return : string which the highlighted-sprite's name
	 */
	std::string GetHighlightedSpriteNameForCookie(CookieType cookie_type);

	/* @function : GetSpriteNameForCookie(CookieType)
	 * @param cookie_type is the cookie for which sprite name is needed
	 * @brief : This methods returns the name of sprite for the cookie
	 * @return : string which the sprite's name
	 */
	std::string GetNormalSpriteNameForCookie(CookieType cookie_type);



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

private:
	static GameGlobal* game_global_ref_;
};

#endif /* GAMEGLOBAL_H_ */
