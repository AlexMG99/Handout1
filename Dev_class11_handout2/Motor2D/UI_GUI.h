#ifndef _UI_GUI_H_
#define _UI_GUI_H_

#include "j1Module.h"

enum UI_Type 
{
	LABEL = 0,
	SPRITE,
	BUTTON
};

class UI_GUI : public j1Module
{
public:
	UI_GUI() {};
	~UI_GUI() {};

protected:
	UI_Type			type;
	int				pos_x = 0;
	int				pos_y = 0;
	
};


#endif // !_UI_GUI_H_
