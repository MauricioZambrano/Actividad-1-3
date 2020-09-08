#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void cargaDatosFechas(vector <Fecha> &listaFechas, int &cantFechas){
    string mes;
    int dia;
    string hora;
    string direccion;
    string razonDeFalla;
    
    ifstream archivo;
    archivo.open("bitacora.txt");
    
    cantFechas = 0;
    while(archivo >> mes)
        {
             archivo >> mes >> dia >> hora >> direccion >> razonDeFalla;
             listaFechas[cantFechas] = new Fecha(mes, dia, hora, direccion, razonDeFalla);
        }
        cantFechas++;
    }
    
    archivo.close();
    
}

int main(){
    vector<Fecha> listaFechas;
    int cantFechas;

    cargaDatosFechas(listaFechas, cantFechas);
}
