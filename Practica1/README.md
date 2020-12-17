## Practica 1
### *Ejercicio 1*

Implementar un programa usando MPI, que imprima por salida estándar:

`“Hola mundo, soy el proceso X de un total de Y.”`

cuando el número total de tareas es Y=50 y X un rango de 0 a 49.

Calcular el speedup con respecto a la versión serie de este programa medida que aumenta el número de procesos lanzados. Realizar gráfica indicando la tendencia. 

```c
#include <stdio.h>
#include <mpi.h>


int main(int argc, char** argv){
    int nproc, myrank;
    double start, finish, time;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();
    printf("Hola mundo, soy el proceso %d de un total %d.\n", myrank, nproc);
    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();
    time = finish - start;
    printf("Total time of %d: %f\n", myrank, time);

    MPI_Finalize();

    return 0;
}
```


### *Ejercicio 2*

Implementar un programa usando MPI, donde el proceso 0 toma un dato del usuario y lo envía al resto de nodos en anillo. Esto es, el proceso i recibe de i-1 y transmite el dato a i+1, hasta que el dato alcanza el último nodo: 

![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/ac1.PNG)

Asumir que el dato que se transmite es un entero y que el proceso cero lee el dato del usuario.
* Modificar la implementación para el dato introducido por el usuario de tantas vueltas como éste indique en el anillo.
* Que desventaja se aprecia en este tipo de comunicaciones punto a punto a medida que aumentan el numero de procesos requeridos. Razonar la respuesta.
* Cómo podría mejorar el sistema y su implemenación.

```c++
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
```
