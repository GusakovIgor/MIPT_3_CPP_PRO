#include <Application.hpp>
#include <Math.hpp>
#include <Materials.hpp>
#include <Objects.hpp>
#include <Figures.hpp>
#include <Scene.hpp>

#include <iostream>
#include <vector>


using std::vector;


int main (int argc, char* argv[])
{
	Application* App = new Application ("RayTracer", "Application/Fonts/OpenSans-Bold.ttf");

	Scene* TestScene = new Scene ();

	TestScene->AddFigure (new Sphere3f (Spatial (Point3f (-3,    0,   -16)), 2, Material (LightCoral)));

	TestScene->AddFigure (new Sphere3f (Spatial (Point3f (-1.0, -1.5, -12)), 2, Material (Ivory)));
	TestScene->AddFigure (new Sphere3f (Spatial (Point3f ( 1.5, -0.5, -18)), 3, Material (Cyan)));
	TestScene->AddFigure (new Sphere3f (Spatial (Point3f ( 7,    5,   -18)), 4, Material (DarkViolet)));

	TestScene->AddLight (new Light (Spatial (Point3f (-3, 0, 0)), 1.0));
	TestScene->AddLight (new Light (Spatial (Point3f ( 3, 0, 0)), 1.0));


	// int i = 30;
	// while (i > 0)
	while (App->IsRunning())
	{
		App->ShowFPS ();

		TestScene->Render (App);

		App->RefreshScreen ();
		App->ClearScreen ();
		App->Wait (0.010);

		App->CheckEvents ();

		// --i;
	}

	delete App;

	return 0;
}