/*

 * GameSceneHandler.h
 *
 *  @Created on: 26-Dec-2016
 *	@Author: ajay
 *	@FileName : GameSceneManager
 *	@brief : This is a singleton class which manages the changing of the scenes for the game
 */

#pragma once

#ifndef GAMESCENEMANAGER_H_
#define GAMESCENEMANAGER_H_

class GameSceneManager {
public:
	GameSceneManager();
	virtual ~GameSceneManager();

	/* @function : GetInstance()
	 * @brief : Creates the instance for the GameSceneManager if called for the first time else returns already
	 * created instance
	 * @return : returns the instance of the GameSceneManager
	 */
	static GameSceneManager* GetInstance();

	/* @function : GoToOpeningScene()
	 * @brief : Changes the scene to OpeningScene.
	 */
	void GoToOpeningScene();

	/* @function : GoToOpeningScene()
	 * @brief : Changes the scene to OpeningScene.
	 */
	void GoToGameScene();

	/* @function : GoToOpeningScene()
	 * @brief : The scene on levelup and this increments the levelno and
	 * changes scene again to GameScene.
	 */
	void GoToLevelUpScene();

private:

	static GameSceneManager* game_scene_manager_ref_;
	float scene_transition_time_;
};

#endif /* GAMESCENEMANAGER_H_ */
