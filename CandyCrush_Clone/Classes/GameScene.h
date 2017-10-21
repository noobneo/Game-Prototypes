/*
 * GameScene.h
 *
 *  @Created on: 9-jan-2017
 *  @Author: ajay
 *  @fileName : GameScene
 *  @brief :this the GameWorld Scene and the point where ViewManager and GameManager init takes place
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"

class GameScene : public cocos2d::Scene{
public:
	GameScene();
	virtual ~GameScene();

	/*
	 * @function : init()
	 * @brief: inits the Game. Inits ViewManager and GameManager
	 * @return : returns bool based on if the init was success or not.
	 */
	virtual bool init();

	/*
	 * @function : update()
	 * @param dt is the delta time
	 * @brief: Update game loop
	 */
	virtual void update(float dt);

	/* @function : ResetEnableTouch()
	 * @brief : Resets and Enables the touch again
	 */
	void ResetEnableTouch();

	/* @function : RegisterTouchListener()
	 * @brief : register the touch listener for this scene
	 */
	void RegisterTouchListener();


	/* @function : FillUpEmptySpaces()
	 * @brief : Calls GameManager's FillUpEmptySpaces method
	 */
	void FillUpEmptySpaces();


	/* @function : SwapCookieValue()
	 * @brief : Calls GameManagers SwapCookiesValueToEmptySpace;
	 */
	void SwapCookiesValueToEmptySpace();


	/* @function : IsValidMove()
	 * @brief : Asks GameManager if the Move played is valid or not
	 * @return : bool based on whether the move played is valid or not
	 */
	bool IsValidMove();

	/* @function : RemoveChain(std::set<short>& )
	 * @param chain_container is container for indices in the chain
	 * @brief : Asks GameManager to remove the Chain
	 */
	bool RemoveChain(std::set<short>& chain_container);

	/*
	 * @brief : touch methods
	 */
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);


	/* @function : Create()
	 * @brief : Creates the scene
	 * @return : returns the Scene created
	 */
    static Scene* Create();

	CREATE_FUNC(GameScene);

private:

	cocos2d::Layer* hud_layer_;
	bool touch_started_;
	bool touch_moved_;
	bool cookie_moved_;

};

#endif /* GAMESCENE_H_ */
