/***********************************************************************************************************
** Program:		 Group Project - Predator-Prey Game
** Authors:      Elaine Alasagas, Keenon Hunsaker, Jesse Hyatt, Brendan Jang, Jacob Theander
** Description:  Header / Prototypes for Cell Class 
**               Holds information for each individual cell on the game board grid
************************************************************************************************************/

#ifndef CELL_HPP
#define CELL_HPP

#include "Critter.hpp"

#include <iostream>

using std::ostream;

class Cell {
public:
    // constructor
    Cell();
    // destructor 
    virtual ~Cell();
    // getter 
    Cell ** getNeigbour();
    Critter * getCritter();
    // setter 
    void setCritter(Critter * obj);
    // is there any critter 
    bool isEmpty();
    // friend method
    friend ostream& operator<< (std::ostream &out, Cell &cell);
public:
    const static int NEIGHBOR_NUM = 4;    
    const static int UP = 0;    
    const static int LEFT = 1;    
    const static int DOWN = 2;    
    const static int RIGHT = 3; 
   // int r; // row and col for debugging issue
  //  int c;
private:   
    // the current critter
    Critter * obj;
    // pointers to adjacency cell 
    Cell * neigbour[NEIGHBOR_NUM];    
};

#endif /* CELL_HPP */