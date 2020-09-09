/***********************************************************************************************************
** Program:		 Group Project - Predator-Prey Game
** Authors:      Elaine Alasagas, Keenon Hunsaker, Jesse Hyatt, Brendan Jang, Jacob Theander
** Description:  Definitions for menu functions
**               These functions allow the user to control game parameters and flow
************************************************************************************************************/

#include "menu.hpp"

#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;

void menu1(int& rowIn, int& colIn, int& antIn, int& bugIn, int& stepsIn)
{
	bool op1, op2, op3, op4, op5;
	op1 = op2 = op3 = op4 = op5 = true;
	int row, col, ant, bug, steps;

	while (op1 != false) {
		cout << "Enter number of rows for gameboard (2 - 40): ";
		cin >> row;
		if (cin.fail() || (cin.peek() != '\n')) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Must enter an integer. Try again." << endl;
			cout << endl;
		}
		else if (row < 2 || row > 40) {
			cout << "Must be an integer between 2 and 40. Try again." << endl;
			cout << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			rowIn = row;
			op1 = false;
		}
	}

	while (op2 != false) {
		cout << "Enter number of columns for gameboard (2 - 40): ";
		cin >> col;
		if (cin.fail() || (cin.peek() != '\n')) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Must enter an integer. Try again." << endl;
			cout << endl;
		}
		else if (col < 2 || col > 40) {
			cout << "Must be an integer between 2 and 40. Try again." << endl;
			cout << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			colIn = col;
			op2 = false;
		}
	}
	while (op3 != false) {
		cout << "Enter number of ants to start (1 - " << ((row * col) / 2) << "): ";
		cin >> ant;
		if (cin.fail() || (cin.peek() != '\n')) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Must enter an integer. Try again." << endl;
			cout << endl;
		}
		else if (ant < 1 || ant > ((row * col) / 2)) {
			cout << "Must enter integer between 1 and " << ((row * col) / 2) << ". Try again." << endl;
			cout << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			antIn = ant;
			op3 = false;
		}
	}
	while (op4 != false) {
		cout << "Enter number of doodlebugs to start (1 - " << ((row * col) / 2) << "): ";
		cin >> bug;
		if (cin.fail() || (cin.peek() != '\n')) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Must enter an integer. Try again." << endl;
			cout << endl;
		}
		else if (bug < 1 || bug >((row * col) / 2)) {
			cout << "Must enter integer between 1 and " << ((row * col) / 2) << ". Try again." << endl;
			cout << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			bugIn = bug;
			op4 = false;
		}
	}
	while (op5 != false) {
		cout << "Enter number of simulation steps (1 - 50): ";
		cin >> steps;
		if (cin.fail() || (cin.peek() != '\n')) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Must enter an integer. Try again." << endl;
			cout << endl;
		}
		else if (steps < 1 || steps > 50) {
			cout << "Must enter integer between 1 and 50. Try again." << endl;
			cout << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			stepsIn = steps;
			op5 = false;
		}
	}
}

bool menu2(int& stepsIn)
{
	int selection = 0;
	int steps = 0;
	bool menuRun = true;
	bool choice = true;

	while (menuRun != false) {
		cout << endl;
		cout << "Would you like to continue the simulation?" << endl;
		cout << "1 - Continue" << endl;
		cout << "2 - Exit Game" << endl;
		while ((cout << "Enter your choice: ") && (!(cin >> selection) || (cin.peek() != '\n') || selection < 1 || selection > 2))
        {
			cout << "Invalid input. Please try again." << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

		switch (selection)
		{
		case 1:  menuRun = false;
			cout << endl;
			while (choice != false) {
				cout << "Enter number of additional steps to run (1 - 50): ";
				cin >> steps;
				if (cin.fail() || (cin.peek() != '\n')) {
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cout << "Must enter an integer. Try again." << endl;
					cout << endl;
				}
				else if (steps < 1 || steps > 50) {
					cout << "Must enter integer between 1 and 50. Try again." << endl;
					cout << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				else {
					stepsIn = steps;
					choice = false;
				}
			}
			return true;
			break;
		case 2:  menuRun = false;
			cout << endl;
			cout << "Thank you for playing!" << endl;
			return false;
			break;
		default: cout << endl;
			cout << "You must select '1' or '2'." << endl;
			cout << endl;
			cout << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
	return false;
}