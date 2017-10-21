/*
 * ViewManager.h
 *
 *  @Created on: 26-Dec-2016
 *  @Author: ajay
 *  @fileName : ViewManager
 *  @brief :It is a singleton class. this is the view manager of the game , it creates the game layer , is responsible for the view part of the game.
 *
 */

#ifndef VIEWMANAGER_H_
#define VIEWMANAGER_H_

#include "cocos2d.h"
#include "GameGlobal.h"

class Settings;

class ViewManager {
public:
	ViewManager();
	virtual ~ViewManager();

	/* @function : Clear()
	 * @brief : It clears all the containers and also calls for the Clear method for the GameManager
	 */
	void Clear();

	/* @function : CreateGameLayer()
	 * @brief : It creates the game layer and asks LayoutHandler to parse the layout for the game scene.
	 */
	void CreateGameLayer();

	/* @function : CreatePuzzleLayer()
	 * @brief : It creates the puzzle layer and adds it to the parent scene.
	 */
	void CreatePuzzleLayer();

	/* @function : CreateSettingsLayer()
	 * @brief : It creates the setting layer and adds it to the parent scene.
	 */
	void CreateSettingsLayer();

	/* @function : CreatePuzzlePieces()
	 * @brief : It creates the puzzle peices from the sprite and add them to puzzle board layer.
	 */
	void CreatePuzzlePieces();

	/* @function : ShufflePuzzle()
	 * @brief : Shuffles the puzzle pieces randomly.
	 */
	void ShufflePuzzle();

	/* @function : ResetMoveVars()
	 * @brief : Resets the vars and containers after the puzzles pieces are done moving.
	 */
	void ResetMoveVars();

	/* @function : AddWrapAroundImages()
	 * @brief : It creates the puzzle peices from the sprite and add them to puzzle board layer.
	 */
	void AddWrapAroundImages();

	/* @function : ResetMoveRelatedInfo()
	 * @brief : It creates the puzzle peices from the sprite and add them to puzzle board layer.
	 */
	void ResetMoveRelatedInfo();

	/* @function : MovePuzzleVertically()
	 * @brief : Moves the puzzle pieces vertically.
	 */
	void MovePuzzleVertically();

	/* @function : MovePuzzleHorizontally()
	 * @brief : Moves the puzzle pieces horizontally.
	 */
	void MovePuzzleHorizontally();

	/* @function : SelectPuzzlePiecesToBeMoved()
	 * @brief : Selects the puzzles pieces that are needed to be moved after touch end.
	 */
	void SelectPuzzlePiecesToBeMoved();

	/* @function : Init(cocos2d::Scene)
	 * @param game_scene this the scene where view_layer is added and from the Init is called
	 * @brief : this inits the creation of game and settings layer and stores the ref to the game_scene
	 */
	void Init(cocos2d::Scene* game_scene);

	/* @function : LoadLevel(short)
	 * @param level_no is the level number to be loaded.
	 * @brief : this method calls the createpuzzle and shufflepuzzle
	 */
	void LoadLevel(short level_no);

	/* @function : ResetIsMoving(short)
	 * @param level_no is the level number to be loaded.
	 * @brief : this method calls the createpuzzle and shufflepuzzle
	 */
	void ResetIsMoving(cocos2d::Node* sender);

	/* @function : onTouchBegan(cocos2d::Touch*)
	 * @param touch is the touch related information.
	 * @brief : When the user begin touch. this method is called.
	 */
	void onTouchBegan(cocos2d::Touch* touch);

	/* @function : onTouchMoved(cocos2d::Touch*)
	 * @param touch is the touch related information.
	 * @brief : When the user is moving the touch. this method is called.
	 */
    	void onTouchMoved(cocos2d::Touch* touch);

	/* @function : onTouchEnded(cocos2d::Touch*)
	 * @param touch is the touch related information.
	 * @brief : When the user ends the touch. this method is called.
	 */
    	void onTouchEnded(cocos2d::Touch* touch);

	/* @function : MovePuzzle(cocos2d::Touch*)
	 * @param touch is the touch related information.
	 * @brief : Moves the puzzle pieces based on the touch
	 */
    	void MovePuzzle(cocos2d::Touch* touch);

	/* @function : CheckSwipeDirection(cocos2d::Touch*)
	 * @param touch is the touch related information.
	 * @brief : It checks the swipe direction based on the touch
	 */
   	 void CheckSwipeDirection(cocos2d::Touch* touch);

	/* @function : LoadLevel(short)
	 * @param touch_ended is the bool which the method if the touch is ended
	 * @brief : Repositions the puzzles pieces according to their position
	 * based on if the touch is ended or not
	 */
	void RepositionPuzzlePieces(bool touch_ended);

	/* @function : UpdatePuzzleBoardState(int,int)
	 * @param index of the puzzle _board_state .
	 * @param tag is the new value for the index
	 * @brief : this method calls the UpdatePuzzleBoardState of GameManager
	 */
	void UpdatePuzzleBoardState(int index , int tag);

	/* @function : PuzzlePieceClicked(cocos2d::Vec2)
	 * @param position is the coordinates  where player touched the screen.
	 * @brief : Checks which puzzle pieces was clicked
	 */
    	void PuzzlePieceClicked(cocos2d::Vec2 position);

	/* @function : RemoveOutOfBoundPieces(cocos2d::Node* , cocos2d::Node* , bool )
	 * @param sender is sender of this callback.
	 * @param spr is puzzle piece
	 * @param is_inside is the bool which tells if the piece is inside the puzzle layer or not
	 * @brief : This method removes spr(puzzle piece) for which is_inside is not true.
	 */
    	void RemoveOutOfBoundPieces(cocos2d::Node* sender , cocos2d::Node* spr , bool is_inside);
//    void RemoveOutOfBoundColPieces(cocos2d::Node* sender , cocos2d::Node* spr,bool is_inside);

