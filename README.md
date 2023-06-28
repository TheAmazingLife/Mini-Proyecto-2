# Mini-Proyecto-2

## Compilar

Para compilar usar idealmente:

Main metodos, que comprueba el funcionamiento de los metodos countRegion() y aggregateRegion()
> `g++ -O3 mainMetodos.cpp source/*.cpp -o metodos`
> `nice -n -20 ./metodos.exe`

Main insert, que inserta los datos y ejecuta totalPoints() y totalNodes()
> `g++ -O3 mainInsert.cpp source/*.cpp -o insert`
> `nice -n -20 ./insert.exe`

Cada main hace los 20 tests, correspondientes, con diferente cantidad de inserciones
