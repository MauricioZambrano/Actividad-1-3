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
    
    ifstream archivo("bitacora.txt");
    
    while(archivo >> mes >> dia >> hora >> direccionIP){
        getline(archivo, razon);
        vecRegistros.push_back(new Registro(mes, dia, hora, direccionIP, razon));
    }
    
    archivo.close();  
}

int clave(string mes, int dia){
    if(mes == "Jun")
        return 600 + dia;
    if(mes == "Jul")
        return 700 + dia;
    if(mes == "Aug")
        return 800 + dia;
    if(mes == "Sep")
        return 900 + dia;
        
    return 1000 + dia;
}

int busquedaBinaria(vector<Registro*> v, int dato, bool inicio){
    int tam = v.size(), ini = 0, fin = tam - 1,  mit;
    while (ini <= fin){
        mit = (ini + fin) / 2;

        if (*v[mit] == dato){
            if(inicio){
                if(mit == 0 || *v[mit-1] != dato)
                    return mit;
                
                fin = --mit;
            } else{
                if(mit == tam-1 || *v[mit+1] != dato)
                    return mit;

                ini = ++mit;
            }
        } else if(*v[mit] > dato)
            fin = --mit;

        else
            ini = ++mit;
    }  
    
    return -1;
}

void busqueda(vector<Registro*> vec, string mesI, string mesF, int diaI, int diaF){
    int ini = clave(mesI, diaI), posInicial;
    int fin = clave(mesF, diaF), posFinal;

    posInicial = busquedaBinaria(vec, ini, true);
    posFinal = busquedaBinaria(vec, fin, false);

    if(posInicial == -1)
        cout << "La fecha " << mesI << ' ' << diaI << " no existe en el registro." << endl;
    else if(posFinal == -1)
        cout << "La fecha " << mesF << ' ' << diaF << " no existe en el registro." << endl;
    else
        for(int i = posInicial; i<=posFinal; i++)
            cout <<  *vec[i];
}

void exportarRegistros(vector<Registro*> vecRegistros, string nombreArchivo){
    ofstream archivo(nombreArchivo);

    for(int i = 0; i < vecRegistros.size(); i++)
        archivo << *vecRegistros[i];

    archivo.close();
}

int main(){
    vector<Registro*> vecRegistros;
    cargaRegistros(vecRegistros);

    int diaI, diaF;
    string mesI, mesF, nombreArchivo;

    char opcion;

    cout << "Bienvenid@ a la Bitacora de Errores! Seleccione la acción que desea ejectuar:" << endl;
    cout << "1) Ordenar información de bitacora" << endl;
    cout << "2) Buscar un rango de datos basado en fechas" << endl;
    cout << "3) Transpasar datos ordenados a nuevo archivo" << endl;
    cout << "0) Salir" << endl;
    do{
    
    cin >> opcion;

    switch(opcion){
        case '1':{ //Ordena información

            break;
        }
        case '2':{ //Busqueda
            cout << "Fecha inicial: (ej. aug 10):" << endl;
            cin >> mesI >> diaI;

            cout << endl << "Fecha Final: " << endl;
            cin >> mesF >> diaF;

            busqueda(vecRegistros, mesI, mesF, diaI, diaF);
            break;
        }
        case '3':{  //Almanecar datos ordenados en archivo nuevo
            cout << "Tecléa el nombre del archivo en el que deseas almacenar los registros ordenados: ";
            cin >> nombreArchivo;
            exportarRegistros(vecRegistros, nombreArchivo);
            break;
        }
    }

    } while( opcion != '0');

    return 0;
}