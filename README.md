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

Ó si estas usando CMD solo ingresa el nombre del exe:

```ArtSorter```

## Uso
El programa se ejecuta en un bucle interactivo con las siguientes opciones:

```Listar imágenes: ```Muestra una lista de las imágenes en el directorio Proyecto_dibujo, mostrando su nombre, tamaño y dimensiones.

```Abrir imagen:``` Permite al usuario abrir una imagen específica desde el directorio utilizando el programa predeterminado del sistema.

```Listar precios y ordenar:``` Permite asignarle presios a las imagenes y las ordena de mayor a menor respecto al presio.

```Guardar presios en archivo``` Guarda la lista de presios en un .txt y lo abre imediatamente.

```Imprimir precios``` Muestra la lista de precios

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

#### Guardar precios en archivo
Te guarda los precios en un archivo .txt al cual puedes acceder en cualquier momento fuerra del programa

#### Imprimir precios
Muestra el nombre de cada archivo seguido del presio asignado, si esque a este ya se le habia dado uno. Por ejemplo:

Imagen: imagen1.jpg | Precio: $7.00


## Notas
### Compatibilidad con otros sistemas operativos: 
Actualmente, la función std::system("start") es específica de Windows. Para usar este programa en otros sistemas operativos como GNU/Linux o macOS, deberás modificar esa parte del código para usar los comandos adecuados (como xdg-open en Linux o open en macOS).

### Tamaño y rendimiento: 
El rendimiento del programa puede verse afectado por la cantidad de imágenes que se cargan. Si el directorio contiene muchas imágenes grandes, la carga y procesamiento pueden tomar un tiempo considerable.

## SICT0301: Evalúa los componentes

### Análisis de Complejidad del Código

### los analisis de complejidad estan dentro del codigo en comentarios

#### 1. Algoritmo de Ordenamiento (Merge Sort)
- En el programa se utiliza el algoritmo Merge Sort para ordenar las imágenes en el vector imagenes por tamaño. La complejidad de Merge Sort es O(m log m), donde m es el número de imágenes. Este algoritmo es de división y conquista: el conjunto de datos se divide en subgrupos recursivamente hasta llegar a conjuntos de un solo elemento, que luego se fusionan en orden. Dado que el costo de cada operación de fusión es proporcional a O(m) y el proceso de división tiene una profundidad de log m, la complejidad total es O(m log m).

- Mejor caso: O(m log m). Merge Sort siempre requiere el mismo número de comparaciones y fusiones, sin importar el orden de los elementos, debido a su naturaleza recursiva y estructura fija. Por ello, su rendimiento es constante en cualquier situación.
- Peor caso: O(m log m). Como Merge Sort no depende del orden inicial de los elementos (no tiene peor caso en comparación con Quick Sort, por ejemplo), el rendimiento en el peor caso también es O(m log m).

- Conclucion:
Merge Sort es estable (preserva el orden de elementos iguales) y predecible en su complejidad. A pesar de que requiere memoria adicional para almacenar las submatrices y la matriz final, su rendimiento consistente y estabilidad en cualquier caso lo hacen ideal para ordenar un conjunto de elementos en el que el espacio extra no es un inconveniente.

#### 2. Función listarImagenes
   - La función listarImagenes recorre el vector imagenes y muestra los detalles de cada imagen. Su complejidad es **O(m)**, donde \( m \) es el número de imágenes en el vector. Esto se debe a que la función realiza una operación constante para cada imagen sin procesos adicionales de ordenamiento o búsqueda.

#### 3. Función ordenarPrecios
   - Para ordenar y mostrar los precios, se convierte el map de precios a un vector y se ordena utilizando std::sort, lo que tiene una complejidad de **O(n \log n)**, donde \( n \) es el número de precios. La ordenación en este caso se realiza en función de los precios, y std::sort tiene una eficiencia de \( O(n \log n) \), similar al Merge Sort.

