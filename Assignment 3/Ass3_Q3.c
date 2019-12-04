#include <stdio.h>
#include <upc.h>
#define GNRL_SIZE 10	//Assume the array size is 10
shared int arr0[GNRL_SIZE];	//shared array distributed acros threads
shared int partial_sums[THREADS];	//shared array with one integer per thread
shared int sum;				//sum will have affinity to thread 0
shared int mean;			//mean will have affinity to thread 0
shared int var;				//var will have affinity to thread 0

main(){
	int i, temp;
	upc_forall(i = 0; i < GNRL_SIZE; i ++; i){
		partial_sums[MYTHREAD] += arr0[i];		//calculate partial sums for each thread
	}
	upc_barrier;	//wait until all partial sums calculated

	if(MYTHREAD == 0){
		for(i = 0; i < THREADS; i ++){
			sum += partial_sums[i];		//sum the partial sums
		}
		mean = sum/GNRL_SIZE;			//calculate mean
		for(i = 0; i < GNRL_SIZE; i ++){	
			temp += (arr0[i]-mean)*(arr0[i]-mean);
		}	
		var = temp/(GNRL_SIZE - 1);		//calculate variance
		printf("Mean = %i\tVariance = %i\n", mean, var);
	}
}