#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define GNRL_SIZE 10

float compute_partial_sum(float *array, int num_elements){
	float sum = 0.f;
	int i;
	for (i = 0; i < num_elements; i++) {
  	sum += array[i];
	}
	return sum;
}

float compute_var(float *array, float mean){
	float temp;
	int i;
	for(i = 0; i < GNRL_SIZE; i++){
		temp += (array[i]-mean)*(array[i]-mean);
	}
	return temp/(GNRL_SIZE-1);
}

int main(int argc, char *argv[]){
	int n, myid, nprocs, i;
	int num_elements_per_proc = atoi(argv[1]);

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	if(nprocs == 0){
		double array[GNRL_SIZE];
	}
	// Create buffer that will hold subset of entire array on each process
	float *sub_array = (float *)malloc(sizeof(float) * num_elements_per_proc);
	assert(sub_array != NULL);

  if(nprocs == 0){
    MPI_Scatter(array, num_elements_per_proc, MPI_FLOAT, sub_array, num_elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD)
	}

	float sub_sum = compute_partial_sum(sub_array, num_elements_per_proc);

  if(nprocs == 0){
    float global_sum;
    MPI_Reduce(&sub_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    float mean = global_sum/(nprocs*num_elements_per_proc);
    float var = compute_var(array, mean);
    printf("Mean of all elements is %f \n", mean);
    printf("Variance of all elements is %f \n", var);
  }

	MPI_Barrier(MPI_COMM_WORLD);
  	MPI_Finalize();
	return 0;
}