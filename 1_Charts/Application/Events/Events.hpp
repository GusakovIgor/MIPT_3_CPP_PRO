#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SDL2/SDL.h>


enum events
{
	APP_MOUSEMOTION = SDL_MOUSEMOTION,
	APP_MOUSEWHEEL  = SDL_MOUSEWHEEL
};

enum mouse_buttons
{
	APP_LEFTBUTTON  = SDL_BUTTON_LMASK,
	APP_RIGHTBUTTON = SDL_BUTTON_RMASK,
};



struct Event
{

public:

	SDL_Event base;

	Event ();
	explicit Event (const SDL_Event& init_base);
};


#endif //EVENTS_HPP