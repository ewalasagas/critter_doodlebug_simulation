/***********************************************************************************************************
** Program:		 Group Project - Predator-Prey Game
** Authors:      Elaine Alasagas, Keenon Hunsaker, Jesse Hyatt, Brendan Jang, Jacob Theander
** Description:  Definitions for Cell Class 
**               Holds information for each individual cell on the game board grid
************************************************************************************************************/

#include "Cell.hpp"
#include "Ant.hpp"
#include "Doodlebug.hpp"

#include <typeinfo>

/**
 * constructor 
 */
Cell::Cell() {
    // all pointer points to null
    obj = 0;
    for (int i = 0; i < Cell::NEIGHBOR_NUM; i++) {
        neigbour[i] = 0;
    }
}

/**
 * destructor 
 */
Cell::~Cell() {
    // deallocate if it's needed 
    if (obj != 0) {
        delete obj;
    }
    obj = 0;
}

/**
 * getter
 * @return the critter which is in the cell 
 */
Critter* Cell::getCritter() {
    return obj;
}

/**
 * getter
 * @return array of pointer to adjacency cell
 */
Cell** Cell::getNeigbour() {
    return neigbour;
}

/**
 * setter
 * @param obj pointer to a critter 
 */
void Cell::setCritter(Critter* obj) {
    this->obj = obj;
}

/**
 * checker 
 * @return true when there is a critter in the cell
 * false when there isn't any critter in the cell
 */
bool Cell::isEmpty() {
    return obj == 0;
}

/**
 * overload output stream
 * @param out stream
 * @param cell the cell
 * @return the stream
 */
ostream& operator<<(std::ostream &out, Cell &cell) {
    Critter * critter = cell.getCritter();
    
    if (critter == 0) {
        // cell is empty
        out << " ";
    } else {
        // print an ant or an doodlebug
        if (critter->hash_code() == typeid (Ant).hash_code()) {
            // turn the pointer to Ant pointer 
            // then print the value at its pointed address
            out << *((Ant*) critter);
            // out << "O";
        } else {
            //  out << "X";
            // turn the pointer to Doodlebug pointer 
            // then print the value at its pointed address
            out << *((Doodlebug*) critter);
        }
    }
    return out;
}