/*
 * OpeningScene.h
 *
 *  Created on: 9-jan-2017
 *      Author: ajay
 */

#pragma once

#ifndef OPENINGSCENE_H_
#define OPENINGSCENE_H_

#include "cocos2d.h"

class OpeningScene : public cocos2d::Scene{
public:
	OpeningScene();
	virtual ~OpeningScene();

	virtual bool init();

	static cocos2d::Scene* Create();

	void PlayButtonCallBack(cocos2d::Ref* sender);
	void ExitButtonCallBack(cocos2d::Ref* sender);

	CREATE_FUNC(OpeningScene);

};

#endif /* OPENINGSCENE_H_ */
