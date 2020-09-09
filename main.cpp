/*
 * Programación de estructuras de datos y algoritmos fundamentales
 * Actividad 1.3 - Actividad integral de conceptos básicos y algoritmos fundamentales
 * Fernando Doddoli Lankenau - A00827038
 * Mauricio Eugenio Zambrano Díaz - A00827055
 * Cristóbal Alberto Escamilla Sada - A00827074
 * 11 de septiembre del 2020
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include "Registro.h"

void cargaRegistros(vector<Registro*> &v){
    string mes;
    int dia;
    string hora;
    string direccionIP;
    string razon;
    
    ifstream archivo("bitacora.txt");
    
    while(archivo >> mes >> dia >> hora >> direccionIP){
        getline(archivo, razon);
        v.push_back(new Registro(mes, dia, hora, direccionIP, razon));
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

void unir(vector<Registro*> &v, vector<Registro*> &paso, int ini, int fin){
    int mit = (ini + fin) / 2;
    int i = ini, j = mit+1, k = ini;

    while(i <= mit && j <= fin)
        if(*v[i] <= *v[j])
            paso[k++] = v[i++];
        else
            paso[k++] = v[j++];
    
    while(i <= mit)
        paso[k++] = v[i++];
    
    while(j <= fin)
        paso[k++] = v[j++];
    
    for(int z = ini; z <= fin; z++)
        v[z] = paso[z];
}

void ordenaMerge(vector<Registro*> &v, vector<Registro*> &paso, int ini, int fin){
    int mit;

    if(ini < fin){
        mit = (ini + fin) / 2;

        ordenaMerge(v, paso, ini, mit);
        ordenaMerge(v, paso, mit+1, fin);
        unir(v, paso, ini, fin);
    }
}

int busquedaBinaria(vector<Registro*> v, int dato, bool inicio){
    int tam = v.size(), ini = 0, fin = tam - 1,  mit;
    while (ini <= fin){
        mit = (ini + fin) / 2;

        if (*v[mit] == dato){
            if(inicio){
                if(mit == 0 || *v[mit-1] != dato)
                    return mit;
                
                fin = mit + 1;
            } else{
                if(mit == tam-1 || *v[mit+1] != dato)
                    return mit;

                ini = mit + 1;
            }
        } else if(*v[mit] > dato)
            fin = mit + 1;

        else
            ini = mit + 1;
    }  
    
    return -1;
}

void busqueda(vector<Registro*> v, string mesI, string mesF, int diaI, int diaF){
    int ini = clave(mesI, diaI), posInicial;
    int fin = clave(mesF, diaF), posFinal;

    posInicial = busquedaBinaria(v, ini, true);
    posFinal = busquedaBinaria(v, fin, false);

    if(posInicial == -1)
        cout << "La fecha " << mesI << ' ' << diaI << " no existe en el registro." << endl;
    else if(posFinal == -1)
        cout << "La fecha " << mesF << ' ' << diaF << " no existe en el registro." << endl;
    else
        for(int i = posInicial; i<=posFinal; i++)
            cout <<  *v[i];
}

void exportarRegistros(vector<Registro*> v, string nombreArchivo){
    ofstream archivo(nombreArchivo);

    for(int i = 0; i < v.size(); i++)
        archivo << *v[i];

    archivo.close();
}

int main(){
    vector<Registro*> vecRegistros;
    cargaRegistros(vecRegistros);
    int tam = vecRegistros.size();
    vector<Registro*> paso(tam);

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
            ordenaMerge(vecRegistros, paso, 0, tam-1);
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