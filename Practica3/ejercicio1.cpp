#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
  int value, rank, cuadrado, size, flag;
  int tag = 201;

  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  if(rank == 0){
    printf("Comunicacion punto a punto (introduce 0). Comunicacion colectiva (introduce 1, esta por defecto): ");
    cin>>flag;
  }

  if(flag == 0){
    // Comunicacion punto a punto
    if(rank == 0){
      printf("Introduzca un numero entero: ");
      cin>>value;
      cuadrado = value * value;
      for(int i = 1; i < size; i++){
        MPI_Send(&cuadrado, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
      }
      printf("Proceso padre ha enviado %d a todos los procesos hijo!\n\n", cuadrado);
    }else{
      MPI_Recv(&cuadrado, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      printf("Proceso %d ha recibido el resultado %d\n", rank, cuadrado);
    }
  }else{
    //Comunicacion colectiva
    if(rank == 0){
      printf("Introduzca un numero entero: ");
      cin>>value;
      cuadrado = value * value; 
    }
    MPI_Bcast(&cuadrado, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if(rank != 0){
      printf("Proceso %d ha recibido el resultado %d\n", rank, cuadrado);
    }
    printf("Proceso padre ha enviado %d a todos los procesos hijo!\n\n", cuadrado);
  }
  MPI_Finalize();
  return 0;
}