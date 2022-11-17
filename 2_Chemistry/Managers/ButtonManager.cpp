#include "ButtonManager.hpp"


ButtonManager::ButtonManager ()
{
	num_button_types = 0;

	textures = NULL;
}

ButtonManager::ButtonManager (Application* App, const char* config_file)
{
	textures = new Texture* [MAX_NUM_BUTTONS];
	
	GetTexturesFromConfig (App, config_file);
}

ButtonManager::~ButtonManager ()
{
	while (!buttons.Empty ())
	{
		Button* button = buttons.PopFront ();
		
		delete button;
	}

	for (int i = 0; i < num_button_types; i++)
	{
		SDL_DestroyTexture (textures[i]);
	}

	delete textures;
}

void ButtonManager::AddButton (Button* button)
{
	FunctorType init_type = button->functor->GetType ();

	int functor_num = static_cast<int> (init_type);

	button->texture = textures[functor_num];


	buttons.PushFront (button);


	if (init_type == FunctorType::add_atom_t)
	{
		Shape* sub_shape = NULL;

		AddAtom* parent_functor = dynamic_cast <AddAtom*> (button->functor);

		sub_shape = GetSubRectangle (button->shape, 2, 3, 1, 3);
		AddButton (new IncBasicsButton (new IncreaseBasics (parent_functor, Elementaries (1, 0, 0)), sub_shape));
		sub_shape = GetSubRectangle (button->shape, 2, 3, 1, 3);
		AddButton (new DecBasicsButton (new DecreaseBasics (parent_functor, Elementaries (1, 0, 0)), sub_shape));
		
		sub_shape = GetSubRectangle (button->shape, 2, 3, 2, 3);
		AddButton (new IncBasicsButton (new IncreaseBasics (parent_functor, Elementaries (0, 1, 0)), sub_shape));
		sub_shape = GetSubRectangle (button->shape, 2, 3, 2, 3);
		AddButton (new DecBasicsButton (new DecreaseBasics (parent_functor, Elementaries (0, 1, 0)), sub_shape));

		sub_shape = GetSubRectangle (button->shape, 2, 3, 3, 3);
		AddButton (new IncBasicsButton (new IncreaseBasics (parent_functor, Elementaries (0, 0, 1)), sub_shape));
		sub_shape = GetSubRectangle (button->shape, 2, 3, 3, 3);
		AddButton (new DecBasicsButton (new DecreaseBasics (parent_functor, Elementaries (0, 0, 1)), sub_shape));

		sub_shape = GetSubRectangle (button->shape, 3, 3, 1, 2);
		AddButton (new IncSpeedButton (new IncreaseSpeed (parent_functor, Vector (1, 0)), sub_shape));
		sub_shape = GetSubRectangle (button->shape, 3, 3, 1, 2);
		AddButton (new DecSpeedButton (new DecreaseSpeed (parent_functor, Vector (1, 0)), sub_shape));

		sub_shape = GetSubRectangle (button->shape, 3, 3, 2, 2);
		AddButton (new IncSpeedButton (new IncreaseSpeed (parent_functor, Vector (0, 1)), sub_shape));
		sub_shape = GetSubRectangle (button->shape, 3, 3, 2, 2);
		AddButton (new DecSpeedButton (new DecreaseSpeed (parent_functor, Vector (0, 1)), sub_shape));
	}
}



void ButtonManager::DrawButtons (Application* App)
{
	for (auto button = buttons.Begin(); button != buttons.End(); ++button)
	{
		(*button)->Draw (App);
	}
}


void ButtonManager::UpdateButtons (Mouse* mouse)
{
	for (auto button = buttons.Begin(); button != buttons.End(); ++button)
	{
		if (!(*button)->Contains (mouse->location))
		{
			(*button)->Update ();
		}
	}
}


void ButtonManager::CheckClicks (Mouse* mouse)
{
	for (auto button = buttons.Begin(); button != buttons.End(); ++button)
	{
		if ((*button)->Contains (mouse->location))
		{
			(*button)->Act (mouse);
			break;
		}
	}
}


Rectangle* GetSubRectangle (Shape* init_shape, int line,   int num_lines,
											   int figure, int num_figures)
{
	static int prev_line   = 0;
	static int prev_figure = 0;
	bool again = false;

	if (line == prev_line && figure == prev_figure)
	{
		again = true;
	}
	else
	{
		prev_line   = line;
		prev_figure = figure;
	}


	float left  = init_shape->left_border  ();
	float right = init_shape->right_border ();
	float up    = init_shape->up_border    ();
	float down  = init_shape->down_border  ();

	float width  = right - left;
	float height = down  - up;

	float new_height = 2.5 * height / (num_lines * 3.5 + 1);
	float new_width  = 1.5 * new_height / 2;

	float h_space = (width  - num_figures * new_width) / 15;
	float v_space = new_height / 2.5;


	float x_shift = 5 * h_space + (figure - 1) * (new_width  + 4 * h_space);
	float y_shift =     v_space + (line   - 1) * (new_height +     v_space);

	if (num_figures == 2)
	{
		x_shift += 2 * h_space;
	}

	if (again)
	{
		y_shift += new_height / 2;
	}

	return new Rectangle (Point (left + x_shift, up + y_shift), Point (left + x_shift + new_width, up + y_shift + new_height / 2), init_shape->GetColour ());
}


void ButtonManager::GetTexturesFromConfig (Application* App, const char* config_file)
{
	char* button = new char [255];
	char* path   = new char [255];

	FILE* config = fopen (config_file, "r");

	fscanf (config, "%d ", &num_button_types);

	for (int i = 0; i < num_button_types; i++)
	{
		textures[i] = NULL;
	}

	for (int i = 0; i < num_button_types; i++)
	{
		fscanf (config, "%s : \"%[^\"]\"", button, path);

		if (strcmp (button, "AddMolecule") == 0)
		{
			textures[static_cast<int> (FunctorType::add_atom_t)]   = GetTextureFromPath (App, path); 
		}
		else if (strcmp (button, "IncreaseBasics") == 0)
		{
			textures[static_cast<int> (FunctorType::inc_basics_t)] = GetTextureFromPath (App, path); 
		}
		else if (strcmp (button, "DecreaseBasics") == 0)
		{
			textures[static_cast<int> (FunctorType::dec_basics_t)] = GetTextureFromPath (App, path); 
		}
		else if (strcmp (button, "IncreaseSpeed") == 0)
		{
			textures[static_cast<int> (FunctorType::inc_speed_t)]  = GetTextureFromPath (App, path); 
		}
		else if (strcmp (button, "DecreaseSpeed") == 0)
		{
			textures[static_cast<int> (FunctorType::dec_speed_t)]  = GetTextureFromPath (App, path); 
		}
		else if (strcmp (button, "HeatWalls") == 0)
		{
			textures[static_cast<int> (FunctorType::heat_walls_t)] = GetTextureFromPath (App, path); 
		}
		else
		{
			printf ("Wrong format in config file \"%s\":\n", config_file);
			printf ("%s : \"%s\"\n", button, path);
			assert (!"right format");
		}
	}

	delete button;
	delete path;
}


Texture* ButtonManager::GetTextureFromPath (Application* App, const char* path)
{
	if (strcmp (path, "No texture") != 0)
	{
		return App->LoadTexture (path);
	}

	return NULL;
}