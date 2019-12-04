#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N 512 //assume image is 512x512

int main(int argc, char *argv[]){
	int myid, nprocs, i, j;
	int num_elements_per_proc = atoi(argv[1]);

	unsigned char image [N][N];

	for(i = 0; i < N; i ++){
		for(j = 0; j < N; j ++){
			image[i][j] = rand();
		}
	}

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	float *sub_image = (float *)malloc(sizeof(float) * num_elements_per_proc);
	assert(sub_image != NULL);

	MPI_Scatter(image, num_elements_per_proc, MPI_CHAR, sub_image, num_elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD)

	int sub_histogram[num_elements_per_proc]

	for(i = 0; i < nprocs; i ++){
		for(j = 0; j < nprocs; j ++){
			sub_histogram[sub_image[i][j]];
		}
	}

	if(nprocs == 0){
		int histogram[256];
		MPI_Reduce(&sub_hisogram, &histogram, 1, MPI_FLOAT, MPI_NULL, 0, MPI_COMM_WORLD);
	}

	MPI_Barrier(MPI_COMM_WORLD);
  	MPI_Finalize();
	return 0;
}