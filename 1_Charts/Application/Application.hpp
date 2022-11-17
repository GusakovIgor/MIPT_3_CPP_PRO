#ifndef APPLICATION_HPP
#define APPLICATION_HPP


#include <Math.hpp>
#include <Events.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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


class Application
{

private:

	bool m_running;

	int32_t m_width;
	int32_t m_height;

	SDL_Window*   m_window;
	SDL_Renderer* m_renderer;

	TTF_Font* m_font;

	queue <Event> events;


	void CreateWindow   (const char* windowname);
	void CreateRenderer ();
	void FontsInit 		(const char* fontname);

public:

	bool IsRunning () const;
	int32_t Width  () const;
	int32_t Height () const;

	 Application (const char* windowname, const char* fontname);
	~Application ();

	void ShowFPS () const;
	void CheckEvents ();
	bool PollEvent (Event* event);
	Point2f GetMouse () const;
	void Wait (float seconds) const;

	void RefreshScreen () const;
	void ClearScreen () const;


	void SetTextureMode (Texture* target) const;
	void SetWindowMode  () const;

	Texture* CreateTexture (int32_t width, int32_t height) const;
	Texture* LoadTexture (const char* image) const;

	void DrawTexture (Texture* texture, float start_x, float start_y, float end_x, float end_y) const;
	inline void DrawTexture (Texture* texture, const Point2f& lcorner, const Point2f& rcorner) const
	{
		DrawTexture (texture, lcorner.x, lcorner.y, rcorner.x, rcorner.y);
	}

	void DrawPoint (float point_x, float point_y, Colour colour) const;
	inline void DrawPoint (const Point2f& point, Colour colour) const
	{
		DrawPoint (point.x, point.y, colour);
	}

	void DrawText (const char* text, float start_x, float start_y, float end_x, float end_y, Colour colour) const;
	inline void DrawText (const char* text, const Point2f& lcorner, const Point2f& rcorner, Colour colour) const
	{
		DrawText (text, lcorner.x, lcorner.y, rcorner.x, rcorner.y, colour);
	}

	void DrawLine (float start_x, float start_y, float end_x, float end_y, Colour colour) const;
	inline void DrawLine (const Point2f& a, const Point2f& b, Colour colour) const
	{
		DrawLine (a.x, a.y, b.x, b.y, colour);
	}

	void DrawRect (float start_x, float start_y, float end_x, float end_y, Colour colour) const;
	inline void DrawRect (const Point2f& a, const Point2f& b, Colour colour) const
	{
		DrawRect (a.x, a.y, b.x, b.y, colour);
	}

	void DrawCircle (float centre_x, float centre_y, float radius, Colour colour) const;
	inline void DrawCircle (const Point2f& centre, float radius, Colour colour) const
	{
		DrawCircle (centre.x, centre.y, radius, colour);
	}

	void DrawRoundedRect (float start_x, float start_y, float end_x, float end_y, float radius, Colour colour) const;
	inline void DrawRoundedRect (const Point2f& a, const Point2f& b, float radius, Colour colour) const
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


#endif