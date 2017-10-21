/*
 * Settings.h
 *
 *  @Created on: 26-Dec-2016
 *  @Author: ajay
 *  @FileName : Settings
 *  @brief : This is the settings class which can be added to any scene having common HUD elements. It adds the callbacks for
 *  the buttons
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "cocos2d.h"
#include "GameGlobal.h"
#include "cocos-ext.h"

class Settings : public cocos2d::Layer{
public:
	Settings();
	virtual ~Settings();

	virtual bool init();
	static cocos2d::Layer* Create();

	/* @function : SetTimer()
	 * @brief : Set and starts the Timer for the Game
	 */
	void SetTimer();

	/* @function : CreateHud(cocos2d::Layer* , SceneType)
	 * @param parent_layer is the parent layer to which contains the Settings layer
	 * @param scene_type is the type of scene for which settings is being created
	 * @brief : Creats the HUD depending on the scene being loaded
	 */
	void CreateHud(cocos2d::Layer* parent_layer , SceneType scene_type);

	/* @function : CreateButtons(cocos2d:Layer*)
	 * @param parent_layer is the parent_layer to which settings layer is added
	 * @brief : Creates the different buttons for the scene
	 */
	void CreateButtons(cocos2d::Layer* parent_layer);

	/* @function : CreatePlayButton(cocos2d:Layer*)
	 * @param parent_layer is the parent_layer to which settings layer is added
	 * @brief : Creates callback for play button and removes it from the parent and
	 * adds to the settings layer
	 */
	void CreatePlayButton(cocos2d::Layer* parent_layer);

	/* @function : CreateExitButton(cocos2d:Layer*)
	 * @param parent_layer is the parent_layer to which settings layer is added
	 * @brief : Creates callback for exit button and removes it from the parent and
	 * adds to the settings layer
	 */
	void CreateExitButton(cocos2d::Layer* parent_layer);

	/* @function : CreateResumeButtons(cocos2d:Layer*)
	 * @param parent_layer is the parent_layer to which settings layer is added
	 * @brief : Creates callback for resume button and removes it from the parent and
	 * adds to the settings layer
	 */
	void CreateResumeButtons(cocos2d::Layer* parent_layer);

	/* @function : CreateTimerLabel(cocos2d:Layer*)
	 * @param parent_layer is the parent_layer to which settings layer is added
	 * @brief : removes the label from parent_layer and adds is to the settings layer
	 */
	void CreateTimerLabel(cocos2d::Layer* parent_layer);

	/* @function : CreateHintButton(cocos2d:Layer*)
	 * @param parent_layer is the parent_layer to which settings layer is added
	 * @brief : Creates callback for hint button and removes it from the parent and
	 * adds to the settings layer
	 */
	void CreateHintButton(cocos2d::Layer* parent_layer);

	/* @function : CreateButtons(cocos2d:Layer*)
	 * @param sender is Node being passed along the callback
	 * @brief : Updates the timer
	 */
	void UpdateTimer(cocos2d::Node* sender);


	/*
	 *@ CallBacks
	 */

	void HintFadeOutCallBack(cocos2d::Node* sender);
	void ExitButtonCallBack(cocos2d::Ref* pSender, cocos2d::extension::Control::EventType rEvent);
	void MenuButtonCallBack(cocos2d::Ref* pSender,cocos2d::extension::Control::EventType rEvent);
	void HintButtonCallBack(cocos2d::Ref* pSender, cocos2d::extension::Control::EventType rEvent);

	/* @function : get_is_hint_on()
	 * @brief : get the value for var is_hint_on_
	 * @return : returns bool value for is_hint_on_
	 */
	bool get_is_hint_on() { return is_hint_on_;};

	CREATE_FUNC(Settings);

private :

	int secs_;
	int mins_;
	bool is_hint_on_;

	SceneType scene_type_;
	cocos2d::Label* timer_label_;
	cocos2d::extension::ControlButton* hint_btn_;
};

#endif /* SETTINGS_H_ */
