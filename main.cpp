#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include "Registro.h"

void cargaRegistros(vector<Registro*> &vecRegistros){
    string mes;
    int dia;
    string hora;
    string direccionIP;
    string razon;
    
    ifstream archivo;
    archivo.open("bitacora.txt");
    
    while(archivo >> mes){
        archivo >> mes >> dia >> hora >> direccionIP >> razon;
        vecRegistros.push_back(new Registro(mes, dia, hora, direccionIP, razon));
    }
    
    archivo.close();
    
}

int main(){
    vector<Registro> vecRegistros;
    cargaRegistros(vecRegistros);
}
