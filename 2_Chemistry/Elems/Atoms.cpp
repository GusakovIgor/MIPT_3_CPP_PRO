#include "Atoms.hpp"



/*** Vector ***/

Vector::Vector (float v_x, float v_y)
{
	x = v_x;
	y = v_y;
}


Vector operator+ (const Vector& left, const Vector& right)
{
	return Vector (left.x + right.x, left.y + right.y);
}

Vector operator- (const Vector& left, const Vector& right)
{
	return Vector (left.x - right.x, left.y - right.y);
}

Vector operator+= (Vector& left, const Vector& right)
{
	left = left + right;

	return left;
}

Vector operator-= (Vector& left, const Vector& right)
{
	left = left - right;

	return left;
}

bool operator== (const Vector& left, const Vector& right)
{
	return (left.x == right.x) &&
		   (left.y == right.y);
}



/*** Elementaries ***/

Elementaries::Elementaries (int init_p, int init_e, int init_n)
{
	protons   = init_p;
	electrons = init_e;
	neutrons  = init_n;
}


bool Elementaries::Exist ()
{
	return (protons   != 0) ||
		   (electrons != 0) ||
		   (neutrons  != 0);
}

int Elementaries::Weight ()
{
	return protons + electrons + neutrons;
}


Elementaries operator+ (const Elementaries& left, const Elementaries& right)
{
	return Elementaries (left.protons   + right.protons,
						 left.electrons + right.electrons,
						 left.neutrons  + right.neutrons);
}

Elementaries operator- (const Elementaries& left, const Elementaries& right)
{
	return Elementaries (left.protons   - right.protons,
						 left.electrons - right.electrons,
						 left.neutrons  - right.neutrons);
}

Elementaries operator+= (Elementaries& left, const Elementaries& right)
{
	left = left + right;

	return left;
}

Elementaries operator-= (Elementaries& left, const Elementaries& right)
{
	left = left - right;
	
	return left;
}

bool operator== (const Elementaries& left, const Elementaries& right)
{
	return (left.protons   == right.protons  ) &&
		   (left.electrons == right.electrons) &&
		   (left.neutrons  == right.neutrons );
}



/*** Atom ***/

// Constructor for adding Atom in random place

Atom::Atom (Borders* window, char* init_name, Elementaries init_basics, Vector init_speed)
{
	name = (char*) calloc (10, sizeof (char));

	strcpy (name, init_name);
	

	lifetime = 0;

	basics = init_basics;
	
	speed  = init_speed;


	int weight = basics.Weight ();

	float rand_x = window->left + weight + BASE_SIZE + rand () % (window->right - 2 * (weight + BASE_SIZE));
	float rand_y = window->up   + weight + BASE_SIZE + rand () % (window->down  - 2 * (weight + BASE_SIZE));

	if (weight < 40)
	{
		shape = new Circle (Point (rand_x, rand_y), weight + BASE_SIZE, Orange);
	}
	else
	{
		shape = new Rectangle (Point (rand_x, rand_y), Point (rand_x + weight + BASE_SIZE, rand_y + weight + BASE_SIZE), White);
	}
}

// Constructor for adding Atom near some place

Atom::Atom (Point appear_centre, char* init_name, Elementaries init_basics, Vector init_speed)
{
	name = (char*) calloc (10, sizeof (char));

	strcpy (name, init_name);


	lifetime = 0;

	basics = init_basics;
	
	speed  = init_speed;

	int weight = basics.protons + basics.neutrons;

	if (weight < 40)
	{
		shape = new Circle (Point (appear_centre.x, appear_centre.y), weight + BASE_SIZE, Orange);
	}
	else
	{
		int side = weight + BASE_SIZE;

		shape = new Rectangle (Point (appear_centre.x - side / 2, appear_centre.y - side / 2), Point (appear_centre.x + side / 2, appear_centre.y + side / 2), White);
	}
}


Atom::~Atom ()
{
	delete shape;

	free (name);
}


int Atom::Lifetime ()
{
	return lifetime;
}

void Atom::UpdateLifetime ()
{
	lifetime++;
}


Vector Atom::GetSpeed ()
{
	return speed;
}

void Atom::SetSpeed (Vector new_speed)
{
	speed = new_speed;
}


Elementaries Atom::GetBasics ()
{
	return basics;
}

Point Atom::GetCentre ()
{
	return Point ((shape->left_border () + shape->right_border ()) / 2.0,
				  (shape->down_border () + shape->up_border ()   ) / 2.0);
}


void Atom::Draw (Application* App)
{
	shape->Draw (App);
	shape->DrawLabel (App, name);
}

void Atom::Replace ()
{
	shape->Replace (speed.x, speed.y);
}


void Atom::CheckCollisionBorders (Borders* window)
{
	float hit_coef = window->hit_coef;
	
	if (shape->left_border () <= window->left)
	{
		speed = Vector (-speed.x * hit_coef, speed.y * hit_coef);

		shape->Replace (window->left - shape->left_border (), 0);
	}

	if (shape->right_border () >= window->right)
	{
		speed = Vector (-speed.x * hit_coef, speed.y * hit_coef);

		shape->Replace (window->right - shape->right_border (), 0);
	}


	if (shape->up_border () <= window->up)
	{
		speed = Vector (speed.x * hit_coef, -speed.y * hit_coef);
		
		shape->Replace (0, window->up - shape->up_border ());
	}

	if (shape->down_border () >= window->down)
	{
		speed = Vector (speed.x * hit_coef, -speed.y * hit_coef);

		shape->Replace (0, window->down - shape->down_border ());
	}
}



/*** Checks whether atoms intersects ***/

bool CheckCollisionAtoms (Atom* atom_first, Atom* atom_second)
{
	Shape* first  = atom_first->shape;
	Shape* second = atom_second->shape;

	typedef bool (*collision_check) (Shape* first, Shape* second);

	const static collision_check										// Might be not efficient, cause casts every call
	check_table[2][2] = {{CheckCollisionCC, CheckCollisionCR},
						 {CheckCollisionRC, CheckCollisionRR}};

	int type_1 = static_cast <int> ( first->GetType ());
	int type_2 = static_cast <int> (second->GetType ());

	return (check_table[type_1][type_2])(first, second);
}