#### 4. Función archivoprecio
   - Esta función guarda los precios en un archivo de texto. Recorre todos los elementos en el map de precios para escribir cada par en el archivo, con una complejidad de **O(n)**, donde \( n \) es la cantidad de precios. No realiza ninguna operación de ordenamiento ni búsqueda, solo recorre el map una vez.

#### 5. Función abrirImagen
   - La función abrirImagen recorre el vector de imagenes buscando una coincidencia con el nombre ingresado por el usuario. Esto implica una búsqueda lineal, resultando en una complejidad de **O(m)**, donde \( m \) es el número de imágenes. En el peor de los casos, el programa deberá recorrer todo el vector antes de encontrar el nombre o determinar que no existe.

#### 6. Función main
   - En el main, el código realiza operaciones de lectura de archivos, ordenamiento y manipulación de las imágenes en el vector y precios en el mapa. El paso más costoso es el ordenamiento con Merge Sort en el vector imagenes, lo cual domina la complejidad global del programa, resultando en una complejidad general de **O(m \log m)**. La lectura de archivos y otras operaciones en main son lineales o constantes y no afectan significativamente la complejidad global del programa.

#### Complejidad Global
La complejidad del programa está dominada por el algoritmo de ordenamiento (Merge Sort), que tiene una complejidad de **O(m \log m)**, donde \( m \) es el número de imágenes a ordenar. En términos de espacio, la complejidad es de **O(m + n)**, donde \( m \) representa las imágenes almacenadas en el vector y \( n \) los precios en el mapa.

## SICT0302: Toma decisiones
El algoritmo seleccionado es Merge Sort, que es adecuado para el tipo de problema que se enfrenta en este proyecto: ordenar un conjunto de imágenes por su tamaño. Merge Sort es eficiente y tiene un rendimiento garantizado de O(m log m), lo que lo hace adecuado para manejar un gran número de imágenes, incluso cuando el número de imágenes es grande. Si bien existen otros algoritmos de ordenamiento, como QuickSort, Merge Sort se seleccionó debido a su estabilidad y su rendimiento en el peor caso, que es particularmente importante cuando se manejan datos no garantizados de tamaño homogéneo.

## SICT0303: Implementa acciones científicas
El programa implementa un sistema de consultas para listar imágenes y precios:

Consulta de imágenes: La función listarImagenes recorre el vector imagenes y muestra la información relevante de cada imagen (nombre, tamaño y dimensiones). Esta consulta es O(m), ya que debe recorrer todas las imágenes almacenadas en el vector.

Consulta de precios: La función listarPrecios recorre el mapa precios y muestra el precio asignado a cada imagen. Esta consulta también es O(p), donde p es el número de precios asignados, y es eficiente debido al uso del mapa.

Implementación de mecanismos de lectura de archivos
El programa implementa la lectura de imágenes desde un directorio usando la función opendir para acceder al directorio Proyecto_dibujo. Luego, cada imagen es cargada utilizando la biblioteca stb_image:

Lectura de imágenes: La función stbi_load se usa para cargar las imágenes y obtener sus dimensiones. Si la carga es exitosa, la imagen se agrega al vector imagenes. Esta acción tiene una complejidad de O(m * N), donde m es el número de imágenes y N es el tamaño promedio de cada imagen en píxeles.

Lectura de tamaños de archivo: El tamaño de cada archivo de imagen se obtiene con la función std::filesystem::file_size, lo que permite almacenar el tamaño de cada imagen en el vector de manera eficiente.

## Respecto a alerta de AI 
Le explico que paso:
- trabaje con librerias que no habia usado antes, asi que en la mayoria le pedi a Chatgpt que generara un ejemplos y de ahi me base. Es posible, que le salga alerta ya que me base mucho es ello
- Comentarios: los analisis de complegidad los pedi a un Ai ya que en cierto punto ya no entendi como estaba contando jaja
- Archivo.h stb_image: esta un una libreria de Github que descarge para usar
- Archivo.h PriceRead: como dije en la parte de comentarios, puse las funciones para sacar el analisis de complegidad, pero esta funcion (apesar del comentario de lambda) fue hecho totalmente a mano con ayuda de un amigo ya que no sabia que estaba haciendo
