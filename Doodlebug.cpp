/***********************************************************************************************************
** Program:		 Group Project - Predator-Prey Game
** Authors:      Elaine Alasagas, Keenon Hunsaker, Jesse Hyatt, Brendan Jang, Jacob Theander
** Description:  Definitions for Doodlebug Class 
************************************************************************************************************/

#include "Doodlebug.hpp"
#include "Ant.hpp"
#include "Cell.hpp"

#include <typeinfo>
#include <vector>

using std::cout;
using std::vector;

/**
 * constructor 
 * 
 */
Doodlebug::Doodlebug() : Critter(typeid (Doodlebug).hash_code()) {
    tte = 0;
}

/**
 * destructor 
 */
Doodlebug::~Doodlebug() {
}

/**
 * get older and get hungry
 */
void Doodlebug::beOlder() {
    // call parent's method in child's class
    this->Critter::beOlder();
    // get hungry
    tte++;
}

/**
 * checker 
 * @return true if the object is starved 
 */
bool Doodlebug::isStarve() {
    return tte > DOODLEBUG_STARVED_TIME;
}

/**
 * breed a new doodlebug when the time comes
 */
void Doodlebug::breed() {
    // check for the right period 
    int age = this->getAge();
    if (age == 0 || age % DOODLEBUG_SURVIVED_TIME != 0) {
        return;
    }
    // make a new bug
    Doodlebug * doodlebug = new Doodlebug();
    // try to put it on the grid
    if (this->setBreed(doodlebug) == false) {
        // cannot put it it, delete it
        delete doodlebug;
        // debugging message
        //cout << "Cannot put new doodlebug on the grid\n";
    }
}

/**
 * move it around
 */
void Doodlebug::move() {

    // check its position
    Cell * cell = this->getCell();
    if (cell == 0) {
        cout << "The doodlebug is not in any cell\n";
        return;
    }
    // try to eat an ant and take its position
    if (this->eating() == false) {
        // there is no ant
        // move to another cell
        this->moving();
    } else {
        //   cout << "eating\n";
        // get full
        tte = 0;
    }
}

/**
 * eat an ant and take its position
 * @return true id there is ant to be eaten
 */
bool Doodlebug::eating() {
    uint64_t ant_hashcode = typeid (Ant).hash_code();

    // get all adjacency cell
    Cell * cell = this->getCell();
    Cell ** neighbours = cell->getNeigbour();
    // try to eat an ant
    // find ant
    vector<int> ant_index;
    for (int i = 0; i < Cell::NEIGHBOR_NUM; i++) {
        if (neighbours[i] != 0) {
            Critter * critter = neighbours[i]->getCritter();
            if (critter != 0
                    && ant_hashcode == critter->hash_code()) {
                //   cout << i << "..";
                ant_index.push_back(i);
            }
        }
    }

    // there is no ant
    if (ant_index.empty() == true) {
        // cout << "empty";
        return false;
    }

    // start to move from current cell to the cell of the ant
    cell->setCritter(0);

    // choose an ant to eat
    int random_direction = rand() % ant_index.size();
    Cell * direction = neighbours[ant_index[random_direction]];

    // take the ant out
    Critter * ant = direction->getCritter();
    // deallocate it 
    delete ant;
    // put the bug into the new cell
    direction->setCritter(this);
    this->setCell(direction);

    // clear vector 
    ant_index.clear();
    
    return true;
}

/**
 * overload output stream
 * @param out stream
 * @param doodlebug the bug
 * @return the stream
 */
ostream& operator<<(std::ostream& out, const Doodlebug& doodlebug) {
    out << "X";
    return out;
}