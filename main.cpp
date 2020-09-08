#include <iostream>
#include <fstream>
#include <string>

void cargaDatosFechas(Video *listaVideos[], int &cantFechas){
    string mes;
    int dia;
    string hora;
    string direccion;
    string razonDeFalla;
    
    ifstream archivo;
    archivo.open("datosVids.txt");
    
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
    Fecha *listaFechas[100];
    int cantFechas;

    cargaDatosFechas(listaFechas, cantFechas);
}
