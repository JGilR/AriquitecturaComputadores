# ComputerArchitecture
## Practica 1
### *Ejercicio 1*

Implementar un programa usando MPI, que imprima por salida estándar:
`“Hola mundo, soy el proceso X de un total de Y.”`

cuando el número total de tareas es Y=50 y X un rango de 0 a 49.

Calcular el speedup con respecto a la versión serie de este programa medida que aumenta el número de procesos lanzados. Realizar gráfica indicando la tendencia. 

### *Ejercicio 2*

Implementar un programa usando MPI, donde el proceso 0 toma un dato del usuario y lo envía al resto de nodos en anillo. Esto es, el proceso i recibe de i-1 y transmite el dato a i+1, hasta que el dato alcanza el último nodo: 



Asumir que el dato que se transmite es un entero y que el proceso cero lee el dato del usuario.
* Modificar la implementación para el dato introducido por el usuario de tantas vueltas como éste indique en el anillo.
* Que desventaja se aprecia en este tipo de comunicaciones punto a punto a medida que aumentan el numero de procesos requeridos. Razonar la respuesta.
* Cómo podría mejorar el sistema y su implemenación. 

## Practica 2
### *Ejercicio 1*

Implementar un código donde utilizando comunicación punto a punto los procesos rebotan continuamente los mensajes entre sí, hasta que deciden detenerse una vez alcanzado límite autoimpuesto. 

### *Ejercicio 2*

Implementar un código, que comunica dos procesos usando comunicación punto a punto. Cada proceso debe enviar un array de datos al otro. Para ello, cada proceso declara dos arrays de floats, A y B, de tamaño fijo (10000). Todas las posiciones del array A se inicializan con los rangos respectivos de los dos procesos. Los arrays A y B serán los buffers para las operaciones de SEND y RECEIVE, respectivamente. El programa termina cuando los 2 procesos imprimen un valor cualquier de sus arrays B.
El programa debe guiarse por el siguiente esquema: 



### *Ejercicio 3*

Implementar un código que usando comunicación punto a punto, lleva a cabo una operación de send/recieve circular, como muestra el siguiente esquema: 



Al igual que en el ejercicio anterior, cada proceso genera sus dos buffers A y B con un tamaño de 1000 posiciones inicializadas con sus respectivos rangos en A. Los arrays de tipo B se usan para recibir los mensajes que lleguen del nodo origen. Como se observa, cada proceso envía al que tiene a su derecha y recibe solo del que tiene a su izquierda. Asegurarse de que el programa funcione para un número de procesos arbitrario. 



## Practica 3




## Practica 4


