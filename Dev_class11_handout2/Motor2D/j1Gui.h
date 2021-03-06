#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "SDL\include\SDL.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	j1Gui* CreateLabel(int x, int y, SDL_Color color, const char* text);

	virtual void Draw() {};

	const SDL_Texture* GetAtlas() const;

private:
	p2SString		atlas_file_name;
	SDL_Texture*	atlas;
};

#endif // __j1GUI_H__