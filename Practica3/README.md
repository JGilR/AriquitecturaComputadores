## Practica 3
### *Ejercicio 1*

Implementar un programa donde el nodo 0 inicializa una variable con un valor arbitrario, después él mismo lo modifica (por ejemplo calculando el cuadrado de su valor) y finalmente lo envía al resto de nodos del comunicador.

* Hacer utilizando comunicación punto a punto.
*  Hacer utilizando comunicación colectiva. 

```c++
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
```

> Solución:
>- La comunicación punto a punto se basa en enviar un dato desde un proceso a otro individualmente. La comunicación colectiva puede enviar y recibir datos del resto de procesos.
>- En nuestro programa creamos un pequeño menu para selecionar si queremos realizar la com. punto a punto (0) o la com. colectiva (1). Según el *flag (1 o 0)* entraras en el *if* o en el *else*.
>- En la com. punto a punto enviamos y recibimos el dato con las funciones *MPI_Comm_Send(), MPI_Comm_Recv()*.

> ![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/Practica3/Exit_ejercicio1-1.png)

>- En la com. colectiva calculamos el cadrado del numero insertado y lo enviamos desde el proceso 0 al resto de procesos con *MPI_Bcast()*.

> ![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/Practica3/Exit_ejercicio1.png)

### *Ejercicio 2*

Implementar un programa donde el nodo 0 inicializa un array unidimensional asignando a cada valor su índice. Este array es dividido en partes, donde cada una de ellas será mandada a un proceso/nodo diferente. Después de que cada nodo haya recibido su porción de datos, los actualiza sumando a cada valor su rank. Por último, cada proceso envía su porción modificada al proceso root. 

`(Hacerlo para que el número de datos total (N) sea múltiplo del número de procesos).`

### *Ejercicio 3*

Implementar un programa donde cada proceso inicializa un array de una dimensión, asignando a todos los elementos el valor de su rank+1. Después el proceso 0 (root) ejecuta dos operaciones de reducción (suma y después producto) sobre los arrays de todos los procesos. 
