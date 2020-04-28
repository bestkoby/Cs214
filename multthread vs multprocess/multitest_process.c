#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> 
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#define random(x) (rand()%x)



void search(int n, int *arr, int pivot)
{	

	if(n > 250)
	{
		int numofproc = n / 250;
        int startindex = -250;
        int j = startindex;
        int endindex = 0;
        pid_t pid;
        int i = 0;
        int k;
        while(i < numofproc)
        {
        	startindex = startindex + 250;
        	endindex = endindex + 250;
        	pid = fork();
        	if(pid < 0)//error
        	{
        		printf("fork failed\n");
        		exit(1);
        	}
        	else if(pid == 0)//in child process 
        	{
        		  for(j = startindex; j < endindex; j++)
        		{
					   if(arr[j] == pivot) 
        			{
       					printf("This is multiprocess.Hit in child process %d. The index is %d. Pid is %d \n", i, j, getpid()); 
						i = j = 2001; 
						break;
					}


        		}
        		// printf("s: %d e:%d \n ", startindex, endindex);
        		exit(0);
        	}
		    else	//parent procss
        	{  
            	for(k = 0; k < numofproc; k++)
            	{
              		int zero = -1;
              		wait(&zero);
					
				}
        	}
        	i++;
        }
	}
}