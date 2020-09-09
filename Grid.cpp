/***********************************************************************************************************
** Program:		 Group Project - Predator-Prey Game
** Authors:      Elaine Alasagas, Keenon Hunsaker, Jesse Hyatt, Brendan Jang, Jacob Theander
** Description:  Definitions for Grid Class 
**               This contains the information for the game board grid
************************************************************************************************************/

#include "Grid.hpp"
#include "Ant.hpp"
#include "Doodlebug.hpp"

#include <vector>
#include <algorithm>
#include <random>
#include <typeinfo>

using std::vector;
using std::pair;


/**
 * constructor 
 * assume that all argument are legal
 * @param row number of row
 * @param col number of column
 * @param ant number of ant
 * @param doodlebug number of bug
 */
Grid::Grid(int row, int col, int ant, int doodlebug) {
    Cell ** neighbor;
    this->row = row;
    this->col = col;

    // allocate row of pointers to pointers
    grid = new Cell*[row];
    // for each row
    for (int i = 0; i < row; i++) {
        // allocate array of cell
        grid[i] = new Cell[col];
        /* for debugging
         * for (int j = 0; j < col; j++) {
             grid[i][j].r = i;
             grid[i][j].c = j;           
         }        
         */
    }
    int tmp;

    // connect cell to its upper cell
    for (int i = 1; i < row; i++) {
        tmp = i - 1;
        for (int j = 0; j < col; j++) {
            neighbor = grid[i][j].getNeigbour();
            neighbor[Cell::UP] = &grid[tmp][j];
        }
    }

    // connect cell to its lower cell
    for (int i = 0; i < row - 1; i++) {
        tmp = i + 1;
        for (int j = 0; j < col; j++) {
            neighbor = grid[i][j].getNeigbour();
            neighbor[Cell::DOWN] = &grid[tmp][j];
        }
    }

    // connect cell to its right cell    
    for (int j = 0; j < col - 1; j++) {
        tmp = j + 1;
        for (int i = 0; i < row; i++) {
            neighbor = grid[i][j].getNeigbour();
            neighbor[Cell::RIGHT] = &grid[i][tmp];
        }
    }

    // connect cell to its left cell
    for (int j = 1; j < col; j++) {
        tmp = j - 1;
        for (int i = 0; i < row; i++) {
            neighbor = grid[i][j].getNeigbour();
            neighbor[Cell::LEFT] = &grid[i][tmp];
        }
    }
    
    // put bug and ant to the grid
    initGrid(ant, doodlebug);
}

/**
 * destructor 
 */
Grid::~Grid() {
    for (int i = 0; i < row; i++) {
        // free each row
        delete [] grid[i];
    }
    // free all grid
    delete [] grid;
}

/**
 * put critter on the grid
 * @param ant number of ant
 * @param doodlebug number of bug
 */
void Grid::initGrid(int ant, int doodlebug) {
    // list all possible position
    vector<pair<int, int>> index;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
        index.push_back(std::make_pair(i,j));
        }
    }
    
    // shuffle them to get random position
    auto rng = std::default_random_engine {};
    std::shuffle(index.begin(), index.end(), rng);
    
    // put ants on grid
    Ant * ant_;
    for (int i = 0; i < ant; i++) {
        ant_ = new Ant();
        putCritter(ant_, index[i].first, index[i].second);
    }

    // put bugs on grid
    Doodlebug * doodlebug_;
    for (int i = ant; i < ant + doodlebug; i++) {
        doodlebug_ = new Doodlebug();
        putCritter(doodlebug_, index[i].first, index[i].second);
    }
    // clear the index vector 
    index.clear();
}

/**
 * put a critter on grid
 * @param critter pointer to a critter 
 * @param index the right position
 */
void Grid::putCritter(Critter* critter, int row_index, int col_index) {
    // find its row
    int r = row_index;
    // find its column
    int c = col_index;
    // put it on grid
    grid[r][c].setCritter(critter);
    critter->setCell(&grid[r][c]);
}

/**
 * overload output stream
 * @param out stream
 * @param grid the grid
 * @return the stream
 */
ostream& operator<<(std::ostream &out, Grid &gr) {
    // first line
    for (int j = 0; j < gr.col; j++) {
        out << "--";
    }
    out << "-\n";
    // the grid
    // print row
    for (int i = 0; i < gr.row; i++) {
        out << "|";
        // print each cell in row
        for (int j = 0; j < gr.col; j++) {
            out << gr.grid[i][j] << "|";
        }
        out << "\n";
    }
    // the bottom line 
    for (int j = 0; j < gr.col; j++) {
        out << "--";
    }
    out << "-\n";
    return out;
}

/**
 * taking step
 */
void Grid::step() {
    
    // make critters to be older 
    uint64_t d_hash = typeid (Doodlebug).hash_code();
    Critter * critter;
    Doodlebug * doodlebug;
    Ant * ant;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            critter = grid[i][j].getCritter();
            if (critter != 0) {
                if (critter->hash_code() == d_hash) {
                    doodlebug = (Doodlebug *) critter;
                    doodlebug->beOlder();
                } else {
                    ant = (Ant*) critter;
                    ant->beOlder();
                }
            }
        }
    }

    // moving
    move();
    // breeding
    breed();
    // starving
    starve();

}

/**
 * starving
 */
void Grid::starve() {
    Doodlebug * doodlebug;
    Critter * critter;
    
    // get out all bug
    uint64_t d_hash = typeid (Doodlebug).hash_code();
    vector<Doodlebug *> bugs;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            critter = grid[i][j].getCritter();
            if (critter != 0
                    && critter->hash_code() == d_hash) {
                doodlebug = (Doodlebug*) critter;
                bugs.push_back(doodlebug);
            }
        }
    }
    
    // check their state
    Cell * cell;
    for (Doodlebug * elem : bugs) {
        // delete it if it is starving 
        if (elem->isStarve()) {
            cell = elem->getCell();
            cell->setCritter(0);
            delete elem;
        }
    }
    // clean the vector
    bugs.clear();
}

/**
 * breeding
 */
void Grid::breed() {
    Critter * critter;
    vector<Critter *> crts;
    // get all critter 
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            critter = grid[i][j].getCritter();
            if (critter != 0) {
                crts.push_back(critter);
            }
        }
    }

    // let them breed
    for (Critter * elem : crts) {
        elem->breed();
    }
    // clear the vector
    crts.clear();
}

/**
 * moving
 */
void Grid::move() {
    Doodlebug * doodlebug;
    Critter * critter;

    // move doodlebug
    uint64_t d_hash = typeid (Doodlebug).hash_code();
    vector<Doodlebug *> bugs;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            critter = grid[i][j].getCritter();
            if (critter != 0
                    && critter->hash_code() == d_hash) {
                doodlebug = (Doodlebug*) critter;
                bugs.push_back(doodlebug);
            }
        }
    }
    for (Doodlebug * elem : bugs) {
        elem->move();
    }
    bugs.clear();

    // move ant
    uint64_t a_hash = typeid (Ant).hash_code();
    Ant * ant;
    vector<Ant *> ants;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            critter = grid[i][j].getCritter();
            if (critter != 0
                    && critter->hash_code() == a_hash) {
                ant = (Ant*) critter;
                ants.push_back(ant);
            }
        }
    }
    for (Ant * elem : ants) {
        elem->move();
    }
    ants.clear();
}