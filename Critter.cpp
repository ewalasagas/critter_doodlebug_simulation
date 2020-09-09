/***********************************************************************************************************
** Program:		 Group Project - Predator-Prey Game
** Authors:      Elaine Alasagas, Keenon Hunsaker, Jesse Hyatt, Brendan Jang, Jacob Theander
** Description:  Definitons for Critter Class 
**               This is the base class that Ants / Doodlebugs inherit from
************************************************************************************************************/

#include "Critter.hpp"
#include "Cell.hpp"

#include <vector>

using std::vector;

/**
 * constructor 
 * @param hashcode hash code helps to distinguish ant and doodlebug 
 */
Critter::Critter(uint64_t hashcode) {
    // at first
    // is doesn't have age. and doesn't in any cell
    ttl = 0;
    cell = 0;
    this->hashcode = hashcode;
}

/**
 * destructor 
 * nothing to be free
 * we free all allocated memory in Cell's destructor 
 */
Critter::~Critter() {
}

/**
 * make the critter to be older 
 */
void Critter::beOlder() {
    ttl++;
}

/**
 * getter
 * @return time to live 
 */
int Critter::getAge() {
    return ttl;
}

/**
 * getter 
 * @return current cell 
 */
Cell* Critter::getCell() {
    return cell;
}

/**
 * setter 
 * @param cell set the cell of the critter
 */
void Critter::setCell(Cell* cell) {
    this->cell = cell;
}

/**
 * let the new critter be in an em[ty cell
 * @param critter
 * @return true when the critter has an empty cell to be put in 
 */
bool Critter::setBreed(Critter* critter) {
    Cell * cell = this->getCell();
    Cell ** neighbours = cell->getNeigbour();
    vector<int> empty_cell_index;

    // get list of possible empty cells
    for (int i = 0; i < Cell::NEIGHBOR_NUM; i++) {
        if (neighbours[i] != 0
                && neighbours[i]->isEmpty() == true) {
            empty_cell_index.push_back(i);
        }
    }

    // there is no empty cell
    if (empty_cell_index.empty() == true) {
        return false;
    }

    // get an empty cell
    int random_direction = rand() % empty_cell_index.size();
    Cell * direction = neighbours[empty_cell_index[random_direction]];
    // put it in 
    critter->setCell(direction);
    direction->setCritter(critter);

    // clean the vector 
    empty_cell_index.clear();
    return true;
}

/**
 * move the critter around
 */
void Critter::moving() {

    // get the cell
    Cell * cell = this->getCell();
    // the critter is not on the grid
    if (cell == 0) {
        return;
    }

    // get a direction
    int random_direction = rand() % Cell::NEIGHBOR_NUM;

    // get the destination cell
    Cell ** neighbours = cell->getNeigbour();
    Cell * direction = neighbours[random_direction];

    // the destination is out of grid
    if (direction == 0) {
        return;
    }

    // the destination isn't empty
    if (direction->isEmpty() == false) {
        return;
    }

    // move the critter to the new cell
    direction->setCritter(this);
    // leave the old cell
    cell->setCritter(0);
    // reset its position
    this->setCell(direction);
}

/**
 * getter
 * @return hash code 
 */
uint64_t Critter::hash_code() {
    return hashcode;
}