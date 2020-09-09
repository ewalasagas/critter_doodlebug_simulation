/***********************************************************************************************************
** Program:		 Group Project - Predator-Prey Game
** Authors:      Elaine Alasagas, Keenon Hunsaker, Jesse Hyatt, Brendan Jang, Jacob Theander
** Description:  Header / Prototypes for Critter Class 
**               This is the base class that Ants / Doodlebugs inherit from
************************************************************************************************************/

#ifndef CRITTER_HPP
#define CRITTER_HPP

#include <cstdint>

class Cell;

class Critter {
public:
    // constructor
    Critter(uint64_t hash_code);
    // destructor
    virtual ~Critter();    
    
    // pure virtual method
    virtual void move() = 0;
    // pure virtual method
    virtual void breed() = 0;
    
    // get the critter to be older 
    void beOlder();
    // getter 
    int getAge();
    // setter 
    void setCell(Cell * cell);
    // getter 
    Cell * getCell();
    // getter
    uint64_t hash_code();
protected:
    // let the critter breed a new critter 
    bool setBreed(Critter * critter);
    // move the critter around
    void moving();
    
private:
    int ttl; // time to live    
    Cell * cell;  // pointer to its current cell
    uint64_t hashcode; // hash code of type id of the object
};

#endif /* CRITTER_HPP */