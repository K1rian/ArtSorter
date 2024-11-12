#include<fstream>
#include<iostream>
#include<map>

std::string validNumber = "0123456789";
void ReadPriceFromFile(std::string fileName, std::map<std::string, double> &out){  //Complegidad de tiempo O(p*m) donde p es numero de presios del archivo y m es el tamaño promedio de cada linea  ---  Complegidad de espacio O(p) para el mapa out
    std::fstream archivo;

    archivo.open(fileName, std::fstream::in);

    std::string thisline;

    while(std::getline(archivo, thisline)){

        char thislinebutchar [thisline.size()] = "";
        int finish;
        std::string endofline = "";

        for(int i = 8; i < thisline.size() ; i ++){
            if(thisline[i] == ' ' && thisline[i+1] == '|'){
                finish = i;
                int k = 0;
                for (int j = i+1 ; j < thisline.size() ; j++){
                    if(validNumber.find(thisline[j]) == std::string::npos)continue;
                    endofline+= thisline[j];
                    k++;
                }
                break;
            }
            thislinebutchar[i-8] = thisline[i];
            
        }
            
            double thisvalue = std::stod(endofline);

            out[thislinebutchar] = thisvalue;

    }

}

void PrintPrecio(const std::map<std::string, double> &in){  //Complegidad de tiempo O(n)  ---  Complegidad de espacio O(1)

    for(const auto&c : in){
        std::cout << "Imagen: " << c.first << ", Precio: " << c.second << "\n";
    }
}