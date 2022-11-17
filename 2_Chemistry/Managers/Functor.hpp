#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP


#include "AtomManager.hpp"


enum class FunctorType
{
	wrong_t      = -1,
	
	add_atom_t   =  0,
	
	inc_basics_t =  1,
	dec_basics_t =  2,
	
	inc_speed_t  =  3,
	dec_speed_t  =  4,

	heat_walls_t =  5
};



class Functor
{

private:

	FunctorType type;

public:

	Functor ();

	Functor (FunctorType init_type);

	FunctorType GetType ();


	virtual void Act    (Mouse* mouse) = 0;

	virtual void Update () = 0;
};



class AddAtom : public Functor
{

private:

	AtomManager* AManager;

	Elementaries basics;

	Vector speed;

public:

	AddAtom ();

	AddAtom (AtomManager* init_manager, 
			 Elementaries init_basics = Elementaries (1, 1, 1), 
			 Vector       init_speed  = Vector (0, 0));

	void Act    (Mouse* mouse);
	void Update ();

	friend class IncreaseBasics;
	friend class DecreaseBasics;

	friend class IncreaseSpeed;
	friend class DecreaseSpeed;
};



class IncreaseBasics : public Functor
{

private:

	AddAtom* AddAtomFunctor;

	Elementaries delta;

public:

	IncreaseBasics ();

	IncreaseBasics (AddAtom* init_functor, Elementaries init_delta);

	int GetBasicNumber ();

	void Act    (Mouse* mouse);
	void Update ();
};


class DecreaseBasics : public Functor
{

private:

	AddAtom* AddAtomFunctor;

	Elementaries delta;

public:

	DecreaseBasics ();

	DecreaseBasics (AddAtom* init_functor, Elementaries init_delta);

	int GetBasicNumber ();

	void Act    (Mouse* mouse);
	void Update ();
};



class IncreaseSpeed : public Functor
{

private:

	AddAtom* AddAtomFunctor;

	Vector delta;

public:

	IncreaseSpeed ();

	IncreaseSpeed (AddAtom* init_functor, Vector init_delta);

	int GetSpeedNumber ();

	void Act    (Mouse* mouse);
	void Update ();
};


class DecreaseSpeed : public Functor
{

private:

	AddAtom* AddAtomFunctor;

	Vector delta;

public:

	DecreaseSpeed ();

	DecreaseSpeed (AddAtom* init_functor, Vector init_delta);

	int GetSpeedNumber ();
	
	void Act    (Mouse* mouse);
	void Update ();
};



class HeatWalls : public Functor
{

private:

	AtomManager* AManager;

	Colour colour_delta;

	float coef_delta;

	bool on_button;

public:

	HeatWalls ();

	HeatWalls (AtomManager* init_manager, 
			   Colour init_colour_delta = {1, 0, 0, 0},
			   float  init_coef_delta = 0.1);

	void Act    (Mouse* mouse);
	void Update ();
};



#endif