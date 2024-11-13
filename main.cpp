#include <iostream>
#include <fstream>
#include <filesystem>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include <stack>
#include <utility>
#include <algorithm>
#include "PriceRead.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct plant {
    std::string name;
    uintmax_t size = 0;
    std::string path;
    int width = 0;
    int height = 0;
    int channels = 0;
};

// Función de mezcla para Merge Sort
// Complejidad de tiempo (mejor y peor caso): O(n)
// Complejidad de espacio (mejor y peor caso): O(n)
void merge(std::vector<plant>& imagenes, int left, int mid, int right) {  

    int n1 = mid - left + 1; 
    int n2 = right - mid;
    std::vector<plant> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = imagenes[left + i];
    for (int i = 0; i < n2; ++i)
        R[i] = imagenes[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].size <= R[j].size) {
            imagenes[k] = L[i];
            i++;
        } else {
            imagenes[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        imagenes[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        imagenes[k] = R[j];
        j++;
        k++;
    }
}

// Función Merge Sort para ordenar imágenes
    // Complejidad de tiempo (mejor y peor caso): O(n log n)
    // Complejidad de espacio (mejor y peor caso): O(n)
void mergeSort(std::vector<plant>& imagenes, int left, int right) {
    
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(imagenes, left, mid);
        mergeSort(imagenes, mid + 1, right);
        merge(imagenes, left, mid, right);
    }
}

