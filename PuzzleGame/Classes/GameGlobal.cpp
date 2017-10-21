/*
 * GameGlobal.cpp
 *
 *  Created on: 26-Dec-2016
 *      Author: ajay
 */

#include "GameGlobal.h"
#include "cocos2d.h"

GameGlobal* GameGlobal::game_global_ref_ = nullptr;

GameGlobal::GameGlobal() {
	// TODO Auto-generated constructor stub

}

GameGlobal::~GameGlobal() {
	// TODO Auto-generated destructor stub
}


GameGlobal* GameGlobal::GetInstance() {

	if(!game_global_ref_) {

		game_global_ref_ = new GameGlobal();
	}

	return game_global_ref_;

}


void GameGlobal::LoadPlistFiles() {

	GAMELOG("Inside LoadPlistFiles");
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(cocos2d::FileUtils::getInstance()->fullPathForFilename("gameworld-HD.plist"));
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(cocos2d::FileUtils::getInstance()->fullPathForFilename("level_01-HD.plist"));
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(cocos2d::FileUtils::getInstance()->fullPathForFilename("level_02-HD.plist"));
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(cocos2d::FileUtils::getInstance()->fullPathForFilename("level_03-HD.plist"));
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(cocos2d::FileUtils::getInstance()->fullPathForFilename("level_04-HD.plist"));
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(cocos2d::FileUtils::getInstance()->fullPathForFilename("level_05-HD.plist"));
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(cocos2d::FileUtils::getInstance()->fullPathForFilename("level_06-HD.plist"));
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(cocos2d::FileUtils::getInstance()->fullPathForFilename("level_07-HD.plist"));
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(cocos2d::FileUtils::getInstance()->fullPathForFilename("level_08-HD.plist"));
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(cocos2d::FileUtils::getInstance()->fullPathForFilename("opening-HD.plist"));
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(cocos2d::FileUtils::getInstance()->fullPathForFilename("ui-HD.plist"));
	GAMELOG("leaving LoadPlistFiles");

}


void GameGlobal::GetRowColFromIndex( short& indx , short& col , short& row) {

	row = indx/COLS;
	col = indx - (COLS *row) ;

	GAMELOG("This is the index respect to new board %d" , indx);
	GAMELOG("Col : %d , Row : %d" , col , row);
}

short  GameGlobal::GetIndexFromRowCol(short& col , short& row) {

	short index = col + (row* COLS);
	return index;
}
