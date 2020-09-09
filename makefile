#***********************************************************************************************************
#* Program:		 Group Project - Predator-Prey Game
#* Authors:      Elaine Alasagas, Keenon Hunsaker, Jesse Hyatt, Brendan Jang, Jacob Theander
#* Description:  makefile
#***********************************************************************************************************/

CXX = g++
CXXFLAGS = -std=c++0x 
CXXFLAGS += -Wall 
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS =    main.o   Critter.o   Ant.o   Doodlebug.o   Cell.o   Grid.o   menu.o

SRCS =    main.cpp Critter.cpp Ant.cpp Doodlebug.cpp Cell.cpp Grid.cpp menu.cpp

HEADERS =          Critter.hpp Ant.hpp Doodlebug.hpp Cell.hpp Grid.hpp menu.hpp

#target: dependencies
#	rule to build
#

group_project: ${OBJS} ${HEADERS}
	${CXX} ${OBJS} -o project

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm ${OBJS} project