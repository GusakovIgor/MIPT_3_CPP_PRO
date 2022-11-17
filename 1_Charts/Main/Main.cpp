#include <Application.hpp>
#include <Charts.hpp>

#include <iostream>
#include <vector>


using std::vector;


double linear (double argument);
double square (double argument);


int main (int argc, char* argv[])
{
	Application* App = new Application ("Charts", "Application/Fonts/OpenSans-Bold.ttf");

	ChartManager* chart_manager = new ChartManager ();

	chart_manager->AddChart (new Chart (App, Point2f (0.0, 0.0), Point2f (1000.0, 1000.0), Set2f (-50.0, 50.0), Set2f (-50.0, 50.0)));
	chart_manager->AddChart (new Chart (App, Point2f (1100.0, 10.0), Point2f (1700.0, 610.0), Set2f (-100.0, 100.0), Set2f (-100.0, 100.0)));
	chart_manager->AddChart (new Chart (App, Point2f (1250.0, 650.0), Point2f (1550.0, 950.0), Set2f (-100.0, 100.0), Set2f (-100.0, 100.0)));

	chart_manager->AddFunction (new ChartFunction (linear, Fucsia));
	chart_manager->AddFunction (new ChartFunction (square, Lime));

	while (App->IsRunning())
	{
		App->ShowFPS ();

		chart_manager->Draw (App);

		App->RefreshScreen ();
		App->ClearScreen ();
		App->Wait (0.10);

		App->CheckEvents ();
		chart_manager->CheckEvents (App);
	}

	delete App;

	return 0;
}

double linear (double argument)
{
	return argument * 2;
}

double square (double argument)
{
	return argument * argument;
}