/*
Conway's Game of Life

~Andrea-Tomatis
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <gtk/gtk.h>

//change this parameter to vary the size of the matrix
#define DIM 50

#include "./game_of_life.c"




void init_mat(bool*** mat, int dim);
void print_mat(bool** mat, int dim);
int read_from_file(bool ***mat);
void start_cond(bool ***mat);
int rules(bool **mat, int x, int y, int dim);
void matriscopy (bool ** destmat, bool ** srcmat);
int equal(bool **mat1, bool **mat2, int dim);
bool update(bool ***mat, int dim);
