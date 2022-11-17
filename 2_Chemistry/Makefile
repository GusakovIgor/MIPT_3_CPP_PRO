Run: Main PeriodicTable
	bin/Chemistry PeriodicTable/Elements.txt


Main: Application Shapes Atoms Functor Buttons ListBase AtomManager ButtonManager Chemistry
	g++ bin/Application.o bin/Shapes.o bin/Atoms.o bin/Functor.o bin/Buttons.o bin/ListBase.o bin/AtomManager.o bin/ButtonManager.o bin/Chemistry.o -lSDL2 -lSDL2_ttf -LSDL2_image -o bin/Chemistry


Application: Application/Application.cpp
	g++ -c Application/Application.cpp -o bin/Application.o


Shapes: Elems/Shapes.cpp
	g++ -c Elems/Shapes.cpp -o bin/Shapes.o

Atoms: Elems/Atoms.cpp
	g++ -c Elems/Atoms.cpp -o bin/Atoms.o

Functor: Managers/Functor.cpp
	g++ -c Managers/Functor.cpp -o bin/Functor.o

Buttons: Elems/Buttons.cpp
	g++ -c Elems/Buttons.cpp -o bin/Buttons.o


ListBase: Managers/List/ListBase.cpp
	g++ -c Managers/List/ListBase.cpp -o bin/ListBase.o

AtomManager: Managers/AtomManager.cpp
	g++ -c Managers/AtomManager.cpp -o bin/AtomManager.o

ButtonManager: Managers/ButtonManager.cpp
	g++ -c Managers/ButtonManager.cpp -o bin/ButtonManager.o


Chemistry: Chemistry.cpp
	g++ -c Chemistry.cpp -o bin/Chemistry.o



PeriodicTable: PeriodicTable/GetElementaries.sh PeriodicTable/Elements.csv
	PeriodicTable/GetElementaries.sh PeriodicTable/Elements.csv > PeriodicTable/Elements.txt