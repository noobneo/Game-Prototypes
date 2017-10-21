/*
 * OpeningScene.h
 *
 *  Created on: 26-Dec-2016
 *      Author: ajay
 */

#pragma once

#ifndef OPENINGSCENE_H_
#define OPENINGSCENE_H_

#include "cocos2d.h"
#include "Settings.h"

class OpeningScene : public cocos2d::Scene{
public:
	OpeningScene();
	virtual ~OpeningScene();

	virtual bool init();

	static cocos2d::Scene* Create();

	CREATE_FUNC(OpeningScene);

private :
	cocos2d::Layer *hud_layer_;
	Settings* settings_layer_;
};

#endif /* OPENINGSCENE_H_ */
