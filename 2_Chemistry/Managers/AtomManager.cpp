#include <ctime>

#include "AtomManager.hpp"



/*** Periodic Table ***/

PeriodicTable::PeriodicTable (const char* filename)
{
	FILE* table = fopen (filename, "r");

	fscanf (table, "%d ", &num_atoms);

	AtomNames = NameTableAlloc (num_atoms);

	AtomInfo = InfoTableAlloc (num_atoms);

	ParsePeriodicTable (table, num_atoms, AtomNames, AtomInfo);

	fclose (table);
}

PeriodicTable::~PeriodicTable ()
{
	NameTableDelete (num_atoms, AtomNames);

	InfoTableDelete (AtomInfo);
}


Elementaries PeriodicTable::GetClosest (const Elementaries& basics)
{
	Elementaries closest = basics;

	closest.protons   = (closest.protons   > closest.electrons) ? closest.electrons : closest.protons;
	closest.electrons = (closest.electrons > closest.protons  ) ? closest.protons   : closest.electrons;

	while (closest.protons > num_atoms || AtomInfo[closest.protons].neutrons > closest.neutrons)
	{
		closest.protons--;
		closest.electrons--;
	}

	while (closest.neutrons > AtomInfo[closest.protons].neutrons)
	{
		closest.neutrons--;
	}

	return closest;
}

char* PeriodicTable::GetName (const Elementaries& basics)
{
	char* name = (char*) calloc (10, sizeof (char));
	
	if (basics == proton)
	{
		strcpy (name, "p");
		return name;
	}
	else if (basics == electron)
	{
		strcpy (name, "e");
		return name;
	}
	else if (basics == neutron)
	{
		strcpy (name, "n");
		return name;
	}
	
	if (basics.protons <= num_atoms)
	{
		if (AtomInfo[basics.protons] == basics)
		{
			strcpy (name, AtomNames[basics.protons]);
			return name;
		}
	}

	strcpy (name, "Obscure");

	return name;
}


bool PeriodicTable::Contains (const Elementaries& basics)
{
	if (basics.protons > num_atoms)
	{
		return false;
	}

	return (AtomInfo[basics.protons] == basics || basics == proton || basics == electron || basics == neutron);
}



/*** Periodic table members stuff ***/

char** NameTableAlloc (int num_atoms)
{
	char** AtomNames = (char**) calloc (num_atoms + 1, sizeof (char*));

	for (int i = 0; i < num_atoms + 1; i++)
	{
		AtomNames[i] = (char*) calloc (5, sizeof (char));
	}

	return AtomNames;
}

Elementaries* InfoTableAlloc (int num_atoms)
{
	return (Elementaries*) calloc (num_atoms + 1, sizeof (Elementaries));
}


void NameTableDelete (int num_atoms, char** AtomNames)
{
	for (int i = 0; i < num_atoms + 1; i++)
	{
		free (AtomNames[i]);
	}

	free (AtomNames);
}

void InfoTableDelete (Elementaries* AtomInfo)
{
	free (AtomInfo);
}


void ParsePeriodicTable (FILE* table, int num_lines, char** AtomNames, Elementaries* AtomInfo)
{
	char* name = (char*) calloc (5, sizeof (char));

	for (int i = 0; i < num_lines; i++)
	{
		int number = 0;

		fscanf (table, "%d ", &number);
		fscanf (table, "%s %d %d %d ", AtomNames[number], &AtomInfo[number].neutrons, &AtomInfo[number].protons, &AtomInfo[number].electrons);
			
		printf ("%d: ", number);
		printf ("%s %d %d %d\n", AtomNames[number], AtomInfo[number].neutrons, AtomInfo[number].protons, AtomInfo[number].electrons);
	}
}




/*** Atoms Manager ***/

AtomManager::AtomManager (Borders* init_window, PeriodicTable* init_table)
{
	srand (time(NULL));

	window = init_window;

	table = init_table;
}

AtomManager::~AtomManager ()
{
	delete table;

	while (!atoms.Empty ())
	{
		Atom* atom = atoms.PopFront ();
		
		delete atom;
	}
}


void AtomManager::AddAtomRandomly (Elementaries basics, Vector speed)
{
	char* name = table->GetName (basics);

	atoms.PushBack (new Atom (window, name, basics, speed));

	delete name;
}

void AtomManager::AddAtomIn (Point appear_centre, Elementaries basics, Vector speed)
{
	char* name = table->GetName (basics);

	atoms.PushBack (new Atom (appear_centre, name, basics, speed));

	delete name;
}




void AtomManager::MoveAtoms ()
{
	for (auto atom = atoms.Begin(); atom != atoms.End(); ++atom)
	{		
		(*atom)->Replace ();
	}
}


void AtomManager::UpdateAtoms ()
{
	CheckBorders ();

	while (BlowAtoms ()) {}

	while (SpliceAtoms ()) {}

	UpdateLifetimes ();
}

void AtomManager::CheckBorders ()
{
	for (auto atom = atoms.Begin(); atom != atoms.End(); ++atom)
	{
		(*atom)->CheckCollisionBorders (window);
	}
}

bool AtomManager::BlowAtoms ()
{
	for (auto atom_it = atoms.Begin(); atom_it != atoms.End(); ++atom_it)
	{
		Atom* atom = *atom_it;

		if (!table->Contains (atom->GetBasics ()) && atom->Lifetime () > MAX_LIFETIME)
		{
			SplitAtom (atom);
			atom_it = atoms.Remove (atom_it);

			CheckBorders ();

			return true;
		}
	}

	return false;
}