// Función para ordenar precios
// Complejidad de tiempo (mejor caso): O(n) - Si ya está ordenado
// Complejidad de tiempo (peor caso): O(n log n) - Cuando se necesita ordenar
// Complejidad de espacio (mejor y peor caso): O(n) - Para almacenar en el vector auxiliar
void ordenarPrecios(std::stack<std::pair<std::string, double>> precios) {  

    std::vector<std::pair<std::string, double>> precios_vec;

    while (!precios.empty()) {
        precios_vec.push_back(precios.top());
        precios.pop();
    }

    // Ordenar precios
    std::sort(precios_vec.begin(), precios_vec.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Imprimir precios ordenados
    std::cout << "\nPrecios ordenados:\n";
    for (const auto& p : precios_vec) {
        std::cout << "Imagen: " << p.first << " | Precio: $" << p.second << "\n";
    }
}


// Función para guardar precios ordenados en un archivo
// Complejidad temporal total: O(n log n) debido al proceso de ordenamiento
// Complejidad espacial total: O(n) debido al uso del vector temporal precios_vec
void archivopresio(std::stack<std::pair<std::string, double>> precios) {  

    // Transferir precios Complejidad temporal O(n)
    std::vector<std::pair<std::string, double>> precios_vec;
    while (!precios.empty()) {
        precios_vec.push_back(precios.top());
        precios.pop();
    }

    // Ordenar precios (Complejidad temporal O(n log n))
    std::sort(precios_vec.begin(), precios_vec.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Guardar precios ordenados en el archivo
    std::ofstream archivo("precios.txt");
    if (archivo.is_open()) {
        // Complejidad temporal O(n)
        for (const auto& p : precios_vec) {
            archivo << "Imagen: " << p.first << " | Precio: $" << p.second << "\n";
        }
        archivo.close();
        std::cout << "\nDatos ordenados guardados en precios.txt\n";
        std::system("start precios.txt"); // Abre el archivo automáticamente
    } else {
        std::cout << "\nError al abrir el archivo para guardar los precios.\n";
    }
}

// Función para listar imágenes
// Complejidad de tiempo (mejor y peor caso): O(n)
// Complejidad de espacio (mejor y peor caso): O(1)
void listarImagenes(const std::vector<plant>& imagenes) { 

    for (const auto& img : imagenes) {
        std::cout << "Archivo: " << img.name
                  << " | Size: " << img.size << " bytes"
                  << " | Dimensions: " << img.width << "x" << img.height << " px\n";
    }
}

// Función para abrir una imagen específica
// Complejidad de tiempo (mejor caso): O(1) - Imagen encontrada al inicio
// Complejidad de tiempo (peor caso): O(n) - Imagen no encontrada
// Complejidad de espacio (mejor y peor caso): O(1)
void abrirImagen(const std::vector<plant>& imagenes, std::stack<plant>& historial) { 

    std::string nombreImagen;
    std::cout << "\nEscribe el nombre de la imagen que deseas abrir: ";
    std::getline(std::cin, nombreImagen);
    for (const auto& img : imagenes) {
        if (img.name == nombreImagen) {
            std::cout << "Abriendo imagen: " << img.name << "\n";
            std::string comando = "start " + img.path;
            std::system(comando.c_str());   

            historial.push(img); // agregar a historial
            return;
        }
    }
    std::cout << "Imagen no encontrada.\n";
}

void abrirHistorial(std::stack<plant>historial){  // Complejidad espacial O(1) ya que solo se usa una variable adicional para almacenar el elemento
    if (!historial.empty()){
        plant img = historial.top();
        
        std::cout << "Abriendo imagen anterior\n";
        std::string comando = "start " + img.path;
        std::system(comando.c_str());

    }else{
        std::cout << "No hay imagenes en el historial.\n";
    }
}

int main() {
    std::string folder = "Proyecto_dibujo";
    DIR* dr;
    struct dirent* en;

    std::vector<plant> imagenes;
    std::stack<std::pair<std::string, double>> precios;
    std::stack<plant> historial;

    // Leer imágenes
    dr = opendir(folder.c_str());
    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            std::string filename = en->d_name;
            if (filename != "." && filename != "..") {
                plant img;
                img.name = filename;
                img.path = folder + "/" + filename;

                std::filesystem::path filepath = img.path;
                if (std::filesystem::is_regular_file(filepath)) {
                    img.size = std::filesystem::file_size(filepath);
                    unsigned char* data = stbi_load(img.path.c_str(), &img.width, &img.height, &img.channels, 0);
                    if (data) {
                        stbi_image_free(data);
                    }
                }
                imagenes.push_back(img);
            }
        }
        closedir(dr);
    } else {
        std::cerr << "No se pudo abrir el directorio: " << folder << std::endl;
        return 1;
    }

    mergeSort(imagenes, 0, imagenes.size() - 1);

    int opcion = 0;
    do {
        std::cout << "\nMenu de opciones:\n";
        std::cout << "1. Listar imagenes nuevamente\n";
        std::cout << "2. Abrir imagen\n";
        std::cout << "3. Abrir imagen anterior\n";
        std::cout << "4. Introducir y ordenar precios\n";
        std::cout << "5. Guardar precios en archivo\n";
        std::cout << "6. Mostrar precios \n";
        std::cout << "7. Salir\n";
        std::cout << "Elige una opcion: ";
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar el buffer

        switch (opcion) {
            case 1:
                listarImagenes(imagenes);
                break;
            case 2:{
                abrirImagen(imagenes,historial);
                if (!historial.empty()) {
                    std::cout << "Historial actualizado"<< "\n";
                } else {
                    std::cout << "\n";
                }
                break;
            }
            case 3: {
                abrirHistorial(historial);
                break;
            }
            case 4: {
                std::cout << "\nIntroduce los precios de las imagenes:\n";
                for (const auto& img : imagenes) {
                    double precio;
                    std::cout << "Precio de " << img.name << ": $";
                    std::cin >> precio;
                    precios.push({img.name, precio});
                }
                ordenarPrecios(precios);
                break;
            }
            case 5:
                archivopresio(precios);
                break;
            case 6: { 
                std::map<std::string, double> preciosDesdeArchivo;
                std::string nombreArchivo = "precios.txt";
                ReadPriceFromFile(nombreArchivo, preciosDesdeArchivo);
                PrintPrecio(preciosDesdeArchivo);
                break;
            }
            case 7:
                std::cout << "Ya me void ...\n";
                break;
            default:
                std::cout << "Opcion no válida, intenta de nuevo.\n";
        }
    } while (opcion != 6);

    return 0;
}
