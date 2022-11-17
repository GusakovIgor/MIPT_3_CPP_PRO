#ifndef BUTTONS_HPP
#define BUTTONS_HPP


#include "../Managers/Functor.hpp"

class ButtonManager;

class Button
{

protected:

	Functor* functor;

	Shape* shape;

	Texture* texture;


public:

	Button ();

	Button (Functor* init_functor, Shape* init_shape);


	virtual void Draw (Application* App) = 0;

	void Act    (Mouse* mouse);

	void Update ();

	bool Contains (Point location);


	friend class ButtonManager;
};



class AddAtomButton : public Button
{

public:

	AddAtomButton ();

	AddAtomButton (AddAtom* init_functor, Shape* init_shape);


	void Draw (Application* App);
};


class IncBasicsButton : public Button
{

public:
	
	IncBasicsButton ();

	IncBasicsButton (IncreaseBasics* init_functor, Shape* init_shape);


	void Draw (Application* App);
};


class DecBasicsButton : public Button
{

public:
	
	DecBasicsButton ();

	DecBasicsButton (DecreaseBasics* init_functor, Shape* init_shape);


	void Draw (Application* App);
};



class IncSpeedButton : public Button
{

public:
	
	IncSpeedButton ();

	IncSpeedButton (IncreaseSpeed* init_functor, Shape* init_shape);


	void Draw (Application* App);
};


class DecSpeedButton : public Button
{

public:
	
	DecSpeedButton ();

	DecSpeedButton (DecreaseSpeed* init_functor, Shape* init_shape);


	void Draw (Application* App);
};



class HeatWallsButton : public Button
{

public:

	HeatWallsButton ();

	HeatWallsButton (HeatWalls* init_functor, Shape* init_shape);


	void Draw (Application* App);
};



#endif