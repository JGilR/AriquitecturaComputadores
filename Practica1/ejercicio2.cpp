#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv){
    int rank, nproc;
    int read, data;
    int next, from, tag;
    double start, finish, time;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    //
    tag = 201;
    next = (rank + 1) % nproc;
    from = (rank + nproc -1) % nproc;
    // Padre envia datos
    if (rank == 0){
        cout << "Introduzca el numero de vueltas al anillo: ";
        cin >> read;
        printf("\nProceso %d envia %d al proceso %d\n", rank, read, next);
        MPI_Send(&read, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
    }
    // Son receive data and send it to another son.
    else{
        MPI_Recv(&data, 1, MPI_INT, from, tag, MPI_COMM_WORLD, &status);
        printf("\nProceso %d recibe %d\n", rank, data);
        if (rank == nproc - 1){
            finish = MPI_Wtime();
            time = finish - start;
            printf("\nTiempo total del %d proceso: %f\n", nproc, time);
        }
        // Last son do not send data
        if (rank < nproc - 1){
            MPI_Send(&data, 1, MPI_INT, (rank + 1), tag, MPI_COMM_WORLD);
            printf("Proceso %d envia %d\n", rank, data);
        }
    }

    MPI_Finalize();
    return 0;
}