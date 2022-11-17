#include <cstdint>
#include <Math.hpp>
#include "Events.hpp"


Event::Event ()
{}

Event::Event (const SDL_Event& init_base) :
	base (init_base)
{}