	/* @function : RePositionRowPiecesOnTouchEnd(std::vector<cocos2d::Node*>)
	 * @param puzzlepiece_container is the container which has pieces being moved.
	 * @brief : Repositions the Row pieces on touch end
	 */
	void RePositionRowPiecesOnTouchEnd(std::vector<cocos2d::Node*> puzzlepiece_container );

	/* @function : RePositionColPiecesOnTouchEnd(std::vector<cocos2d::Node*>)
	 * @param puzzlepiece_container is the container which has pieces being moved.
	 * @brief : Repositions the col pieces on touch end
	 */
	void RePositionColPiecesOnTouchEnd(std::vector<cocos2d::Node*> puzzlepiece_container );

	/* @function : WrapThePiecesAroundTheHorizontalBounds(std::vector<cocos2d::Node*> , float , float)
	 * @param puzzlepiece_container is the container which has wrap around pieces being moved.
	 * @param bound is the max bound for the pieces of this particular container
	 * @param position_offset is the offset with which pieces need to be placed
	 * @brief : It wrap the pieces pieces around the puzzle clipping area. once they go out from left screen bound then it is wraped around
	 * to right side and vice-versa.
	 */
    	void WrapThePiecesAroundTheHorizontalBounds(std::vector<cocos2d::Node*> puzzlepiece_container , float bound , float position_offset);

    /* @function : WrapThePiecesAroundTheVerticalBounds(std::vector<cocos2d::Node*> , float , float)
	 * @param puzzlepiece_container is the container which has wrap around pieces being moved.
	 * @param bound is the max bound for the pieces of this particular container
	 * @param position_offset is the offset with which pieces need to be placed
	 * @brief : It wrap the pieces pieces around the puzzle clipping area. once they go out from top screen bound then it is wraped around
	 * to bottom side and vice-versa.
	 */
	 void WrapThePiecesAroundTheVerticalBounds(std::vector<cocos2d::Node*> puzzlepiece_container , float bound , float position_offset);

	/* @function : RowBoundaryCheck(float , float , int , cocos2d::Node*)
	 * @param final_x it the final x position of the sprite
	 * @param final_y it the final y position of the sprite
	 * @param tag is the tag of the sprite
	 * @param spr is the puzzle piece for which horizontal boundary check is to be done
	 * @brief : Checks if the puzzle piece is moved out of the horizontal boundary
	 * @return : returns true or false based on the check
	 */
   	 bool RowBoundaryCheck(float final_x , float final_y , int tag , cocos2d::Node* spr);

    /* @function : ColBoundaryCheck(float , float , int , cocos2d::Node*)
	 * @param final_x it the final x position of the sprite
	 * @param final_y it the final y position of the sprite
	 * @param tag is the tag of the sprite
	 * @param spr is the puzzle piece for which vertical boundary check is to be done
	 * @brief : Checks if the puzzle piece is moved out of the vertical boundary
	 * @return : returns true or false based on the check
	 */
   	 bool ColBoundaryCheck(float final_x , float final_y , int tag , cocos2d::Node* spr);

    /*
     * @MenuButton Callback
     */
	void MenuButtonCallBack(cocos2d::Ref* pSender);


	/* @function : getters
	 * @brief :  These are the getters for the variables of the Class ViewManager
	 */
	void set_is_moving(bool is_moving) { is_moving_ = is_moving;};
	void set_hint_btn_pos(cocos2d::Vec2 hint_btn_pos) { hint_btn_pos_ = hint_btn_pos;};
	void set_puzzle_frame_position(cocos2d::Vec2 puzzle_frame_position) { puzzle_frame_position_ =  puzzle_frame_position;};

	/* @function : getters
	 * @brief :  These are the getters for the variables of the Class ViewManager
	 */
	cocos2d::Vec2 get_hint_btn_pos() { return hint_btn_pos_;};

	/* @function : GetInstance()
	 * @brief : Creates the instance for the ViewManager if called for the first time else returns already
	 * created instance
	 * @return : returns the instance of the ViewManager
	 */
	static ViewManager* GetInstance();

private:

	static ViewManager* view_manager_ref_;

	short selected_row_;
	short selected_col_;
	int directions_[TOTAL_DIRECTION];
	bool is_moving_;
	bool is_animating_;
	bool is_direction_selected_;
	bool is_horizontal_swipe_;
	bool is_vertical_swipe_;
	float puzzle_sprite_width_;
	float puzzle_sprite_height_;
	float piece_height_;
	float piece_width_;
	float offset_;
	float time_delay_;

	std::vector<cocos2d::Vec2> initial_position_;
	std::vector<cocos2d::Node*> moving_piece_container_;
	std::vector<cocos2d::Node*> right_wraparound_piece_container_;
	std::vector<cocos2d::Node*> left_wraparound_piece_container_;
	std::vector<cocos2d::Node*> top_wraparound_piece_container_;
	std::vector<cocos2d::Node*> bottom_wraparound_piece_container_;
	std::map<int , cocos2d::Node*> puzzle_piece_container_;

	cocos2d::Scene* game_scene_;
	cocos2d::Layer* game_layer_;
	cocos2d::ClippingRectangleNode * puzzle_board_layer_;
	cocos2d::Vec2 puzzle_frame_position_;
	cocos2d::Vec2 hint_btn_pos_;
	Settings * settings_layer_;
};

#endif /* VIEWMANAGER_H_ */
