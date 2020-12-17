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
