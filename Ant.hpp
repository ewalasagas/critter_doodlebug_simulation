/***********************************************************************************************************
** Program:		 Group Project - Predator-Prey Game
** Authors:      Elaine Alasagas, Keenon Hunsaker, Jesse Hyatt, Brendan Jang, Jacob Theander
** Description:  Header / Prototypes for Ant Class 
************************************************************************************************************/

#ifndef ANT_HPP
#define ANT_HPP

#include "Critter.hpp"

#include <iostream>

using std::ostream;

class Ant : public Critter {
public:
    // constructor 
    Ant();
    // destructor 
    virtual ~Ant();
    // overriding method
    void move() override;
    // overriding method
    void breed() override;
    // friend method
    friend ostream& operator<< (std::ostream &out, const Ant &ant);
private:
    const static int ANT_SURVIVED_TIME = 3;
};

#endif /* ANT_HPP */

