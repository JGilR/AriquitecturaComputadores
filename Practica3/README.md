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

```c++
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int globaldata[4];
    int localdata;

    int i;
    if (rank == 0) {

        for (i=0; i<size; i++)
            globaldata[i] = i;

        printf("1. Processor %d has data: ", rank);
        for (i=0; i<size; i++)
            printf("%d ", globaldata[i]);
        printf("\n");
    }

    MPI_Scatter(globaldata, 1, MPI_INT, &localdata, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("2. Processor %d has data %d\n", rank, localdata);
    localdata = localdata + rank;
    printf("3. Processor %d now has %d\n", rank, localdata);

    MPI_Gather(&localdata, 1, MPI_INT, globaldata, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("4. Processor %d has data: ", rank);
        for (i=0; i<size; i++)
            printf("%d ", globaldata[i]);
        printf("\n");
    }


    MPI_Finalize();
    return 0;
}
```

> Solución:
>- Inicializamos nuestro array *globaldata[4]* asignando cada valor a su indice (*{0,1,2,3}*) con un simple *for*.
>- Para dividir el array y poder enviar un elemento a cada proceso utilizamos la función *MPI_Scatter()* y le pasamos nuestro array inicial *&globaldata* y el elemento que almacenaremos en una variable *localdata*. 
>- Una vez divididos los elementos realizamos la actualización pedida (*localdata = localdata + rank*), y cada proceso envía su modificación de nuevo al proceso 0 (*root*) con la función *MPI_Gather()*, asi nuestro array modificado será = {0,2,4,6}.

> ![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/Practica3/Exit_ejercicio2.png)

### *Ejercicio 3*

Implementar un programa donde cada proceso inicializa un array de una dimensión, asignando a todos los elementos el valor de su rank+1. Después el proceso 0 (root) ejecuta dos operaciones de reducción (suma y después producto) sobre los arrays de todos los procesos. 

```c++
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
```

> Solución:
>- En este ejercicio nos piden inicializar un array asignando a todos sus elementos el valor *rank + 1*, eso lo realizamos con un simple *for()*, y realizar dos operaciones de reduccion sobre los arrays. 
>- Para aplicar esa reducción utilizamos *MPI_Reduce()* y le pasamos el parámetro *MPI_SUM* (para sumar) o *MPI_PROD* (para multiplicar). Con esto se realizaran las operaciones sobre los elementos de cada array. 
>- Asi llegamos a los resultados, el array del proceso 0 son todo unos, el del proceso 1 son todo doses, el del proceso 2 son todo treses y el del proceso 3 son todo cuatros. Si sumamos cada elemento de cada uno de los arrays (*proc0[0]+proc1[0]+proc2[0]+proc3[0] = 1+2+3+4 = 10*) el array que contiene los resultados de la suma serán todo dieces.
>- Pasará lo mismo con la multiplicación (*1x2x3x4 = 24*).

> ![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/Practica3/Exit_ejercicio3.png)
