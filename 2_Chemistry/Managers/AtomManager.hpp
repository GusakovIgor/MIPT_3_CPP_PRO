#ifndef ATOM_MANAGER_HPP
#define ATOM_MANAGER_HPP

#include "List/ListBase.hpp"
#include "List/List.hpp"
#include "../Elems/Atoms.hpp"

class HeatWalls;


class PeriodicTable
{

private:

	int num_atoms;

	char** AtomNames;

	Elementaries* AtomInfo;


public:

	 PeriodicTable (const char* filename);

	~PeriodicTable ();

	Elementaries GetClosest (const Elementaries& basics);

	char* GetName (const Elementaries& basics);

	bool Contains (const Elementaries& basics);
};


Elementaries operator+ (const Elementaries& left, const Elementaries& right);

bool operator== (const Elementaries& left, const Elementaries& right);






class AtomManager
{

private:

	Borders* window;

	List <Atom*> atoms;

	PeriodicTable* table;


	void CheckBorders ();

	bool BlowAtoms ();

	bool SpliceAtoms ();

	void UpdateLifetimes ();

	void ResolveCollisionAtoms (Atom* atom_first, Atom* atom_second);
	
	void SplitAtom (Atom* wrong_atom);

public:

	 AtomManager (Borders* init_window, PeriodicTable* init_table);

	~AtomManager ();


	void AddAtomRandomly (Elementaries basics, Vector speed);

	void AddAtomIn (Point appear_centre, Elementaries basics, Vector speed);

	void MoveAtoms   ();

	void UpdateAtoms ();	

	void DrawAtoms (Application* App);

	friend class HeatWalls;
};


char** 		  NameTableAlloc (int num_atoms);

Elementaries* InfoTableAlloc (int num_atoms);


void NameTableDelete (int num_atoms, char** AtomNames);

void InfoTableDelete (Elementaries* AtomInfo);

void ParsePeriodicTable (FILE* table, int num_lines, char** AtomNames, Elementaries* AtomInfo);


float CountPrettyDelta (float R, float r);

Vector SplitSomeSpeed (int m, int M, Atom* wrong_atom);



const int MAX_LIFETIME = 200;



#endif