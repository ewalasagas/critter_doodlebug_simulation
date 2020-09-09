# critter_doodlebug_simulation
C++ Project: 2D Predator-prey Simulation

## Overview
This project creates a simple 2D predator-prey simulation. In this simulation the prey are critters and the predators are doodlebugs. 

Basic movement of critter represented by 'O':
Only one critter may occupy a cell at a time and moves randomly - if a cell is occupied/moves outside of grid-size, the critter stays in place.  The critter will breed if it survives 3 steps and a new critter is created in an empty cell.  If not 

Basic movement of doodlebug represented by 'x':
Only one doddlebug may occuy a cell at a time and moves randomly - if a cell is occupied by a critter, the critter is eaten and doodlebug occupies the sapce.  A doodlebug will breed if it survivies 8 steps.  If a doodlebug has not eaten within 3 steps, the doodlebug dies.
