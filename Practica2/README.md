## Practica 2
### *Ejercicio 1*

Implementar un código donde utilizando comunicación punto a punto los procesos rebotan continuamente los mensajes entre sí, hasta que deciden detenerse una vez alcanzado límite autoimpuesto. 

```c
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
```

> Solución:
>- Hemos creado una variable *cont* y otra *limite* para asegurarnos de que cuando llega al limite el contador, el programa finaliza. 
>- Para este ejercicio creamos un *do-while()* con la condición de que el contador no llegue al limite. En el proceso 0 copiamos un mensaje en el buffer y lo enviamos al proceso 1. El proceso 1 recibe el mensaje y lo vuelve a enviar al proceso 0. Asi el mensaje va rebotando hasta llegar al límite.

> ![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/Practica2/Exit_ejercicio1.png)


### *Ejercicio 2*

Implementar un código, que comunica dos procesos usando comunicación punto a punto. Cada proceso debe enviar un array de datos al otro. Para ello, cada proceso declara dos arrays de floats, A y B, de tamaño fijo (10000). Todas las posiciones del array A se inicializan con los rangos respectivos de los dos procesos. Los arrays A y B serán los buffers para las operaciones de SEND y RECEIVE, respectivamente. El programa termina cuando los 2 procesos imprimen un valor cualquier de sus arrays B.
El programa debe guiarse por el siguiente esquema: 

![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/ac2.PNG)

```c
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
```

> Solución:
>- En este ejercicio nos piden la misma comunicación punto a punto y terminan cuando los 2 procesos reciben un valor cualquiera de sus arrays.
>- Asi lo primero es inicializar los arrays (*linea 75-77 y linea 83-85*).
>- PROCESO 1: envía el array (a) y recibe el array (b). Luego imprime un valor cualquiera aleatorio del array (b).
>- PROCESO 2: realiza lo mismo que el primer procesa hasta que imprime un valor cualquiera aleatorio del array (b).

> ![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/Practica2/Exit_ejercicio2.png)

### *Ejercicio 3*

Implementar un código que usando comunicación punto a punto, lleva a cabo una operación de send/recieve circular, como muestra el siguiente esquema: 

![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/ac2-1.PNG)

Al igual que en el ejercicio anterior, cada proceso genera sus dos buffers A y B con un tamaño de 1000 posiciones inicializadas con sus respectivos rangos en A. Los arrays de tipo B se usan para recibir los mensajes que lleguen del nodo origen. Como se observa, cada proceso envía al que tiene a su derecha y recibe solo del que tiene a su izquierda. Asegurarse de que el programa funcione para un número de procesos arbitrario.


```c
#include <stdio.h>
#include "mpi.h"

#define SIZE 10000

int main(int argc, char *argv[]){
    int rank, nproc, count;
    int tag = 201;
    
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    
    if(rank == 0){
        float a[SIZE], b[SIZE];
        for(int i = 0; i < SIZE; i++){
            a[i] = rank;
        }
        MPI_Send(a, SIZE, MPI_FLOAT, 1, tag, MPI_COMM_WORLD);
        printf("Process %d:\n Send %lf to process %d\n\n", rank, a[300], (rank+1));
        MPI_Recv(b, SIZE, MPI_FLOAT, (nproc - 1), tag, MPI_COMM_WORLD, &status);
        printf("Process %d:\n Receive %lf from process %d\n\n", rank, b[300], (nproc - 1));
    }else{
        float a[SIZE], b[SIZE];
        for(int i = 0; i < SIZE; i++){
            a[i] = rank;
        }
        MPI_Recv(b, SIZE, MPI_FLOAT, (rank - 1), tag, MPI_COMM_WORLD, &status);
        printf("Process %d:\n Receive %lf from process %d\n\n", rank, b[300], (rank - 1));
        MPI_Get_count(&status, MPI_CHAR, &count);
        if(rank == (nproc - 1)){ // Tail
            MPI_Send(a, SIZE, MPI_FLOAT, 0, tag, MPI_COMM_WORLD);
            printf("Process %d:\n Send %lf to process %d\n\n", rank, a[300], 0);
        }else{
            MPI_Send(a, SIZE, MPI_FLOAT, (rank + 1), tag, MPI_COMM_WORLD);
            printf("Process %d:\n Send %lf to process %d\n\n", rank, a[300], (rank+1));
        }
    }
    MPI_Finalize();
    return 0;
}
```

> Solución:
>- Al igual que el ejercicio anterior inicializamos los array (a y b). 
>- Siguiendo el esquema propuesto cada proceso envia al proceso de su derecha y reciben solo los de la izquierda. 


> ![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/Practica2/Exit_ejercicio3.png)


