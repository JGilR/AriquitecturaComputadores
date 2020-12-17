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
