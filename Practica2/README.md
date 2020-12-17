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

