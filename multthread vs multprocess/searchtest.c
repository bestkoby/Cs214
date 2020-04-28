  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> 
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

#define random(x) (rand()%x)

// init a first array
void fillArray(int n, int *arr)
{
	srand(time(NULL));
 	int value = 0; /* aux. to provide value to set */
	int i; /* loop index */
  	for (i = 0; i < n; ++i)
  	{
  		arr[i] = value;
  		value++;
  	}
  	int a,b,temp,j,k;
  	a = random(n);
  	for(j = 0; j < n*3/4; ++j)
  	{
  		b = random(n);
  		temp = arr[a];
  		arr[a] = arr[b];
  		arr[b] = temp;
  	}
}

//create a new array from the previous array
void newArray(int n, int *arr, int pivot){
	int index;
	for(index =0; index<n; index++){
		if(arr[index] == pivot){
			break; 
		}
	}
	int newindex = random(n);
	int temp = arr[index];
	arr[index] = arr[newindex];
	arr[newindex] = temp;

}

//test B will try different size of array to and collect the runtime for them 

int main(int argc, char **argv) 
{ 
	struct timeval startTime,endTime; 
	int n = 20000;    //we will test different size by changging the value of n.
	int i;
  	int pivot = random(n); 
	double span[50];
	int arr[n]; 
	fillArray(n, arr); 

	for (i = 0; i < 50; i++)
	{	
		
		gettimeofday(&startTime, NULL); 
		search(n, arr, pivot); 
 		gettimeofday(&endTime, NULL); 
		span[i] = endTime.tv_sec-startTime.tv_sec + (endTime.tv_usec-startTime.tv_usec)/1000000.0; 
		newArray(n, arr, pivot);
		printf ("Test going, iteration #%d was running, testing arraysize %d, used time %lf\n", i, 20000, span[i]);
	}
	double min = span[0];
	double max = span[0];
	double total = 0.0;
	double avg;
	double differ, varsum, SD;
	for(i = 0; i < 50; i++)
	{
		if(span[i] < min) min = span[i];
		if(span[i] > max) max = span[i];
		total += span[i];
	}
	avg = total / 50.0;
	for(i = 0; i < 50; i++)
	{
		differ = span[i] - avg;
		varsum = varsum + pow(differ, 2);
	}
	SD = sqrt(varsum / 50.0);
	printf("The size of arr is %d\nnumber of process = %d\n", 20000, 80); 
 	printf("max time = %.12f\nmin time = %.12f\navg time = %.12f\nstandard deviation = %.12f\n", max, min, avg, SD); 
} 

