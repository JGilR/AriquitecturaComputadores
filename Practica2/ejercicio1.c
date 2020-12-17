#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char *argv[]){
    int rank;
    char msg[20];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int tag = 201;
    int cont = 0;
    int limite = 3;
    do{
        if(rank == 0){
            printf("MASTER SENDING, Message id: %d\n", cont);
            strcpy(msg, "HELLO WORLD!");
            MPI_Send(msg, 13, MPI_CHAR, 1, tag, MPI_COMM_WORLD);
            if(cont != 0){
                MPI_Recv(msg, 13, MPI_CHAR, 1, tag, MPI_COMM_WORLD, &status);
                printf("MASTER RECEIVE: %s, Message id: %d\n", msg, cont);
            }
        }else{
            MPI_Recv(msg, 13, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
            printf("_SECOND RECEIVE: %s, Message id: %d\n", msg, cont);
            MPI_Get_count(&status, MPI_CHAR, &cont);
            printf("_SECOND SENDING, Message id: %d\n", cont);
            strcpy(msg, "HOLA MUNDO!");
            MPI_Send(msg, 13, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
        }
        cont++;
    }while (cont != limite);
        
    MPI_Finalize();
    return 0;
}