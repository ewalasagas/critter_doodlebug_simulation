/***********************************************************************************************************
** Program:		 Group Project - Predator-Prey Game
** Authors:      Elaine Alasagas, Keenon Hunsaker, Jesse Hyatt, Brendan Jang, Jacob Theander
** Description:  Definitions for Ant Class 
************************************************************************************************************/

#include "Ant.hpp"
#include "Cell.hpp"

#include <typeinfo>

/**
 * constructor 
 * 
 */
Ant::Ant() : Critter(typeid (Ant).hash_code()) {
}

/**
 * destructor
 */
Ant::~Ant() {
}

/**
 * move the ant
 */
void Ant::move() {
    this->moving();
}

/**
 * the ant breeds
 */
void Ant::breed() {
    // it should be in the right period of time 
    int age = this->getAge();
    if (age == 0 || age % ANT_SURVIVED_TIME != 0) {
        return;
    }
    // make a new ant
    Ant * ant = new Ant();
    // try to put it in the grid
    if (this->setBreed(ant) == false) {
        // false to put it in 
        delete ant;
        // debugging message
        // cout << "Cannot put new ant on the grid\n";
    }
}

/**
 * overload output stream
 * @param out stream
 * @param ant the ant
 * @return the stream
 */
ostream& operator<<(std::ostream& out, const Ant& ant) {
    out << "O";
    return out;
}