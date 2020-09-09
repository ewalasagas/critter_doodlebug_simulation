/***********************************************************************************************************
** Program:		 Group Project - Predator-Prey Game
** Authors:      Elaine Alasagas, Keenon Hunsaker, Jesse Hyatt, Brendan Jang, Jacob Theander
** Description:  Header / Prototypes for Grid Class 
**               This contains the information for the game board grid
************************************************************************************************************/

#ifndef GRID_HPP
#define GRID_HPP

#include "Cell.hpp"

#include <iostream>

using std::ostream;


class Grid {
public:
    // constructor
    Grid(int row, int col, int ant, int doodlebug);
    // destructor 
    virtual ~Grid();
    // friend method
    friend ostream& operator<< (std::ostream &out, Grid &gr);
    // take step
    void step(); 
    
private:
    // moving
    void move();
    // breeding
    void breed();
    // starving
    void starve();
    // set up the grid
    void initGrid(int ant, int doodlebug);
    // put critter on grid
    void putCritter(Critter * critter, int row_index, int col_index);
private:
    // size of the grid
    int row;
    int col;
    // dynamic array
    Cell ** grid;
};

#endif /* GRID_HPP */