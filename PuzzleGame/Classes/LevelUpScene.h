/*
 * LevelUpScene.h
 *
 *  @Created on: 28-Dec-2016
*   @Author: ajay
*   @fileName : LevelUpScene
 */

#ifndef LEVELUPSCENE_H_
#define LEVELUPSCENE_H_

#include "cocos2d.h"

class LevelUpScene  : public cocos2d::Scene{
public:
	LevelUpScene();
	virtual ~LevelUpScene();

	void ChangeSceneToGame(cocos2d::Node* sender);

	static cocos2d::Scene* Create();
	virtual bool init();

	CREATE_FUNC(LevelUpScene);


};

#endif /* LEVELUPSCENE_H_ */
