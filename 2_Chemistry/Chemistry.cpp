#include "Managers/ButtonManager.hpp"


int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		printf ("Please, call programm with 1 argument - name of the file with periodic table info in format:\n\n");
		assert (!"OK");
	}

	const char* file_with_table = argv[1];


	Application* App = new Application ("Bubbles", "Application/Fonts/OpenSans-Bold.ttf");

	if (!App->IsRunning())
	{		
		assert (!"OK");
	}


	AtomManager* AManager = new AtomManager (new Borders (Point (0, 0), Point (1440, 810), White),
											 new PeriodicTable (file_with_table));
	
	ButtonManager* BManager = new ButtonManager (App, "config.txt");
	
	
	BManager->AddButton (new AddAtomButton (new AddAtom (AManager, Elementaries (1, 1, 0), Vector (0, 0)),
											new RoundedRect (Point (1470, 100), Point (1890, 250), 20, Orange)));

	BManager->AddButton (new HeatWallsButton (new HeatWalls (AManager, {0, 1, 1, 1}, 0.005),
											  new RoundedRect (Point (1500, 350), Point (1860, 450), 20, Orange)));


	Mouse* mouse = new Mouse (Point (0, 0), wrong_b);

	while (App->IsRunning())
	{
		App->ShowFPS ();
		BManager->DrawButtons (App);
		BManager->UpdateButtons (mouse);
		BManager->CheckClicks   (mouse);

		AManager->MoveAtoms ();
		AManager->UpdateAtoms ();
		AManager->DrawAtoms (App);


		App->RefreshScreen ();
		App->ClearScreen ();
		App->Wait (0.010);

		App->CheckEvents (mouse);
	}

	delete BManager;
	delete AManager;
	delete App;

	return 0;
}