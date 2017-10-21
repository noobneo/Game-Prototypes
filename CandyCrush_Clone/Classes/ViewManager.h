/*
 * ViewManager.h
 *
 *  @Created on: 9-jan-2017
 *  @Author: ajay
 *  @fileName : ViewManager
 *  @brief :It is a singleton class. this is the view manager of the game , it creates the game layer , is responsible for the view part of the game.
 *
 */

#pragma once
#ifndef VIEWMANAGER_H_
#define VIEWMANAGER_H_

#include "cocos2d.h"

class Settings;

class ViewManager {
public:
	ViewManager();
	virtual ~ViewManager();

	/* @function : CreatePuzzleBoardBoundingBox()
	 * @brief : Creates the bounding box for the puzzle_board_layer_
	 */
	void CreatePuzzleBoardBoundingBox();

	/* @function : CreateBackGround()
	 * @brief : Creates the background image for the gameworld scene
	 */
	void CreateBackGround();

	/* @function : Clear()
	 * @brief : It clears all the containers and also calls for the Clear method for the GameManager
	 */
	void Clear();

	/* @function : RemoveChain()
	 * @brief : Calls GameScenes RemoveChain and then removes the sprite of the cookies
	 * found in the chain
	 */
	void RemoveChain();


	void FillUpEmptySpaces();

	/* @function : Init(cocos2d::Scene)
	 * @param game_scene this the scene where view_layer is added and from the Init is called
	 * @brief : this inits the creation of game and settings layer and stores the ref to the game_scene
	 */
	void Init(cocos2d::Scene* game_scene);

	/* @function : MoveCookies(short , short)
	 * @param current_cookie_index is the index of the selected cookie
	 * @param adjacent_cookie_index is the index of the cookie being exchanged with
	 * @brief : This method moves and animates the cookies to each other position
	 */
	void MoveCookies(short selected_cookie_index,short adjacent_cookie_index);

	/* @function : CreateCookieSprite(std::string , short , short)
	 * @param normal_sprite_name is the sprite name for normal sate of cookie
	 * @param row  is row of the cookie
	 * @param col  is col of the cookie
	 * @brief : this method creates cookie sprite positions and add it to the container
	 * @return : cocos2d::Sprite* which is the sprite created for the cookie;
	 */

	cocos2d::Sprite* CreateCookieSprite(std::string normal_sprite_name , short row , short col);

	/* @function : CreateCookie(std::string , short , short)
	 * @param normal_sprite_name is the sprite name for normal sate of cookie
	 * @param row  is row of the cookie
	 * @param col  is col of the cookie
	 * @brief : this method creates cookie , sets its positions and adds it to the layer
	 */
	void CreateCookie(std::string normal_sprite_name , short row , short col);

	/* @function : CreateCookieAndAnimateToPosition(std::string , short , short , bool)
	 * @param normal_sprite_name is the sprite name for normal sate of cookie
	 * @param row_  is row of the cookie
	 * @param col_  is col of the cookie
	 * @param is_last if its the last cookie being created
	 * @brief : this method creates cookies  adds it to puzzle_layer and animates it to its position
	 */
	void CreateCookieAndAnimateToPosition(std::string normal_sprite_name , short row , short col , bool is_last);

	/* @function : MoveCookieToEmptySpace(short , short ,short , short)
	 * @param old_row is the old row of the cookie
	 * @param old_col is the old col of the cookie
	 * @param new_row  is row of the cookie
	 * @param new_col  is col of the cookie
	 * @brief : this method makes the cookie sprite fall to new position
	 */
	void MoveCookieToEmptySpace(short old_row , short old_col , short new_row , short new_col);

	/* @function : EnableTouch()
	 * @param sender is the sender of this callback
	 * @brief : This method calls gamescenes method to reset and enable the touch
	 */
	void ResetEnableTouch(cocos2d::Node* sender);

	/* @function : MenuButtonCallBack()
	 * @param sender is the sender of this callback
	 * @brief : MenuButton Callback , this methods calls to scenemanager to go back to
	 * opening scene
	 */
	void MenuButtonCallBack(cocos2d::Ref* sender);

	/* @function : CookieFillAnimationCallBack(cocos2d::Node*)
	 * @brief : This is the callback when CookieDropANimation ends
	 */
	void CookieFillAnimationCallBack(cocos2d::Node* sender );


	/* @function : CookieMoveCallBack(cocos2d::Node* , cocos2d::Sprite* ,short , cocos2d::Sprite* ,short)
	 * @param selected_cookie is selected cookies' sprite
	 * @param selected_cookie_index is the index of the selected cookie
	 * @param adjacent_cookie is adjacent cookie's sprite
	 * @param adjacent_cookie_index is the index of the cookie with which swap is being made
	 * @brief : This is the callback when MoveAnimation Ends
	 */
	void CookieMoveCallBack(cocos2d::Node* sender , cocos2d::Sprite* selected_cookie , short selected_cookie_index , cocos2d::Sprite* adjacent_cookie , short adjacent_cookie_index);

	/* @function : ContainsPoint(cocos2d::Vec2)
	 * @param position where player has touched the screen.
	 * @brief :  this methods checks if the puzzle_layer_ contains the touch position.
	 * @return it returns true or false based on if the puzzle_layer_ contains the touch_position
	 */
	bool ContainsPoint(cocos2d::Vec2 position);

	/* @function : GetInstance()
	 * @brief : Creates the instance for the ViewManager if called for the first time else returns already
	 * created instance
	 * @return : returns the instance of the ViewManager
	 */

	static ViewManager* GetInstance();

private:

	static ViewManager* view_manager_ref_;

	float anim_delay_;
	float min_x_;
	float max_x_;
	float min_y_;
	float max_y_;

	cocos2d::Scene* game_scene_;
	cocos2d::Layer* hud_layer_;
	cocos2d::Layer* tile_layer_;
	cocos2d::Layer* puzzle_layer_;
	cocos2d::ClippingRectangleNode * puzzle_clipping_node_;
	std::map<short ,cocos2d::Sprite*> cookies_sprite_container_;
	cocos2d::Rect puzzle_board_bounding_box_;
	cocos2d::Node* animation_node_;
};

#endif /* VIEWMANAGER_H_ */
