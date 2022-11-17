#ifndef ATOMS_HPP
#define ATOMS_HPP


#include "Shapes.hpp"


struct Vector
{
	float x;
	float y;

	Vector () {}

	Vector (float v_x, float v_y);
};

Vector operator+ (const Vector& left, const Vector& right);

Vector operator- (const Vector& left, const Vector& right);

Vector operator+= (Vector& left, const Vector& right);

Vector operator-= (Vector& left, const Vector& right);

bool operator== (const Vector& left, const Vector& right);



class Elementaries
{

public:

	int protons;
	int electrons;
	int neutrons;

	Elementaries () {}

	Elementaries (int init_p, int init_e, int init_n);

	bool Exist ();

	int Weight ();
};

Elementaries operator+ (const Elementaries& left, const Elementaries& right);

Elementaries operator- (const Elementaries& left, const Elementaries& right);

Elementaries operator+= (Elementaries& left, const Elementaries& right);

Elementaries operator-= (Elementaries& left, const Elementaries& right);

bool operator== (const Elementaries& left, const Elementaries& right);



class Atom
{

private:

	char* name;

	int lifetime;


	Elementaries basics;

	Shape* shape;

	Vector speed;


public:

	 Atom (Borders* window, char* init_name, Elementaries init_basics, Vector init_speed);

	 Atom (Point appear_centre, char* init_name, Elementaries init_basics, Vector init_speed);

	~Atom ();


	int Lifetime ();

	void UpdateLifetime ();


	Vector GetSpeed ();

	void SetSpeed (Vector new_speed);


	Elementaries GetBasics ();

	Point GetCentre ();


	void Draw (Application* App);

	void Replace ();


	void CheckCollisionBorders (Borders* window);
	

	friend bool CheckCollisionAtoms (Atom* first, Atom* second);
};



const int BASE_SIZE = 26;

const Elementaries proton   = Elementaries (1, 0, 0);
const Elementaries electron = Elementaries (0, 1, 0);
const Elementaries neutron  = Elementaries (0, 0, 1);


#endif