#include<stdio.h>
 
#ifndef _MYMALLOC_H
#define _MYMALLOC_H

static char myblock[4096]; 
#define malloc(x) mymalloc(x, _LINE_, _FILE_)
struct _metablock *start= (void *) myblock;
void* mymalloc(int memory, int linenum, char* filename);
 
#define free(x) myfree(x, _LINE_, _FILE_)
void* myfree(void*, int, char*);
void initialize();

void mergeNext(struct _metablock *); 

#endif
