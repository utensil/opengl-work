wxLabyrinth
=============

An OpenGL and wxWidgets based program to create a random 2D labyrinth dynamically, by a "rat" following the algorithm below: 

1. The labyrinth was a grid with N x M cells at the beginning;
2. Every single cell of the grid has 4 intact walls at the beginning;
3. The rat will appear at one of the cells(let's call it cell A);
4. Let's call the cell which the rat is currently in "the current cell";
5. The rat will choose a cell from the unvisited cells surrounding "the current cell" to move to and break through the corresponding wall along the way, if there is at least one unvisited cell surrounding "the current cell";
6. The rat will choose the last visited cell if there is no unvisited cell surrounding "the current cell";
7. The rat will repeat step 4-6 until all cells are visited;
8. Now the labyrinth is created.

Usage
-----------------

* Left key: let the rat creat the labyrinth
* Right key: reset the labyrinth to the grid and place the rat to a random cell
* Space bar: let the rat move to the next cell according to the algorithm if there are still unvisited cells

Build
-----------------

For the time being, we only provides Makefile for MinGW under Windows, but it's easy to port it to other OS or compilers.

* Build wxWidgets
* Modify WX_SOURCE_ROOT in Makefile to where you place wxWidgets source
* Under MSYS, `make`

Build wxWidgets
-----------------

* Use subversion client to check out wxWidgets source to ${WX_SOURCE_ROOT}, eg. C:\wxWidgets
* See ${WX_SOURCE_ROOT}/BuildSVN.txt for building instructions
* Copy ${WX_SOURCE_ROOT}\include\wx\msw\setup0.h to ${WX_SOURCE_ROOT}\include\wx\msw\setup.h
* Under MSYS, `cd` into  the directory 'build/msw', and `make -f makefile.gcc SHARED=1 MONOLITHIC=1 BUILD=debug UNICODE=1`

Development Status
--------------------

The code is still too messy(needs some refactoring), but it works.

Acknowledgments
-----------------

* wxWidgets authors

Licence
-----------------

MIT Licence, see LICENCE.
Copyright (c) 2011-2012 Utensil Song (https://github.com/utensil)