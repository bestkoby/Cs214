#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 
#include <errno.h>
//#include<multitest.h>
#define random(x) (rand()%x)

struct parameter{
    int startindex, endindex, pivot;
    int *arr;

};

void* func(void *p){
    int start = ((struct parameter*)p)->startindex;
    int end = ((struct parameter*)p)->endindex;
    int pivot = ((struct parameter*)p)->pivot;
    int *arr = ((struct parameter*)p)->arr;
    int i;
    for ( i = start; i < end; ++i) {
        if (arr[i] == pivot) break;
    }
    if (i < end) { /* element at i is a hit */
        printf("This is multithread.found in index %d \n", i);
        pthread_exit((void*) 1); //found it
    }else{
        pthread_exit((void*) 0);  //not found it
    }  
}

void search(int n, int *arr, int pivot){
    // my search method is for any input array, divided them into subgroup with 250 elements
    // and create thread to search each of them. 
    if (n>250){
        int numofthread = n/250;
        int reminder = n%250;
        int j = 0;
        int startindex = 0;
        int endindex = 250;
        pthread_t thread[numofthread]; // ptid
        void *parameter[numofthread];
        for (j = 0; j< numofthread; j++){
            parameter[j] = (struct parameter *)malloc(sizeof(struct parameter));
                struct parameter *p = parameter[j];
                p->startindex = startindex;
                p->endindex = endindex;
                p->pivot = pivot;
                p->arr = arr;
            pthread_create(&thread[j], NULL, func, (void*)p); 
           //printf("pthread_create failed with i = %d. errno = %d, %s\n", j, errno, strerror(errno));
            startindex +=250;
            endindex +=250;
        }
        
        void *returnvalue;
        int  i;
        for (i = 0; i < numofthread; i++) { 
            pthread_join(thread[i], &returnvalue); 
            //if (*(int*)returnvalue == 1){ //one thread find it 
            //    exit(0); // terminate all thread
            //    break;
            //}
        }    
        
        for (i = 0; i < numofthread; i++) {
            free(parameter[i]);
        }
    }
}