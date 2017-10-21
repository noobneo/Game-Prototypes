/*
 * GameScene.h
 *
 *  @Created on: 26-Dec-2016
 * 	@Author: ajay
 * 	@fileName : GameScene
 * 	@brief : this the GameWorld Scene and the point where ViewManager and GameManager init takes place
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

	/* @function : RegisterTouchListener()
	 * @brief : register the touch listener for this scene
	 */
	void RegisterTouchListener();

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

	bool touch_started_;

};

#endif /* GAMESCENE_H_ */
