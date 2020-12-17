#include <stdio.h>
#include "mpi.h"

#define SIZE 10000

int main(int argc, char *argv[]){
    int rank, count;
    int tag = 201;
    
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank == 0){
        float a[SIZE], b[SIZE];
        for(int i = 0; i < SIZE; i++){
            a[i] = rank;
        }
        MPI_Send(a, SIZE, MPI_FLOAT, 1, tag, MPI_COMM_WORLD);
        MPI_Recv(b, SIZE, MPI_FLOAT, 1, tag, MPI_COMM_WORLD, &status);
        printf("Process %d:\nValue from random index of array B: %lf\n\n", rank, b[300]);
    }else{
        float a[SIZE], b[SIZE];
        for(int i = 0; i < SIZE; i++){
            a[i] = rank;
        }
        MPI_Recv(b, SIZE, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &count);
        MPI_Send(a, SIZE, MPI_FLOAT, 0, tag, MPI_COMM_WORLD);
        printf("Process %d:\nValue from random index of array B: %lf\n\n", rank, b[200]);
    }
    MPI_Finalize();
    return 0;
}
