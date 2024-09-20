#include <iostream>
#include <fstream>
#include <filesystem>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION // Definir esta macro antes de incluir stb_image.h
#include "stb_image.h" // Asegúrate de tener stb_image.h en la carpeta junto al main

// Estructura para almacenar los datos de las imágenes
struct plant {
    std::string name;
    uintmax_t size = 0;
    std::string path;
    int width = 0;    // Ancho de la imagen
    int height = 0;   // Alto de la imagen
    int channels = 0; // Número de canales de la imagen (RGB, RGBA, etc.)
};

// Algoritmo Selection Sort para ordenar las imágenes por tamaño
void selectionSort(std::vector<plant>& imagenes) {
    int n = imagenes.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (imagenes[j].size < imagenes[minIndex].size) {
                minIndex = j;
            }
        }
        // Intercambiar el menor encontrado con el primer elemento no ordenado
        if (minIndex != i) {
            std::swap(imagenes[i], imagenes[minIndex]);
        }
    }
}

int main() {
    std::string folder = "Proyecto_dibujo";
    DIR* dr;
    struct dirent* en;

    std::vector<plant> imagenes;

    // Abrir el directorio
    dr = opendir(folder.c_str());
    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            std::string filename = en->d_name;

            // Evitar archivos "." y ".."
            if (filename != "." && filename != "..") {
                plant img;
                img.name = filename;
                img.path = folder + "/" + filename;

                // Verificar si es un archivo regular y no un directorio
                std::filesystem::path filepath = img.path;
                if (std::filesystem::is_regular_file(filepath)) {
                    // Obtener el tamaño del archivo
                    img.size = std::filesystem::file_size(filepath);

                    // Leer la imagen usando stb_image.h
                    unsigned char* data = stbi_load(img.path.c_str(), &img.width, &img.height, &img.channels, 0);
                    if (data) {
                        // La imagen fue cargada correctamente y ahora tenemos sus dimensiones
                        stbi_image_free(data); // Liberar la memoria de la imagen después de usarla
                    } else {
                        std::cerr << "No se pudo abrir la imagen: " << img.path << ".\n"; // Enviar mensajes de error/advertencias "std::cerr"
                    }
                }

                imagenes.push_back(img);
            }
        }
        closedir(dr);
    } else {
        std::cerr << "No se pudo abrir el directorio: " << folder << std::endl;
        return 1; // Salir con error si no se puede abrir el directorio
    }

    // Ordenar las imágenes por tamaño usando Selection Sort
    selectionSort(imagenes);
    std::cout << "\n";

    // Mostrar nombres, tamaños y dimensiones de las imágenes ordenadas por tamaño
    for (const auto& img : imagenes) {
        std::cout << "Archivo: " << img.name 
                  << " | Size: " << img.size << " bytes"
                  << " | Dimensions: " << img.width << "x" << img.height << " px\n";
    }

    return 0;
}
