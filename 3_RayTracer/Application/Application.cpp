#include <algorithm>
#include <ctime>
#include <cstdint>
#include "Application.hpp"



/*** Colour ***/

Colour::Colour ()
{
	red   = 0;
	green = 0;
	blue  = 0;
}

Colour::Colour (uint8_t init_red, uint8_t init_green, uint8_t init_blue, uint8_t init_alpha)
{
	red   = init_red;
	green = init_green;
	blue  = init_blue;
	alpha = init_alpha;
}

Colour::operator SDL_Color() const
{
	return {red, green, blue, alpha};
}

Colour operator* (const Colour& colour, double factor)
{
	uint8_t new_red   = static_cast<double> (colour.red)   * factor;
	uint8_t new_green = static_cast<double> (colour.green) * factor;
	uint8_t new_blue  = static_cast<double> (colour.blue)  * factor;
	uint8_t new_alpha = colour.alpha;

	return Colour (new_red, new_green, new_blue, new_alpha);
}


/*** Points ***/

Point2f::Point2f ()
{
	x = 0;
	y = 0;
}

Point2f::Point2f (float a, float b)
{
	x = a;
	y = b;
}

Point2f::operator SDL_FPoint() const
{
	return {x, y};
}



/*** Application ***/


/*** Members ***/

bool Application::IsRunning ()
{
	return Running;
}

int32_t Application::Width ()
{
	return width;
}

int32_t Application::Height ()
{
	return height;
}


/*** Initialization ***/

Application::Application (const char* windowname, const char* fontname)
{
	Running = true;

	SDL_Init (SDL_INIT_VIDEO);

	CreateWindow (windowname);

	CreateRenderer ();

	FontsInit (fontname);

	SetColour (Renderer, DefaultColour);

	SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

void Application::CreateWindow (const char* windowname)
{
	int32_t WindowFlags = 0;

	width  = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;

	Window = SDL_CreateWindow (windowname, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, WindowFlags);

	if (!Window)
	{
		printf ("\n\n\nFailed to create %d x %d window:\n%s\n\n", width, height, SDL_GetError());
		Running = false;

		return;
	}
}

void Application::CreateRenderer ()
{
	int32_t RendererFlags = 0;

	Renderer = SDL_CreateRenderer (Window, -1, RendererFlags);

	if (!Renderer)
	{
		printf ("\n\n\nFailed to create renderer:\n%s\n\n", SDL_GetError());
		Running = false;

		return;
	}

    SDL_RenderClear (Renderer);
}

void Application::FontsInit (const char* fontname)
{
	if (!TTF_WasInit() && TTF_Init() == -1)
	{
    	printf ("TTF_Init: %s\n", TTF_GetError());
    	Running = false;

    	return;
	}

	Font = TTF_OpenFont (fontname, 72);
}

Application::~Application ()
{
	if (Renderer)
	{
		SDL_DestroyRenderer (Renderer);
	}

	if (Window)
	{
		SDL_DestroyWindow (Window);
	}

	SDL_Quit ();
}


/*** Evenets ***/

void Application::ShowFPS ()
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

	SDL_SetWindowTitle (Window, title);
}

void Application::CheckEvents ()
{
	SDL_Event event;

	while (SDL_PollEvent (&event))
	{
		switch (event.type)
		{
			case SDL_MOUSEMOTION:		events.push (event);
										break;


			case SDL_MOUSEBUTTONDOWN:	events.push (event);
										return;


			case SDL_MOUSEBUTTONUP:		events.push (event);
										return;

			case SDL_QUIT:				Running = false;
										return;

			default:	break;
		}

	}
}

void Application::Wait (float seconds)
{
	int32_t m_seconds = (int32_t) (1000 * seconds);

	SDL_Delay (m_seconds);
}


/*** Screen Management ***/

void Application::RefreshScreen ()
{
	SDL_RenderPresent (Renderer);
}

void Application::ClearScreen ()
{
	SetColour (Renderer, DefaultColour);

	SDL_RenderClear (Renderer);
}


/*** Drawing ***/

Texture* Application::LoadTexture (const char* image)
{
	SDL_Surface *image_surface = SDL_LoadBMP(image);

	if (!image_surface)
	{
		printf ("Error, while loading image: %s\n", TTF_GetError ());

		return NULL;
	}

	Texture* image_texture = SDL_CreateTextureFromSurface (Renderer, image_surface);

	if (!image_texture)
	{
		printf ("Error, while loading image: %s\n", TTF_GetError ());

		return NULL;
	}

	SDL_FreeSurface (image_surface);

	return image_texture;
}

void Application::DrawTexture (Texture* texture, float start_x, float start_y, float end_x, float end_y)
{
	SDL_FRect target_location;
	target_location.x = start_x;
	target_location.w = end_x - start_x;
	target_location.y = (start_y < end_y) ? start_y : end_y;
	target_location.h = (start_y < end_y) ? end_y - start_y : start_y - end_y;

	SDL_RenderCopyF (Renderer, texture, NULL, &target_location);
}

