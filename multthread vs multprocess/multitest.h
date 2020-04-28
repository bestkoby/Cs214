#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> 
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#define random(x) (rand()%x)
#include <pthread.h> 


#ifndef _MULTITEST_H
#define _MULTITEST_H

 

#define search(n, arr, pivot)  search(n, arr, pivot)


void search(int n, int *arr, int pivot);
 
#endif