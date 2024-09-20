#include <iostream>
#include <fstream>
#include <filesystem>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION // Definir esta macro antes de incluir stb_image.h
#include "stb_image.h" // Asegúrate de tener stb_image.h en la carpeta junto al main

int main (){
    struct plant{
        std::string name;
        uintmax_t size = 0;
        std::string path;
        int width = 0;    // Ancho de la imagen
        int height = 0;   // Alto de la imagen
        int channels = 0; // Número de canales de la imagen (RGB, RGBA, etc.)
    };

    // Puntero tipo DIR para manipular directorios
    DIR *dr;
    struct dirent *en;
    std::string folder = "Proyecto_dibujo";
    dr = opendir(folder.c_str());

    std::vector<plant> imagenes;
    if (dr) {
        while((en = readdir(dr)) != NULL){
            std::string filename = en->d_name;

            // Evitar archivos "." y ".."
            if (filename != "." && filename != "..") {
                plant img;
                img.name = filename;
                img.path = folder + "/" + filename;

                // Verificar si el archivo es un archivo regular y no un directorio
                std::filesystem::path filepath = img.path;
                if (std::filesystem::is_regular_file(filepath)) {
                    // Obtener el tamaño del archivo
                    img.size = std::filesystem::file_size(filepath);

                    // Leer la imagen usando stb_image
                    unsigned char* data = stbi_load(img.path.c_str(), &img.width, &img.height, &img.channels, 0);
                    if (data) {
                        // La imagen fue cargada correctamente y ahora tenemos sus dimensiones
                        stbi_image_free(data); // Liberar la memoria de la imagen después de usarla
                    } else {
                        std::cerr << "No se pudo abrir la imagen: " << img.path << ".\n"; // Enviar mensajes de error o advertencias "std::cerr"
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

    // Mostrar nombres, tamaños y dimensiones de las imágenes
    for (const auto& img : imagenes) {
        std::cout << "Archivo: " << img.name 
                  << " | Size: " << img.size << " bytes"
                  << " | Dimensions: " << img.width << "x" << img.height << " px\n";
    }

    return 0;
}
