#ifndef _UI_SPRITE_H_
#define _UI_SPRITE_H_

#include "p2Defs.h"
#include "UI_GUI.h"

class UI_Sprite : public UI_GUI
{
public:
	UI_Sprite();
	~UI_Sprite() {};

	void Draw() const;


private:
	//SDL_Rect sprite_rect;
	
};


#endif // !_UI_SPRITE_H_

