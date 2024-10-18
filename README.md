# ArtSorter - Organizador de Dibujos

ArtSorter es una herramienta para organizar tus archivos de dibujo, clasificándolos de acuerdo a diferentes criterios: nombre, tamaño en bytes o dimensiones de la imagen (ancho y alto). Este proyecto utiliza la biblioteca stb_image para obtener información de los archivos de imagen.

## Instrucciones
### Compilación
Para compilar el proyecto, asegúrate de tener stb_image.h en el mismo directorio que tu archivo main.cpp. Usa el siguiente comando para compilarlo:

```g++ main.cpp```

### Ejecución
El programa se ejecuta en la terminal, accediendo a una carpeta que contiene los archivos de imagen. Al ejecutar el programa, se organizarán los archivos dentro del directorio por tamaño en bytes y se mostrarán sus nombres, tamaños y dimensiones (ancho x alto en píxeles).

### Instrucciones de uso:
Crea un directorio llamado Proyecto_dibujo en el mismo lugar donde se ejecutará el programa.
Coloca los archivos de imagen en ese directorio.
Ejecuta el programa en la terminal:

```./ArtSorter (ó como haya guardado el .exe)```

### Visualización de resultados
Al ejecutar el programa, este mostrará la lista de archivos de imagen ordenados por tamaño en bytes, junto con su nombre, tamaño y dimensiones en píxeles. Un ejemplo de la salida sería:

```Archivo: imagen1.png | Size: 51234 bytes | Dimensions: 800x600 px```

```Archivo: imagen2.jpg | Size: 105678 bytes | Dimensions: 1920x1080 px```

```Archivo: imagen3.bmp | Size: 205678 bytes | Dimensions: 2560x1440 px```

### Requisitos
stb_image.h: Debes tener esta cabecera en la misma carpeta que el archivo main.cpp.
C++17: Se requiere soporte para C++17 para usar las funciones de la biblioteca std::filesystem.

### Funcionalidades
#### Ordenamiento por tamaño en bytes:
Utiliza el algoritmo Merge Sort para organizar los archivos de menor a mayor tamaño.


#### Visualización de dimensiones:
Las imágenes se cargan usando stb_image para obtener su ancho y alto, junto con el número de canales (RGB, RGBA, etc.).

### Algoritmo
El proyecto utiliza el algoritmo de ordenación Merge Sort (el cual tiene ```O(n log n)``` de complejidad independientemente del caso) para ordenar los archivos por su tamaño en bytes, asegurando que los archivos más pequeños se presenten primero.

#### ¿Por qué se escogió un "merge"?
En lugar de usar un shell convencional, se decidió emplear un merge para ejecutar y gestionar este programa debido a las siguientes ventajas:

Productividad mejorada: El merge combina varias características que facilitan la administración y ejecución de comandos, acelerando el flujo de trabajo.
Autocompletado avanzado: A diferencia de otros entornos, el merge proporciona una predicción y autocompletado de comandos de manera más inteligente, ayudando a evitar errores tipográficos y optimizando el tiempo de escritura.
Mayor flexibilidad: Ofrece más opciones de personalización para la ejecución de comandos y configuración del entorno, lo que lo hace más adecuado para proyectos de desarrollo que requieren rapidez y flexibilidad.
Integración mejorada: El merge se integra mejor con otras herramientas y funcionalidades, haciendo que el manejo de archivos, directorios y procesos sea mucho más eficiente y con menos fricción.
Por estas razones, ArtSorter se beneficia al utilizar un merge, facilitando una experiencia de usuario más eficiente y adaptable.
