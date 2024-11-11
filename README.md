# ArtSorter
ArtSorter es una herramienta de línea de comandos para organizar y gestionar imágenes en un directorio. El programa permite cargar, ordenar, listar, abrir imágenes y asignar precios a cada imagen. Es ideal para artistas, fotógrafos o cualquier persona que necesite organizar imágenes y asociarles un valor.

## Características
Organización por tamaño de archivo: Utiliza el algoritmo MergeSort para ordenar las imágenes en función de su tamaño.
Visualización de imágenes: Permite abrir imágenes directamente desde el programa.
Gestión de precios: Los usuarios pueden asignar precios a las imágenes y listarlas.
Soporte para múltiples formatos de imagen: Utiliza la biblioteca stb_image para manejar las imágenes en diferentes formatos.

## Requisitos
C++11 o superior.
Biblioteca stb_image para el manejo de imágenes.
Un sistema operativo compatible con la función std::system("start") (Windows, por ejemplo).
## Compilación e Instalación
Instalar dependencias:

Asegúrate de tener la biblioteca stb_image.h disponible en tu proyecto. 
Compilar el programa: Para compilar el código, usa un compilador de C++ 

```g++ -o ArtSorter main.cpp```
Ejecutar el programa: Una vez compilado, ejecuta el programa:

```ArtSorter.exe```

## Uso
El programa se ejecuta en un bucle interactivo con las siguientes opciones:

```Listar imágenes: ```Muestra una lista de las imágenes en el directorio Proyecto_dibujo, mostrando su nombre, tamaño y dimensiones.

```Abrir imagen:``` Permite al usuario abrir una imagen específica desde el directorio utilizando el programa predeterminado del sistema.

```Listar precios y ordenar:``` Permite asignarle presios a las imagenes y las ordena de mayor a menor respecto al presio.

```Guardar presios en archivo``` Guarda la lista de presios en un .txt y lo abre imediatamente.

```Salir: ```Finaliza el programa.

## Estructura de directorios
El programa busca las imágenes en un directorio llamado Proyecto_dibujo que debe encontrarse en la misma carpeta donde se ejecuta el programa. Asegúrate de tener este directorio con imágenes dentro.




## Comandos y Funciones
#### Listar imágenes:

Muestra una lista de todas las imágenes en el directorio Proyecto_dibujo, ordenadas por tamaño.

Ejemplo:

```Archivo: imagen1.jpg | Size: 1024 bytes | Dimensions: 500x500 px```
#### Abrir imagen:

Permite abrir una imagen usando el visualizador predeterminado del sistema operativo. Escribe el nombre de la imagen que deseas abrir 
(por ejemplo, imagen1.jpg).

#### Listar precios y ordenar:

Ingresa el precio por orden del tamaño y al final los proyecta por orden respecto al presio. Por ejemplo:

Introduce los precios de las imagenes:
Imagen: imagen1.jpg | Precio: $10.00
Imagen: imagen2.jpg | Precio: $8.00

Precios ordenados:
Imagen: imagen2.jpg | Precio: $8.00
Imagen: imagen1.jpg | Precio: $10.00


## Notas
### Compatibilidad con otros sistemas operativos: 
Actualmente, la función std::system("start") es específica de Windows. Para usar este programa en otros sistemas operativos como Linux o macOS, deberás modificar esa parte del código para usar los comandos adecuados (como xdg-open en Linux o open en macOS).

### Tamaño y rendimiento: 
El rendimiento del programa puede verse afectado por la cantidad de imágenes que se cargan. Si el directorio contiene muchas imágenes grandes, la carga y procesamiento pueden tomar un tiempo considerable.

## SICT0301: Evalúa los componentes
Análisis de complejidad del algoritmo de ordenamiento (Merge Sort)
En el programa, se utiliza el algoritmo Merge Sort para ordenar las imágenes por su tamaño. Este algoritmo tiene una complejidad O(m log m), donde m es el número de imágenes a ordenar. Esto se debe a que Merge Sort es un algoritmo de división y conquista, donde el conjunto de datos se divide recursivamente hasta llegar a conjuntos de un solo elemento y luego se fusionan de manera ordenada. El costo de cada fusión es proporcional a O(m) y el número de divisiones es proporcional a log m, lo que da como resultado una complejidad global de O(m log m).

## SICT0302: Toma decisiones
Selección del algoritmo de ordenamiento adecuado
El algoritmo seleccionado es Merge Sort, que es adecuado para el tipo de problema que se enfrenta en este proyecto: ordenar un conjunto de imágenes por su tamaño. Merge Sort es eficiente y tiene un rendimiento garantizado de O(m log m), lo que lo hace adecuado para manejar un gran número de imágenes, incluso cuando el número de imágenes es grande. Si bien existen otros algoritmos de ordenamiento, como QuickSort, Merge Sort se seleccionó debido a su estabilidad y su rendimiento en el peor caso, que es particularmente importante cuando se manejan datos no garantizados de tamaño homogéneo.

## SICT0303: Implementa acciones científicas
Implementación de mecanismos para consultar información de las estructuras correctos
El programa implementa un sistema de consultas para listar imágenes y precios:

Consulta de imágenes: La función listarImagenes recorre el vector imagenes y muestra la información relevante de cada imagen (nombre, tamaño y dimensiones). Esta consulta es O(m), ya que debe recorrer todas las imágenes almacenadas en el vector.

Consulta de precios: La función listarPrecios recorre el mapa precios y muestra el precio asignado a cada imagen. Esta consulta también es O(p), donde p es el número de precios asignados, y es eficiente debido al uso del mapa.

Implementación de mecanismos de lectura de archivos
El programa implementa la lectura de imágenes desde un directorio usando la función opendir para acceder al directorio Proyecto_dibujo. Luego, cada imagen es cargada utilizando la biblioteca stb_image:

Lectura de imágenes: La función stbi_load se usa para cargar las imágenes y obtener sus dimensiones. Si la carga es exitosa, la imagen se agrega al vector imagenes. Esta acción tiene una complejidad de O(m * N), donde m es el número de imágenes y N es el tamaño promedio de cada imagen en píxeles.

Lectura de tamaños de archivo: El tamaño de cada archivo de imagen se obtiene con la función std::filesystem::file_size, lo que permite almacenar el tamaño de cada imagen en el vector de manera eficiente.
