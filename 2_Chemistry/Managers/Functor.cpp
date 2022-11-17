#include "Functor.hpp"


/*** Functor ***/

Functor::Functor ()
{
	type = FunctorType::wrong_t;
}

Functor::Functor (FunctorType init_type)
{
	type = init_type;
}

FunctorType Functor::GetType ()
{
	return type;
}



/*** Add Molecule Functor ***/

AddAtom::AddAtom () : Functor (FunctorType::add_atom_t)
{
	AManager = NULL;

	basics = Elementaries (0, 0, 0);

	speed = Vector (0, 0);
}

AddAtom::AddAtom (AtomManager* init_manager, 
				  Elementaries init_basics, 
				  Vector 	   init_speed) : Functor (FunctorType::add_atom_t)
{
	AManager = init_manager;

	basics   = init_basics;

	speed    = init_speed;
}


void AddAtom::Act (Mouse* mouse)
{
	if (mouse->LeftClick ())
	{
		AManager->AddAtomRandomly (basics, speed);
	}
}

void AddAtom::Update () {}



/*** Increase Basics Functor ***/

IncreaseBasics::IncreaseBasics () : Functor (FunctorType::inc_basics_t)
{
	AddAtomFunctor = NULL;

	delta = Elementaries (0, 0, 0);
}

IncreaseBasics::IncreaseBasics (AddAtom* init_functor, Elementaries init_delta) : Functor (FunctorType::inc_basics_t)
{
	AddAtomFunctor = init_functor;

	delta = init_delta;
}


int IncreaseBasics::GetBasicNumber ()
{
	if (delta == proton)
	{
		return AddAtomFunctor->basics.protons;
	}
	else if (delta == electron)
	{
		return AddAtomFunctor->basics.electrons;
	}
	else if (delta == neutron)
	{
		return AddAtomFunctor->basics.neutrons;
	}

	return -1;
}

void IncreaseBasics::Act (Mouse* mouse)
{
	if (mouse->LeftClick ())
	{
		AddAtomFunctor->basics += delta;
	}
}

void IncreaseBasics::Update () {}



/*** Decrease Basics Functor ***/

DecreaseBasics::DecreaseBasics () : Functor (FunctorType::dec_basics_t)
{
	AddAtomFunctor = NULL;

	delta = Elementaries (0, 0, 0);
}

DecreaseBasics::DecreaseBasics (AddAtom* init_functor, Elementaries init_delta) : Functor (FunctorType::dec_basics_t)
{
	AddAtomFunctor = init_functor;

	delta = init_delta;
}


int DecreaseBasics::GetBasicNumber ()
{
	if (delta == proton)
	{
		return AddAtomFunctor->basics.protons;
	}
	else if (delta == electron)
	{
		return AddAtomFunctor->basics.electrons;
	}
	else if (delta == neutron)
	{
		return AddAtomFunctor->basics.neutrons;
	}

	return -1;
}

void DecreaseBasics::Act (Mouse* mouse)
{
	if (mouse->LeftClick ())
	{
		AddAtomFunctor->basics -= delta;
	}
}

void DecreaseBasics::Update () {}



/*** Increase Speed Functor ***/

IncreaseSpeed::IncreaseSpeed () : Functor (FunctorType::inc_speed_t)
{
	AddAtomFunctor = NULL;

	delta = Vector (0, 0);
}

IncreaseSpeed::IncreaseSpeed (AddAtom* init_functor, Vector init_delta) : Functor (FunctorType::inc_speed_t)
{
	AddAtomFunctor = init_functor;

	delta = init_delta;
}


int IncreaseSpeed::GetSpeedNumber ()
{
	if (delta == Vector (1, 0))
	{
		return AddAtomFunctor->speed.x;
	}
	else if (delta == Vector (0, 1))
	{
		return AddAtomFunctor->speed.y;
	}

	return 1000;
}

void IncreaseSpeed::Act (Mouse* mouse)
{
	if (mouse->LeftClick ())
	{
		AddAtomFunctor->speed += delta;
	}
}

void IncreaseSpeed::Update () {}



/*** Decrease Speed Functor ***/

DecreaseSpeed::DecreaseSpeed () : Functor (FunctorType::dec_speed_t)
{
	AddAtomFunctor = NULL;

	delta = Vector (0, 0);
}

DecreaseSpeed::DecreaseSpeed (AddAtom* init_functor, Vector init_delta) : Functor (FunctorType::dec_speed_t)
{
	AddAtomFunctor = init_functor;

	delta = init_delta;
}


int DecreaseSpeed::GetSpeedNumber ()
{
	if (delta == Vector (1, 0))
	{
		return AddAtomFunctor->speed.x;
	}
	else if (delta == Vector (0, 1))
	{
		return AddAtomFunctor->speed.y;
	}

	return 1000;
}

void DecreaseSpeed::Act (Mouse* mouse)
{
	if (mouse->LeftClick ())
	{
		AddAtomFunctor->speed -= delta;
	}
}

void DecreaseSpeed::Update () {}



/*** Heat Walls Functor ***/

HeatWalls::HeatWalls () : Functor (FunctorType::heat_walls_t)
{
	AManager = NULL;
	
	colour_delta = {0, 0, 0, 0};
	
	coef_delta = 0;

	on_button = false;
}

HeatWalls::HeatWalls (AtomManager* init_manager, 
		   			  Colour init_colour_delta,
		   			  float  init_coef_delta) : Functor (FunctorType::heat_walls_t)
{
	AManager = init_manager;
	
	colour_delta = init_colour_delta;
	
	coef_delta = init_coef_delta;
	
	on_button = false;
}

void HeatWalls::Act (Mouse* mouse)
{
	static Colour start_colour = AManager->window->colour;
	static int start_hit_coef  = AManager->window->hit_coef;

	if (mouse->RightClick ())
	{
		AManager->window->hit_coef = start_hit_coef;
		AManager->window->colour   = start_colour;
	}
	else
	{
		AManager->window->hit_coef += coef_delta;

		Colour win_colour = AManager->window->colour;

		if (win_colour.r - colour_delta.r >= 0)
		{
			win_colour.r -= colour_delta.r;
		}

		if (win_colour.g - colour_delta.g >= 0)
		{
			win_colour.g -= colour_delta.g;
		}
		
		if (win_colour.b - colour_delta.b >= 0)
		{
			win_colour.b -= colour_delta.b;
		}
		
		if (win_colour.a - colour_delta.a >= 0)
		{
			win_colour.a -= colour_delta.a;
		}

		AManager->window->colour = win_colour;
	}
}

void HeatWalls::Update ()
{
	static Colour start_colour = AManager->window->colour;
	static int start_hit_coef  = AManager->window->hit_coef;

	if (AManager->window->hit_coef > start_hit_coef)
	{
		AManager->window->hit_coef -= coef_delta;
	}
	
	Colour win_colour = AManager->window->colour;

	if (win_colour.r + colour_delta.r <= start_colour.r)
	{
		win_colour.r += colour_delta.r;
	}

	if (win_colour.g + colour_delta.g <= start_colour.g)
	{
		win_colour.g += colour_delta.g;
	}
	
	if (win_colour.b + colour_delta.b <= start_colour.b)
	{
		win_colour.b += colour_delta.b;
	}
	
	if (win_colour.a + colour_delta.a <= start_colour.a)
	{
		win_colour.a += colour_delta.a;
	}

	AManager->window->colour = win_colour;
}