#include <stdio.h>
#include <upc_relaxed.h>

#define N 512	//assume image is 512x512
shared [N*N/THREADS] unsigned char img [N][N] //Shared array with block size N*N/THREADS
shared int histogram[256];
upc_lock_t*lock;

void initialize(void){
	lock = upc_all_lock_alloc();
	CHECK_MEM(lock);

}

int main(void){
	int i, j;
	initialize();
	upc_barrier;
	upc_forall(i = 0; i < N; i ++; i*THREADS/N){
		for(j = 0; j < N; j ++){
			upc_lock(lock);
			histogram[img[i][j]] ++;
			upc_unlock(lock);
		}
	}
	upc_barrier;
	if(MYTHREAD == 0){
		//print histogram
	}
	return 0;
}