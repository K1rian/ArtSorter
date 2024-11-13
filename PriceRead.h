#include<fstream>
#include<iostream>
#include<map>

std::string validNumber = "0123456789";

// Complejidad temporal (mejor y peor caso): O(p * m), donde p es el número de precios en el archivo 
// y m es el tamaño promedio de cada línea. Cada línea se procesa completamente.
// Complejidad espacial: O(p), ya que se almacenan hasta p elementos en el mapa 'out'.
void ReadPriceFromFile(std::string fileName, std::map<std::string, double> &out){  
    
    std::fstream archivo;
    archivo.open(fileName, std::fstream::in); // Abrir el archivo para lectura
    std::string thisline;

    while(std::getline(archivo, thisline)){  // Procesar cada línea del archivo

        char thislinebutchar[thisline.size()] = "";
        int finish;
        std::string endofline = "";

        // Extraer nombre de la imagen y precio de cada línea
        for(int i = 8; i < thisline.size() ; i++){
            if(thisline[i] == ' ' && thisline[i+1] == '|'){ // Identificar el separador
                finish = i;
                int k = 0;
                for (int j = i+1 ; j < thisline.size() ; j++){
                    if(validNumber.find(thisline[j]) == std::string::npos) continue;
                    endofline += thisline[j]; // Extraer solo caracteres numéricos para el precio
                    k++;
                }
                break;
            }
            thislinebutchar[i-8] = thisline[i];
        }
        
        double thisvalue = std::stod(endofline); // Convertir el precio a double
        out[thislinebutchar] = thisvalue;  // Guardar el nombre de la imagen y el precio en el mapa 'out'
    }
}

// Complejidad temporal (mejor y peor caso): O(n), donde n es el número de elementos en el mapa.
// La función recorre todos los elementos de 'in' e imprime cada uno.
// Complejidad espacial: O(1), ya que solo utiliza memoria constante y no depende de la cantidad de elementos en el mapa.
void PrintPrecio(const std::map<std::string, double> &in){  

    for(const auto& c : in){  // Imprimir cada par de nombre de imagen y precio
        std::cout << "Imagen: " << c.first << ", Precio: " << c.second << "\n";
    }
}
