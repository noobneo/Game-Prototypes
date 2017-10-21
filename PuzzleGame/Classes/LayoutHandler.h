/*
 * LayoutHandler.h
 *
 *  @Created on: 26-Dec-2016
 *  @Author: ajay
 *  @fileName : LayoutHandler
 *  @brief : This class helps parse the the layout and then create each type of widget based on the what is found in the
 *  layout file and then adds it to the parent . Its a singleton class
 */


#pragma once

#ifndef LAYOUTHANDLER_H_
#define LAYOUTHANDLER_H_

#include "cocos2d.h"
#include "extensions/GUI/CCControlExtension/CCControlButton.h"


class LayoutHandler {
public:
	LayoutHandler();
	virtual ~LayoutHandler();

	/* @function : GetInstance()
	 * @brief : Returns instance of this class
	 */
	static LayoutHandler* GetInstance();

	/* @function : ParseAndAddLayout(std::string, cocos2d::Node* , bool , bool)
	 * param layout_name the name of the layout to be loaded
	 * @param layer is the parent to which object being created is to be added
	 * @param apply_scale is true or false based on if the scale need to be applied to the object being created
	 * @param converto_node_space is true or false based on if the position is needed to be converted to the node space
	 * @brief : This method reads the layout file and parses it
	 */
	void ParseAndAddLayout(std::string layout_name , cocos2d::Node* layer , bool apply_scale , bool converto_node_space = false);

private :

	/* @function : CreateSprite(std::string  ,float , float , int , cocos2d::Node*)
	 * param name is the name of the sprite to be created.
	 * @param x is x'cordinate position of the sprite.
	 * @param y is y'cordinate  position of the sprite.
	 * @param layer_no is zorder no for this sprite.
	 * @param layer is parent of the sprite to which it needs to be added.
	 * @brief : Creates the sprite sets its required property and then adds to the parent.
	 */
	void CreateSprite(std::string name , float x , float y , int layer_no , cocos2d::Node* layer);

	/* @function : CreateLabel(std::string  ,float , float , int , cocos2d::Node*)
	 * param name is the name of the label to be created.
	 * @param x is x'cordinate position of the label.
	 * @param y is y'cordinate  position of the label.
	 * @param layer_no is zorder no for this label.
	 * @param layer is parent of the label to which it needs to be added.
	 * @brief : Creates the label sets its required property and then adds to the parent.
	 */
	void CreateLabel(std::string name , float x , float y , int layer_no , cocos2d::Node* layer);

	/* @function : CreateButton(std::string  ,float , float , int , cocos2d::Node*)
	 * param name is the name of the button to be created.
	 * @param x is x'cordinate position of the button.
	 * @param y is y'cordinate  position of the button.
	 * @param layer_no is zorder no for this button.
	 * @param layer is parent of the button to which it needs to be added.
	 * @brief : Creates the button sets its required property and then adds to the parent.
	 */
	void CreateButton(std::string name , float x , float y , int layer_no , cocos2d::Node* layer , std::string button_name);

	static LayoutHandler* layout_handler_ref_;

	int btn_layer_;
	float x_scale_factor_;
	float y_scale_factor_;
	bool is_parent_selected_;

	std::string btn_name_;

	cocos2d::Vec2 btn_pos_;
	cocos2d::extension::ControlButton *button_;

};

#endif /* LAYOUTHANDLER_H_ */
