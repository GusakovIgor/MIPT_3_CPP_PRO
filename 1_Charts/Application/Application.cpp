#include <algorithm>
#include <ctime>
#include <cstdint>
#include <iostream>
#include "Application.hpp"


/*** Colour ***/

Colour::Colour () :
	red   (0),
	green (0),
	blue  (0),
	alpha (0)
{}

Colour::Colour (uint8_t init_red, uint8_t init_green, uint8_t init_blue, uint8_t init_alpha) :
	red   (init_red),
	green (init_green),
	blue  (init_blue),
	alpha (init_alpha)
{}

Colour::operator SDL_Color() const
{
	return {red, green, blue, alpha};
}



/*** Application ***/

bool Application::IsRunning () const
{
	return m_running;
}

int32_t Application::Width () const
{
	return m_width;
}

int32_t Application::Height () const
{
	return m_height;
}


Application::Application (const char* windowname, const char* fontname)
{
	m_running = true;

	SDL_Init (SDL_INIT_VIDEO);

	CreateWindow (windowname);

	CreateRenderer ();

	FontsInit (fontname);

	SetColour (m_renderer, DefaultColour);

	SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

void Application::CreateWindow (const char* windowname)
{
	int32_t window_flags = 0;

	m_width  = WINDOW_WIDTH;
	m_height = WINDOW_HEIGHT;

	m_window = SDL_CreateWindow (windowname, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, window_flags);

	if (!m_window)
	{
		printf ("\n\n\nFailed to create %d x %d m_window:\n%s\n\n", m_width, m_height, SDL_GetError());
		m_running = false;

		return;
	}
}

void Application::CreateRenderer ()
{
	int32_t renderer_flags = 0;

	m_renderer = SDL_CreateRenderer (m_window, -1, renderer_flags);

	if (!m_renderer)
	{
		printf ("\n\n\nFailed to create m_renderer:\n%s\n\n", SDL_GetError());
		m_running = false;

		return;
	}

    SDL_RenderClear (m_renderer);
}

void Application::FontsInit (const char* fontname)
{
	if (!TTF_WasInit() && TTF_Init() == -1)
	{
    	printf ("TTF_Init: %s\n", TTF_GetError());
    	m_running = false;

    	return;
	}

	m_font = TTF_OpenFont (fontname, 72);
}

Application::~Application ()
{
	if (m_renderer)
	{
		SDL_DestroyRenderer (m_renderer);
	}

	if (m_window)
	{
		SDL_DestroyWindow (m_window);
	}

	SDL_Quit ();
}


/*** Evenets ***/

void Application::ShowFPS () const
{
	static clock_t prev_time = clock ();

	clock_t time = clock ();

	double drawing_time = ((double) (time - prev_time)) / CLOCKS_PER_SEC;

	double fps = 1.0 / drawing_time;

	prev_time = time;


	char title[MAX_TITLE_SIZE];

	if (fps <= 1.0)
	{
		snprintf (title, MAX_TITLE_SIZE, "FPS: %.3f", fps);
	}
	else
	{
		snprintf (title, MAX_TITLE_SIZE, "FPS: %.2f", fps);
	}

	SDL_SetWindowTitle (m_window, title);
}

void Application::CheckEvents ()
{
	SDL_Event event;

	while (SDL_PollEvent (&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:				m_running = false;
										return;

			case SDL_MOUSEWHEEL:		events.push (Event (event));
										break;

			case SDL_MOUSEMOTION:		events.push (Event (event));
										break;

			default:	break;
		}

	}
}

bool Application::PollEvent (Event* event)
{
	if (events.size () == 0)
	{
		return false;
	}

	*event = events.front ();

	events.pop ();

	return true;
}

Point2f Application::GetMouse () const
{
	int x = 0;
	int y = 0;

	SDL_GetMouseState (&x, &y);

	return Point2f (x, y);
}

void Application::Wait (float seconds) const
{
	int32_t m_seconds = (int32_t) (1000 * seconds);

	SDL_Delay (m_seconds);
}


/*** Screen Management ***/

void Application::RefreshScreen () const
{
	SDL_RenderPresent (m_renderer);
}

void Application::ClearScreen () const
{
	SetColour (m_renderer, DefaultColour);

	SDL_RenderClear (m_renderer);
}


/*** Drawing ***/


void Application::SetTextureMode (Texture* target) const
{
	SDL_SetRenderTarget (m_renderer, target);
}

void Application::SetWindowMode () const
{
	SDL_SetRenderTarget (m_renderer, NULL);
}

Texture* Application::CreateTexture (int32_t m_width, int32_t m_height) const
{
	return SDL_CreateTexture (m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
}

Texture* Application::LoadTexture (const char* image) const
{
	SDL_Surface *image_surface = SDL_LoadBMP(image);

	if (!image_surface)
	{
		printf ("Error, while loading image: %s\n", TTF_GetError ());

		return NULL;
	}

	Texture* image_texture = SDL_CreateTextureFromSurface (m_renderer, image_surface);

	if (!image_texture)
	{
		printf ("Error, while loading image: %s\n", TTF_GetError ());

		return NULL;
	}

	SDL_FreeSurface (image_surface);

	return image_texture;
}

void Application::DrawTexture (Texture* texture, float start_x, float start_y, float end_x, float end_y) const
{
	SDL_FRect target_location;
	target_location.x = start_x;
	target_location.w = end_x - start_x;
	target_location.y = (start_y < end_y) ? start_y : end_y;
	target_location.h = (start_y < end_y) ? end_y - start_y : start_y - end_y;

	SDL_RenderCopyF (m_renderer, texture, NULL, &target_location);
}

void Application::DrawText (const char* text, float start_x, float start_y, float end_x, float end_y, Colour colour) const
{
	SetColour (m_renderer, colour);

	SDL_FRect target_location;
	target_location.x = start_x;
	target_location.w = end_x - start_x;
	target_location.y = (start_y < end_y) ? start_y : end_y;
	target_location.h = (start_y < end_y) ? end_y - start_y : start_y - end_y;


	SDL_Surface* text_surface = TTF_RenderText_Solid (m_font, text, colour);

	if (!text_surface)
	{
		printf ("Error, while printing text: %s\n", TTF_GetError ());

		return;
	}


	Texture* text_texture = SDL_CreateTextureFromSurface (m_renderer, text_surface);

	if (!text_texture)
	{
		printf ("Error, while printing text: %s\n", TTF_GetError ());

		return;
	}


	SDL_RenderCopyF (m_renderer, text_texture, NULL, &target_location);

	SDL_FreeSurface (text_surface);
	SDL_DestroyTexture (text_texture);
}

void Application::DrawPoint (float point_x, float point_y, Colour colour) const
{
	SetColour (m_renderer, colour);

	SDL_RenderDrawPointF (m_renderer, point_x, point_y);
}

void Application::DrawLine (float start_x, float start_y, float end_x, float end_y, Colour colour) const
{
	SetColour (m_renderer, colour);

	SDL_RenderDrawLineF (m_renderer, start_x, start_y, end_x, end_y);
}

void Application::DrawRect (float start_x, float start_y, float end_x, float end_y, Colour colour) const
{
	SetColour (m_renderer, colour);

	SDL_FRect rectangle;
	rectangle.x = start_x;
	rectangle.w = end_x - start_x;
	rectangle.y = (start_y < end_y) ? start_y : end_y;
	rectangle.h = (start_y < end_y) ? end_y - start_y : start_y - end_y;

	const SDL_FRect* rect_ptr = &rectangle;

	SDL_RenderDrawRectF (m_renderer, rect_ptr);
}

void Application::DrawCircle (float centre_x, float centre_y, float radius, Colour colour) const
{
	SetColour (m_renderer, colour);

	float x = radius;		// Starting with (r, 0) and going up
	float y = 0;

	float P = 1 - radius;

	// y can only increase
	// and x is decreasing till x < y
	// that way we making iterations for one eigths of dots

	while (x >= y)
	{
		SDL_RenderDrawPointF (m_renderer, centre_x + x, centre_y + y);
		SDL_RenderDrawPointF (m_renderer, centre_x + x, centre_y - y);
		SDL_RenderDrawPointF (m_renderer, centre_x - x, centre_y + y);
		SDL_RenderDrawPointF (m_renderer, centre_x - x, centre_y - y);

		SDL_RenderDrawPointF (m_renderer, centre_x + y, centre_y + x);
		SDL_RenderDrawPointF (m_renderer, centre_x + y, centre_y - x);
		SDL_RenderDrawPointF (m_renderer, centre_x - y, centre_y + x);
		SDL_RenderDrawPointF (m_renderer, centre_x - y, centre_y - x);

		if (P <= 0)
		{
			P += 2*y + 1;
		}
		else
		{
			x--;

			P+= 2*y - 2*x + 1;
		}

		y++;
	}
}

void Application::DrawRoundedRect (float start_x, float start_y, float end_x, float end_y, float radius, Colour colour) const
{
	SetColour (m_renderer, colour);

	float x = radius;		// Starting with (r, 0) and going up
	float y = 0;

	float P = 1 - radius;

	// y can only increase
	// and x is decreasing till x < y
	// that way we making iterations for one eigths of dots

	while (x >= y)
	{
		SDL_RenderDrawPointF (m_renderer, end_x   - radius + x, end_y   - radius + y);
		SDL_RenderDrawPointF (m_renderer, end_x   - radius + x, start_y + radius - y);
		SDL_RenderDrawPointF (m_renderer, start_x + radius - x, end_y   - radius + y);
		SDL_RenderDrawPointF (m_renderer, start_x + radius - x, start_y + radius - y);

		SDL_RenderDrawPointF (m_renderer, end_x   - radius + y, end_y   - radius + x);
		SDL_RenderDrawPointF (m_renderer, end_x   - radius + y, start_y + radius - x);
		SDL_RenderDrawPointF (m_renderer, start_x + radius - y, end_y   - radius + x);
		SDL_RenderDrawPointF (m_renderer, start_x + radius - y, start_y + radius - x);

		if (P <= 0)
		{
			P += 2*y + 1;
		}
		else
		{
			x--;

			P+= 2*y - 2*x + 1;
		}

		y++;
	}

	SDL_RenderDrawLineF (m_renderer, start_x + radius, start_y, end_x - radius, start_y);
	SDL_RenderDrawLineF (m_renderer, start_x + radius, end_y,   end_x - radius, end_y);

	SDL_RenderDrawLineF (m_renderer, start_x, start_y + radius, start_x, end_y - radius);
	SDL_RenderDrawLineF (m_renderer, end_x,   start_y + radius, end_x,   end_y - radius);
}

void SetColour (SDL_Renderer* m_renderer, const Colour& colour)
{
	SDL_SetRenderDrawColor (m_renderer, colour.red, colour.green, colour.blue, colour.alpha);
}