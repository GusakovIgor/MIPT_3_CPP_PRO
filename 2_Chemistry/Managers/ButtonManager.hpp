#ifndef BUTTON_MANAGER_HPP
#define BUTTON_MANAGER_HPP


#include "../Elems/Buttons.hpp"


class ButtonManager
{

private:

	int num_button_types;

	Texture** textures;

	List <Button*> buttons;


	void     GetTexturesFromConfig (Application* App, const char* config_file);

	Texture* GetTextureFromPath    (Application* App, const char* path);


public:

	 ButtonManager ();

	 ButtonManager (Application* App, const char* config_file);

	~ButtonManager ();


	void AddButton (Button* button);

	void DrawButtons (Application* App);

	void UpdateButtons (Mouse* mouse);

	void CheckClicks   (Mouse* mouse);
};


Rectangle* GetSubRectangle (Shape* init_shape, int line,   int num_lines,
											   int figure, int num_figures);

Texture* GetTexture (Application* App, const char* path);


const int MAX_NUM_BUTTONS = 255;



#endif