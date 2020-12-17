# ComputerArchitecture
## Practica 1
### *Ejercicio 1*

Implementar un programa usando MPI, que imprima por salida estándar:

`“Hola mundo, soy el proceso X de un total de Y.”`

cuando el número total de tareas es Y=50 y X un rango de 0 a 49.

Calcular el speedup con respecto a la versión serie de este programa medida que aumenta el número de procesos lanzados. Realizar gráfica indicando la tendencia. 

### *Ejercicio 2*

Implementar un programa usando MPI, donde el proceso 0 toma un dato del usuario y lo envía al resto de nodos en anillo. Esto es, el proceso i recibe de i-1 y transmite el dato a i+1, hasta que el dato alcanza el último nodo: 

![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/ac1.PNG)

Asumir que el dato que se transmite es un entero y que el proceso cero lee el dato del usuario.
* Modificar la implementación para el dato introducido por el usuario de tantas vueltas como éste indique en el anillo.
* Que desventaja se aprecia en este tipo de comunicaciones punto a punto a medida que aumentan el numero de procesos requeridos. Razonar la respuesta.
* Cómo podría mejorar el sistema y su implemenación. 

[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/colored.png)](#table-of-contents)

## Practica 2
### *Ejercicio 1*

Implementar un código donde utilizando comunicación punto a punto los procesos rebotan continuamente los mensajes entre sí, hasta que deciden detenerse una vez alcanzado límite autoimpuesto. 

### *Ejercicio 2*

Implementar un código, que comunica dos procesos usando comunicación punto a punto. Cada proceso debe enviar un array de datos al otro. Para ello, cada proceso declara dos arrays de floats, A y B, de tamaño fijo (10000). Todas las posiciones del array A se inicializan con los rangos respectivos de los dos procesos. Los arrays A y B serán los buffers para las operaciones de SEND y RECEIVE, respectivamente. El programa termina cuando los 2 procesos imprimen un valor cualquier de sus arrays B.
El programa debe guiarse por el siguiente esquema: 

![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/ac2.PNG)

### *Ejercicio 3*

Implementar un código que usando comunicación punto a punto, lleva a cabo una operación de send/recieve circular, como muestra el siguiente esquema: 

![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/ac2-1.PNG)

Al igual que en el ejercicio anterior, cada proceso genera sus dos buffers A y B con un tamaño de 1000 posiciones inicializadas con sus respectivos rangos en A. Los arrays de tipo B se usan para recibir los mensajes que lleguen del nodo origen. Como se observa, cada proceso envía al que tiene a su derecha y recibe solo del que tiene a su izquierda. Asegurarse de que el programa funcione para un número de procesos arbitrario. 



[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/colored.png)](#table-of-contents)

## Practica 3
### *Ejercicio 1*

Implementar un programa donde el nodo 0 inicializa una variable con un valor arbitrario, después él mismo lo modifica (por ejemplo calculando el cuadrado de su valor) y finalmente lo envía al resto de nodos del comunicador.

* Hacer utilizando comunicación punto a punto.
*  Hacer utilizando comunicación colectiva. 

### *Ejercicio 2*

Implementar un programa donde el nodo 0 inicializa un array unidimensional asignando a cada valor su índice. Este array es dividido en partes, donde cada una de ellas será mandada a un proceso/nodo diferente. Después de que cada nodo haya recibido su porción de datos, los actualiza sumando a cada valor su rank. Por último, cada proceso envía su porción modificada al proceso root. 

`(Hacerlo para que el número de datos total (N) sea múltiplo del número de procesos).`

### *Ejercicio 3*

Implementar un programa donde cada proceso inicializa un array de una dimensión, asignando a todos los elementos el valor de su rank+1. Después el proceso 0 (root) ejecuta dos operaciones de reducción (suma y después producto) sobre los arrays de todos los procesos. 

[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/colored.png)](#table-of-contents)

## Practica 4
### *Ejercicio 1*

Implementar un programa que realice la transposición de la matriz inicial motrada en la figura (parte izquierda):

* Realizar el proceso en paralelo, distribuyendo la matriz entre 4 procesos.

![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/ac3.PNG)

### *Ejercicio 2*

Implementar un programa donde se resuelva el problema de la transposición de matrices cuadradas de dimensión arbitraria NxN (siendo N múltiplo del número de P de procesos). La matriz se dividirá entre P procesos (p<<N) que la inicializarán, de tal modo que cada elemento sea único (para ello usar la posición de la fila y la columna y el
número de rank, como por ejemplo: 1000 * i + j + n/p * rank).

Para ello, distribuir A y B por columnas (o filas), entre los procesos y haciendo uso de las operaciones colectivas que se consideren oportunas llevar a cabo el proceso de transposición. 

![Image of capture](https://raw.githubusercontent.com/JGilR/ComputerArchitecture/master/ac3-1.PNG)

[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/colored.png)](#table-of-contents)
