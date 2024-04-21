#ifndef MSSV_H
#define MSSV_H

#include "child.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

int** sol;
int* row;
int* col;
int* sub;
int* counter;
int delay_time;

int main(int, char**);


#endif