bool AtomManager::SpliceAtoms ()
{
	for (auto first_it = atoms.Begin(); first_it != atoms.End(); ++first_it)
	{
		for (auto second_it = first_it; second_it != atoms.End(); ++second_it)
		{
			if (first_it != second_it)
			{
				Atom* first  = *first_it;
				Atom* second = *second_it;

				if (CheckCollisionAtoms (first, second))
				{
					ResolveCollisionAtoms (first, second);

					first_it  = atoms.Remove (first_it);
					second_it = atoms.Remove (second_it);
					
					return true;
				}
			}
		}
	}

	return false;
}

void AtomManager::UpdateLifetimes ()
{
	for (auto atom = atoms.Begin(); atom != atoms.End(); ++atom)
	{		
		(*atom)->UpdateLifetime ();
	}
}

void AtomManager::ResolveCollisionAtoms (Atom* atom_first, Atom* atom_second)
{
	Elementaries basics_first  = atom_first->GetBasics ();
	Elementaries basics_second = atom_second->GetBasics ();

	Vector speed_first  = atom_first->GetSpeed ();
	Vector speed_second = atom_second->GetSpeed ();


	Point appear_centre;
	Vector appear_speed;

	float m = basics_first.Weight ();
	float M = basics_second.Weight ();

	if (m > M)
	{
		appear_centre = atom_first->GetCentre ();
	}
	else
	{
		appear_centre = atom_second->GetCentre ();
	}
	
	appear_speed = Vector ((m * speed_first.x + M * speed_second.x) / (m + M), (m * speed_first.y + M * speed_second.y) / (m + M));

	AddAtomIn (appear_centre, basics_first + basics_second, appear_speed);
}


void AtomManager::DrawAtoms (Application* App)
{
	for (int i = 0; i < BORDERS_WIDTH; i++)
	{
		App->DrawRect (Point (window->left + i, window->up + i), Point (window->right + i, window->down + i), window->colour);
	}

	for (auto atom = atoms.Begin(); atom != atoms.End(); ++atom)
	{
		(*atom)->Draw (App);
	}
}




void AtomManager::SplitAtom (Atom* wrong_atom)
{
	Elementaries wrong_basics = wrong_atom->GetBasics ();
	Elementaries correct_basics = table->GetClosest (wrong_basics);

	float r = BASE_SIZE;
	float R = 1.5 * correct_basics.Weight () + 2 * BASE_SIZE;

	float pi    = acos (-1);
	float angle = 0;
	float delta = CountPrettyDelta (R, r);


	Vector speed = wrong_atom->GetSpeed ();

	Point centre = wrong_atom->GetCentre ();
	

	int protons = wrong_basics.protons - correct_basics.protons;

	Vector p_speed = SplitSomeSpeed (protons, wrong_basics.Weight(), wrong_atom);

	while (protons)
	{
		--protons;

		AddAtomIn (Point (centre.x + R * cos (angle), centre.y + R * sin (-angle)) , Elementaries (1, 0, 0), Vector (p_speed.x * cos (angle), p_speed.y * sin (-angle)));

		angle += delta;
		
		if (angle + delta > 2 * pi)
		{
			R += 3 * BASE_SIZE;
			angle = 0;
			delta = CountPrettyDelta (R, r);
		}
	}

	wrong_basics.protons = correct_basics.protons;



	int electrons = wrong_basics.electrons - correct_basics.electrons;

	Vector e_speed = SplitSomeSpeed (electrons, wrong_basics.Weight(), wrong_atom);

	while (electrons)
	{
		--electrons;

		AddAtomIn (Point (centre.x + R * cos (angle), centre.y + R * sin (-angle)) , Elementaries (0, 1, 0), Vector (e_speed.x * cos (angle), e_speed.y * sin (-angle)));
		
		angle += delta;

		if (angle + delta > 2 * pi)
		{
			R += 3 * BASE_SIZE;
			angle = 0;
			delta = CountPrettyDelta (R, r);
		}
	}

	wrong_basics.electrons = correct_basics.electrons;



	int neutrons = wrong_basics.neutrons - correct_basics.neutrons;

	Vector n_speed = SplitSomeSpeed (neutrons, wrong_basics.Weight(), wrong_atom);

	while (neutrons)
	{
		--neutrons;

		AddAtomIn (Point (centre.x + R * cos (angle), centre.y + R * sin (-angle)) , Elementaries (0, 0, 1), Vector (n_speed.x * cos (angle), n_speed.y * sin (-angle)));

		angle += delta;

		if (angle + delta > 2 * pi)
		{
			R += 3 * BASE_SIZE;
			angle = 0;
			delta = CountPrettyDelta (R, r);
		}
	}

	wrong_basics.neutrons = correct_basics.neutrons;


	if (correct_basics.Exist ())
	{
		AddAtomIn (centre, correct_basics, wrong_atom->GetSpeed ());
	}
}


float CountPrettyDelta (float R, float r)
{
	// 1 circle's size is 2 * asin (r / R)
	// So delta will be 1,5 size of circle (0.5 circle's size free space between circles)

	float delta = 3 * asin (r / R);
	
	// Then we want to get rid of unused space in th end of circle

	float pi = acos (-1);

	int num_elementaries = (int) (2 * pi / delta);
	
	delta = 2 * pi / num_elementaries - 0.01;


	return delta;
}


Vector SplitSomeSpeed (int m, int M, Atom* wrong_atom)
{
	float mass_k = (float) m / (float) M;

	float k = 0.0;


	Vector old_speed = wrong_atom->GetSpeed ();
	
	k = sqrt (1 - mass_k);

	Vector new_speed  = Vector (old_speed.x * k, old_speed.y * k);

	k = sqrt (2 - mass_k);

	Vector elem_speed = Vector (old_speed.x * k, old_speed.y * k);
	

	wrong_atom->SetSpeed (new_speed);

	return elem_speed;
}