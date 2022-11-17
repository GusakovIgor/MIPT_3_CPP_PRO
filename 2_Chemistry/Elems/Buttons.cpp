#include "Buttons.hpp"


Button::Button ()
{
	functor = NULL;

	shape = NULL;

	texture = NULL;
}

Button::Button (Functor* init_functor, Shape* init_shape)
{
	functor = init_functor;

	shape = init_shape;

	texture = NULL;
}

void Button::Draw (Application* App)
{
	if (texture && shape)
	{
		float left  = shape->left_border  ();
		float right = shape->right_border ();
		float up    = shape->up_border    ();
		float down  = shape->down_border  ();

		App->DrawTexture (texture, Point (left, up), Point (right, down));
	}
	else if (shape)
	{
		shape->Draw (App);
	}
}

void Button::Act (Mouse* mouse)
{
	if (functor)
	{
		functor->Act (mouse);
	}
}

void Button::Update ()
{
	if (functor)
	{
		functor->Update ();
	}
}

bool Button::Contains (Point location)
{
	if (shape)
	{
		return shape->Contains (location);
	}

	return false;
}



/*** Add Atom Button***/

AddAtomButton::AddAtomButton () :
					  Button ()
{

}

AddAtomButton::AddAtomButton (AddAtom* init_functor, Shape* init_shape) :
					  Button (         init_functor,        init_shape)
{

}

void AddAtomButton::Draw (Application* App)
{
	Button::Draw (App);

	int len = strlen ("Add Atom");
	int num_lines = 3;

	float left  = shape->left_border  ();
	float right = shape->right_border ();
	float up    = shape->up_border    ();
	float down  = shape->down_border  ();

	float width  = right - left;
	float height = down  - up;


	float new_height = 2.5 * height / (num_lines * 3.5 + 1);
	float new_width  = 0.5 * new_height;

	float x_shift = (width  - len * new_width) / 2;
	float y_shift = new_height / 5;

	App->DrawText ("Add Atom",
				   Point (left + x_shift,                   up + y_shift             ),
				   Point (left + x_shift + len * new_width, up + y_shift + new_height + new_height / 2.5),
				   shape->GetColour ());
}



/*** Increase Basics Button ***/

IncBasicsButton::IncBasicsButton () :
						  Button ()
{

}

IncBasicsButton::IncBasicsButton (IncreaseBasics* init_functor, Shape* init_shape) :
					  	  Button (                init_functor,        init_shape)
{

}

void IncBasicsButton::Draw (Application* App)
{
	Button::Draw (App);


	char* number = new char [5];

	IncreaseBasics* inc_basics_functor = dynamic_cast <IncreaseBasics*> (functor);

	int num = inc_basics_functor->GetBasicNumber ();

	sprintf (number, "%3d", num);


	float left  = shape->left_border  ();
	float right = shape->right_border ();
	float up    = shape->up_border    ();
	float down  = shape->down_border  ();

	float width  = right - left;
	float height = down  - up;

	float new_height = 2 * height;
	float new_width  = 2 * width;

	App->DrawText (number,
				   Point (left - new_width, up             ),
				   Point (left            , up + new_height),
				   shape->GetColour ());

	delete number;
}


/*** Decrease Basics Button ***/

DecBasicsButton::DecBasicsButton () :
						  Button ()
{

}

DecBasicsButton::DecBasicsButton (DecreaseBasics* init_functor, Shape* init_shape) :
					  	  Button (                init_functor,        init_shape)
{

}

void DecBasicsButton::Draw (Application* App)
{
	Button::Draw (App);
}



/*** Increase Speed Button ***/

IncSpeedButton::IncSpeedButton () :
						Button ()
{

}

IncSpeedButton::IncSpeedButton (IncreaseSpeed* init_functor, Shape* init_shape) :
					  	Button (               init_functor,        init_shape)
{

}

void IncSpeedButton::Draw (Application* App)
{
	Button::Draw (App);


	char* number = new char [5];

	IncreaseSpeed* inc_speed_functor = dynamic_cast <IncreaseSpeed*> (functor);

	int num = inc_speed_functor->GetSpeedNumber ();

	sprintf (number, "%2d", num);


	float left  = shape->left_border  ();
	float right = shape->right_border ();
	float up    = shape->up_border    ();
	float down  = shape->down_border  ();

	float width  = right - left;
	float height = down  - up;

	float new_height = 2 * height;
	float new_width  = 4 * width / 3;

	App->DrawText (number,
				   Point (left - new_width, up             ),
				   Point (left            , up + new_height),
				   shape->GetColour ());

	delete number;
}


/*** Decrease Speed Button ***/

DecSpeedButton::DecSpeedButton () :
						Button ()
{

}

DecSpeedButton::DecSpeedButton (DecreaseSpeed* init_functor, Shape* init_shape) :
					  	Button (               init_functor,        init_shape)
{

}

void DecSpeedButton::Draw (Application* App)
{
	Button::Draw (App);
}



/*** Heat Walls Button ***/

HeatWallsButton::HeatWallsButton () :
						  Button ()
{

}

HeatWallsButton::HeatWallsButton (HeatWalls* init_functor, Shape* init_shape) :
					  	  Button (           init_functor,        init_shape)
{

}


void HeatWallsButton::Draw (Application* App)
{
	Button::Draw (App);

	shape->DrawLabel (App, "Heat Walls");
}