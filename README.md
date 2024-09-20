# ArtSorter - Organizador de Dibujos

ArtSorter es una herramienta para organizar tus archivos de dibujo, clasificándolos de acuerdo a diferentes criterios: nombre, tamaño en bytes o dimensiones de la imagen (ancho y alto). Este proyecto utiliza la biblioteca stb_image para obtener información de los archivos de imagen.

## Instrucciones de uso
### Compilación
Para compilar el proyecto, asegúrate de tener stb_image.h en el mismo directorio que tu archivo main.cpp. Usa el siguiente comando para compilarlo:

g++ main.cpp


### Ejecución
El programa se ejecuta en la terminal, accediendo a una carpeta que contiene los archivos de imagen. Al ejecutar el programa, se organizarán los archivos dentro del directorio por tamaño en bytes y se mostrarán sus nombres, tamaños y dimensiones (ancho x alto en píxeles).

### Instrucciones de uso:

Crea un directorio llamado Proyecto_dibujo en el mismo lugar donde se ejecutará el programa.
Coloca los archivos de imagen en ese directorio.
Ejecuta el programa en la terminal:
bash
Copiar código
./ArtSorter

### Visualización de resultados
Al ejecutar el programa, este mostrará la lista de archivos de imagen ordenados por tamaño en bytes, junto con su nombre, tamaño y dimensiones en píxeles. Un ejemplo de la salida sería:

Archivo: imagen1.png | Size: 51234 bytes | Dimensions: 800x600 px
Archivo: imagen2.jpg | Size: 105678 bytes | Dimensions: 1920x1080 px
Archivo: imagen3.bmp | Size: 205678 bytes | Dimensions: 2560x1440 px

### Requisitos
stb_image.h: Debes tener esta cabecera en la misma carpeta que el archivo main.cpp.
C++17: Se requiere soporte para C++17 para usar las funciones de la biblioteca std::filesystem.

### Funcionalidades
#### Ordenamiento por tamaño en bytes:
Utiliza el algoritmo Selection Sort para organizar los archivos de menor a mayor tamaño.

#### Visualización de dimensiones:
Las imágenes se cargan usando stb_image para obtener su ancho y alto, junto con el número de canales (RGB, RGBA, etc.).

### Algoritmo
El proyecto utiliza el algoritmo de ordenación Selection Sort (el cual tiene O(n^2) de complejidad independientemente del caso) para ordenar los archivos por su tamaño en bytes, asegurando que los archivos más pequeños se presenten primero.

## Subcompetencias
SICT0301: Evalúa los componentes
Cada archivo de imagen tiene características como tamaño en bytes, ancho y alto, que son evaluadas para su correcta organización y visualización.

SICT0302: Toma decisiones
El algoritmo de ordenación Selection Sort fue elegido por su simplicidad para comparar archivos por tamaño en este contexto.
