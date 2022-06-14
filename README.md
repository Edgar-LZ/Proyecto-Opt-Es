# Proyecto Optimización Estocástica

Repositorio creado para documentos y código relacionados con el proyecto de clase.

# Compilación y ejecución

Para compilar el proyecto se deben ejecutar los siguientes comandos:
* Primero nos movemos a la carpeta build 
```bash
	cd build
```
* Después ejecutamos el siguiente comando 
```bash
	cmake ..
```
* Con esto podemos construir el proyecto
```bash
	cmake --build .
```

Una vez hecho esto, se habrá compilado y generado un ejecutable que se encuentra
en la carpeta raiz bajo el nombre `TSP_run`. Para ejecutar el programa se llama el siguiente comando:
```bash
./TSP_run <semilla> <archivo de entrada> <archivo de salida> <Algoritmo> <Argumentos opcionales del genético>
```
un ejemplo de ejecución para el Algoritmo Genético sería
```bash
./TSP_run 1234 instances/fri26.tsp out/out.txt genetic inv 1
```

En el algoritmo se escribe `genetic` o `localsearch` si se elige el algoritmo genético, se tienen que incluir dos argumentos más, el primero es el tipo de cruza a utilizar, pueden ser `ord` para cruza ordenada e `inv` para cruza utilizando la secuencias de inversión. Después el último argumento es 1 o 0 si se quiere utilizar búsqueda local en el algoritmo genético o no, respectivamente.
