#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void printArray(int array[], int count);

int main(int argc, char *argv[]){
  int rank, size;
  int suma[10];
  int mult[10];
  int array[10];

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  for(int i = 0; i < 10; i++){
    array[i] = (int)rank+1;
    //printf("%d ", array[i]);
  }
  //printf("\n");
  
  MPI_Reduce(array, suma, 10, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(array, mult, 10, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
  
  if(rank == 0){
    printf("MPI SUM:\n");
    printArray(suma, 10);
    printf("\n\nMPI MULT:\n");
    printArray(mult, 10);
    printf("\n");
  }

  MPI_Finalize();
  return 0;
}

void printArray(int array[], int count){
  for(int i = 0; i < count; i++){
    printf("%d ", array[i]);
  }
}