void Application::DrawText (const char* text, float start_x, float start_y, float end_x, float end_y, Colour colour)
{
	SetColour (Renderer, colour);

	SDL_FRect target_location;
	target_location.x = start_x;
	target_location.w = end_x - start_x;
	target_location.y = (start_y < end_y) ? start_y : end_y;
	target_location.h = (start_y < end_y) ? end_y - start_y : start_y - end_y;


	SDL_Surface* text_surface = TTF_RenderText_Solid (Font, text, colour);

	if (!text_surface)
	{
		printf ("Error, while printing text: %s\n", TTF_GetError ());

		return;
	}


	Texture* text_texture = SDL_CreateTextureFromSurface (Renderer, text_surface);

	if (!text_texture)
	{
		printf ("Error, while printing text: %s\n", TTF_GetError ());

		return;
	}


	SDL_RenderCopyF (Renderer, text_texture, NULL, &target_location);

	SDL_FreeSurface (text_surface);
	SDL_DestroyTexture (text_texture);
}

void Application::DrawPoint (float point_x, float point_y, Colour colour)
{
	SetColour (Renderer, colour);

	SDL_RenderDrawPointF (Renderer, point_x, point_y);
}

void Application::DrawLine (float start_x, float start_y, float end_x, float end_y, Colour colour)
{
	SetColour (Renderer, colour);

	SDL_RenderDrawLineF (Renderer, start_x, start_y, end_x, end_y);
}

void Application::DrawRect (float start_x, float start_y, float end_x, float end_y, Colour colour)
{
	SetColour (Renderer, colour);

	SDL_FRect rectangle;
	rectangle.x = start_x;
	rectangle.w = end_x - start_x;
	rectangle.y = (start_y < end_y) ? start_y : end_y;
	rectangle.h = (start_y < end_y) ? end_y - start_y : start_y - end_y;

	const SDL_FRect* rect_ptr = &rectangle;

	SDL_RenderDrawRectF (Renderer, rect_ptr);
}

void Application::DrawCircle (float centre_x, float centre_y, float radius, Colour colour)
{
	SetColour (Renderer, colour);

	float x = radius;		// Starting with (r, 0) and going up
	float y = 0;

	float P = 1 - radius;

	// y can only increase
	// and x is decreasing till x < y
	// that way we making iterations for one eigths of dots

	while (x >= y)
	{
		SDL_RenderDrawPointF (Renderer, centre_x + x, centre_y + y);
		SDL_RenderDrawPointF (Renderer, centre_x + x, centre_y - y);
		SDL_RenderDrawPointF (Renderer, centre_x - x, centre_y + y);
		SDL_RenderDrawPointF (Renderer, centre_x - x, centre_y - y);

		SDL_RenderDrawPointF (Renderer, centre_x + y, centre_y + x);
		SDL_RenderDrawPointF (Renderer, centre_x + y, centre_y - x);
		SDL_RenderDrawPointF (Renderer, centre_x - y, centre_y + x);
		SDL_RenderDrawPointF (Renderer, centre_x - y, centre_y - x);

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

void Application::DrawRoundedRect (float start_x, float start_y, float end_x, float end_y, float radius, Colour colour)
{
	SetColour (Renderer, colour);

	float x = radius;		// Starting with (r, 0) and going up
	float y = 0;

	float P = 1 - radius;

	// y can only increase
	// and x is decreasing till x < y
	// that way we making iterations for one eigths of dots

	while (x >= y)
	{
		SDL_RenderDrawPointF (Renderer, end_x   - radius + x, end_y   - radius + y);
		SDL_RenderDrawPointF (Renderer, end_x   - radius + x, start_y + radius - y);
		SDL_RenderDrawPointF (Renderer, start_x + radius - x, end_y   - radius + y);
		SDL_RenderDrawPointF (Renderer, start_x + radius - x, start_y + radius - y);

		SDL_RenderDrawPointF (Renderer, end_x   - radius + y, end_y   - radius + x);
		SDL_RenderDrawPointF (Renderer, end_x   - radius + y, start_y + radius - x);
		SDL_RenderDrawPointF (Renderer, start_x + radius - y, end_y   - radius + x);
		SDL_RenderDrawPointF (Renderer, start_x + radius - y, start_y + radius - x);

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

	SDL_RenderDrawLineF (Renderer, start_x + radius, start_y, end_x - radius, start_y);
	SDL_RenderDrawLineF (Renderer, start_x + radius, end_y,   end_x - radius, end_y);

	SDL_RenderDrawLineF (Renderer, start_x, start_y + radius, start_x, end_y - radius);
	SDL_RenderDrawLineF (Renderer, end_x,   start_y + radius, end_x,   end_y - radius);
}

void SetColour (SDL_Renderer* Renderer, const Colour& colour)
{
	SDL_SetRenderDrawColor (Renderer, colour.red, colour.green, colour.blue, colour.alpha);
}