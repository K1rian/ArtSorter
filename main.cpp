#include <iostream>
#include <fstream>
#include <filesystem>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include <map>
#include <algorithm>

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

void mergeSort(std::vector<plant>& imagenes, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(imagenes, left, mid);
        mergeSort(imagenes, mid + 1, right);
        merge(imagenes, left, mid, right);
    }
}

// Función para ordenar precios
void ordenarPrecios(std::map<std::string, double>& precios) {
    std::vector<std::pair<std::string, double>> precios_vec(precios.begin(), precios.end());
    std::sort(precios_vec.begin(), precios_vec.end(), [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
        return a.second < b.second; // Orden ascendente por precio
    });

    // Imprimir precios ordenados
    std::cout << "\nPrecios ordenados:\n";
    for (const auto& p : precios_vec) {
        std::cout << "Imagen: " << p.first << " | Precio: $" << p.second << "\n";
    }
}

// Función para guardar precios en un archivo
void archivopresio(const std::map<std::string, double>& precios) {
    std::ofstream archivo("precios.txt");
    if (archivo.is_open()) {
        for (const auto& p : precios) {
            archivo << "Imagen: " << p.first << " | Precio: $" << p.second << "\n";
        }
        archivo.close();
        std::cout << "\nDatos guardados en precios.txt\n";

        // Abrir el archivo inmediatamente
        std::system("start precios.txt");  // Para Windows
    } else {
        std::cout << "\nError al abrir el archivo para guardar los precios.\n";
    }
}


void listarImagenes(const std::vector<plant>& imagenes) {
    std::cout << "\nListado de imagenes:\n";
    for (const auto& img : imagenes) {
        std::cout << "Archivo: " << img.name
                  << " | Size: " << img.size << " bytes"
                  << " | Dimensions: " << img.width << "x" << img.height << " px\n";
    }
}

void abrirImagen(const std::vector<plant>& imagenes) {
    std::string nombreImagen;
    std::cout << "\nEscribe el nombre de la imagen que deseas abrir: ";
    std::getline(std::cin, nombreImagen);
    for (const auto& img : imagenes) {
        if (img.name == nombreImagen) {
            std::cout << "Abriendo imagen: " << img.name << "\n";
            std::string comando = "start " + img.path; // Para Windows
            std::system(comando.c_str());
            return;
        }
    }
    std::cout << "Imagen no encontrada.\n";
}

int main() {
    std::string folder = "Proyecto_dibujo";
    DIR* dr;
    struct dirent* en;

    std::vector<plant> imagenes;
    std::map<std::string, double> precios;  // Para almacenar precios

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
        std::cout << "3. Listar precios y ordenar\n";
        std::cout << "4. Guardar precios en archivo\n";
        std::cout << "5. Salir\n";
        std::cout << "Elige una opcion: ";
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar el buffer

        switch (opcion) {
            case 1:
                listarImagenes(imagenes);
                break;
            case 2:
                abrirImagen(imagenes);
                break;
            case 3:
                // Opción para agregar precios
                std::cout << "\nIntroduce los precios de las imagenes:\n";
                for (const auto& img : imagenes) {
                    double precio;
                    std::cout << "Precio de " << img.name << ": $";
                    std::cin >> precio;
                    precios[img.name] = precio;
                }

                // Ordenar y mostrar precios
                ordenarPrecios(precios);
                break;
            case 4:
                archivopresio(precios);  // Guardar precios en un archivo
                break;
            case 5:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opcion no válida, intenta de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}
