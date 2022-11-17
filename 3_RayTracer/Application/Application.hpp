#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Events/Events.hpp"

#include <queue>
using std::queue;
typedef SDL_Texture Texture;


class Colour
{

public:

	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;

	Colour ();
	Colour (uint8_t init_red, uint8_t init_green, uint8_t init_blue, uint8_t init_alpha = SDL_ALPHA_OPAQUE);

	operator SDL_Color() const;
};

Colour operator* (const Colour& colour, double factor);


class Point2f
{

public:

	float x;
	float y;

	Point2f ();
	Point2f (float a, float b);

	operator SDL_FPoint() const;
};



class Application
{

private:

	bool Running;

	int32_t width;
	int32_t height;

	SDL_Window*   Window;
	SDL_Renderer* Renderer;
	TTF_Font* 	  Font;

	queue <AppEvent> events;


public:

	/*** Members ***/

	bool IsRunning ();

	int32_t Width  ();
	int32_t Height ();


	/*** Construction ***/

	 Application (const char* windowname, const char* fontname);
	~Application ();

	void CreateWindow   (const char* windowname);
	void CreateRenderer ();
	void FontsInit 		(const char* fontname);


	/*** Events ***/

	void ShowFPS ();

	void CheckEvents ();

	void Wait (float seconds);


	/*** Screen Management ***/

	void RefreshScreen ();

	void ClearScreen ();



	/*** Drawing ***/

	Texture* LoadTexture (const char* image);


	void DrawTexture (Texture* texture, float start_x, float start_y, float end_x, float end_y);

	inline void DrawTexture (Texture* texture, const Point2f& lcorner, const Point2f& rcorner)
	{
		DrawTexture (texture, lcorner.x, lcorner.y, rcorner.x, rcorner.y);
	}


	void DrawPoint (float point_x, float point_y, Colour colour);

	inline void DrawPoint (const Point2f& point, Colour colour)
	{
		DrawPoint (point.x, point.y, colour);
	}


	void DrawText (const char* text, float start_x, float start_y, float end_x, float end_y, Colour colour);

	inline void DrawText (const char* text, const Point2f& lcorner, const Point2f& rcorner, Colour colour)
	{
		DrawText (text, lcorner.x, lcorner.y, rcorner.x, rcorner.y, colour);
	}


	void DrawLine (float start_x, float start_y, float end_x, float end_y, Colour colour);

	inline void DrawLine (const Point2f& a, const Point2f& b, Colour colour)
	{
		DrawLine (a.x, a.y, b.x, b.y, colour);
	}


	void DrawRect (float start_x, float start_y, float end_x, float end_y, Colour colour);

	inline void DrawRect (const Point2f& a, const Point2f& b, Colour colour)
	{
		DrawRect (a.x, a.y, b.x, b.y, colour);
	}


	void DrawCircle (float centre_x, float centre_y, float radius, Colour colour);

	inline void DrawCircle (const Point2f& centre, float radius, Colour colour)
	{
		DrawCircle (centre.x, centre.y, radius, colour);
	}


	void DrawRoundedRect (float start_x, float start_y, float end_x, float end_y, float radius, Colour colour);

	inline void DrawRoundedRect (const Point2f& a, const Point2f& b, float radius, Colour colour)
	{
		DrawRoundedRect (a.x, a.y, b.x, b.y, radius, colour);
	}
};



const int32_t MAX_TITLE_SIZE = 20;

const int32_t WINDOW_WIDTH  = 1920;
const int32_t WINDOW_HEIGHT = 1080;

#include "Colours.hpp"

const Colour DefaultColour = Black;




void SetColour (SDL_Renderer* Renderer, const Colour& colour);

uint32_t GetClick (float* mouse_x, float* mouse_y);

bool IsLeft (uint32_t buttons_mask);


#endif