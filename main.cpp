/***********************************************************************************************************
** Program:		 Group Project - Predator-Prey Game
** Authors:      Elaine Alasagas, Keenon Hunsaker, Jesse Hyatt, Brendan Jang, Jacob Theander
** Description:  Main.cpp file for group project. Runs an ant vs. doodlebug simulation on a gameboard with
				 a size determined by user input. Ants and doodlebugs are randomly placed on the board, then
				 move and breed functions are called for both, while each step prints the gameboard. 
************************************************************************************************************/

#include "menu.hpp"
#include "Critter.hpp"
#include "Ant.hpp"
#include "Doodlebug.hpp"
#include "Grid.hpp"

#include <iostream>

using std::cout;
using std::endl;

int main()
{
	//Program header
	cout << endl;
	cout << endl;
	cout << "                   PREDATOR vs. PREY" << endl;
	cout << "__________________________________________________________" << endl;
	cout << "This critter simulation of ants vs. doodlebugs runs on a" << endl;
	cout << "user defined gameboard, with random placement of critters" << endl;
	cout << "to start. Ants breed every 3 rounds, doodlebugs every 8." << endl;
	cout << "Doodlebugs attempt to eat ants each round, and will starve" << endl;
	cout << "if no ants are consumed in 3 rounds. Enjoy." << endl;
	cout << endl;
	cout << endl;

	//Call initial menu for user to build gameboard w/ ant & bug count
	int boardRows, boardCols, ant, bug, steps;
	menu1(boardRows, boardCols, ant, bug, steps);
	cout << endl;
	cout << endl;

	// allocate the grid
	Grid * grid;
    grid = new Grid(boardRows, boardCols, ant, bug);

	int round = 1;

	// outputs the initial state of the board before any moves are made
	cout << "Initial Board Setup" << "\n";
	cout << *grid << "\n";

	bool simExtend = true;
	while (simExtend) {    
        // taking step
        while (steps > 0) {
            grid->step();
            cout << "Round "<< round << "\n";
            cout << *grid << "\n";
			round++;
            steps--;
        }
        // get number of step 
		cout << "            END OF SIMULATION" << endl;
		simExtend = menu2(steps);       
    }

    // free the allocated memory 
    delete grid;
    return 0;
}