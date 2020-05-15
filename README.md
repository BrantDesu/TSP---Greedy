# TSP---Greedy
Implementacion heurística greedy para TSP, entrega 1 IAA.

Cristian Chamorro Brant
201673506-2

Consideraciones:

-Para obtener registro de los outputs, la carpeta "Outputs_TSP" debe estar creada.
-Algunas instancias no coinciden en formato, dado que estaba corto de tiempo preferí modificar directamente los archivos de estas, el problemas al que me refiero es que 3 de ellas en la descripcion de las primeras lineas utiliza un espacio antes de ':' quedando como un string distinto al parsearlo (e.g. NAME : d198 ) el resto de ellas (2) no utilizan ese espacio, por lo que decidí dejarlas todas con la separación. Si se prueban otras instancias y tienen conflictos con el formato, el programa se caerá.
-Dentro del makefile se incluyó una variable "SEEDS" para pasarlas por consola al ejecutar make. Es necesario que haya al menos una seed en los argumentos del main para que el programa se ejecute. 
