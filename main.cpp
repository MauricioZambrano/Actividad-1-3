/*
 * Programación de estructuras de datos y algoritmos fundamentales
 * Actividad 1.3 - Actividad integral de conceptos básicos y algoritmos fundamentales
 * 
 * Equipo 13
 * 
 * Fernando Doddoli Lankenau - A00827038
 * Mauricio Eugenio Zambrano Díaz - A00827055
 * Cristóbal Alberto Escamilla Sada - A00827074
 * 
 * 11 de septiembre del 2020
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include "Registro.h"

//Cargar los registros de el archivo .txt a un vector de Registros con sus respectivos atributos
//Complejidad: O(n)
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

//Crea una clave para ponerle un valor numérico a la fecha para facilitar las comparaciones
//Complejidad: O(1)
int clave(string mes, int dia){
    if(mes == "Jun")
        return 600 + dia;
    if(mes == "Jul")
        return 700 + dia;
    if(mes == "Aug")
        return 800 + dia;
    if(mes == "Sep")
        return 900 + dia;
    if(mes == "Oct")
        return 1000 + dia;
    
    return -1;
}

// Ordena y une los datos proporcionados en un vector
// Llamada a través de la función ordenaMerge
// Regresa el número de comparaciones realizadas por la función
// Complejidad: O(n)
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

// Ordena los datos proporcionados por el usuario a través del método merge
// Opera de manera recursiva
// Regresa el número de comparaciones realizadas por la función
// Complejidad: O(nlog n)
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
    int ini = claveOrden(mesI, diaI), posInicial;
    int fin = claveOrden(mesF, diaF), posFinal;

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
    int tam = v.size();

    for(int i = 0; i < tam-1; i++)
        archivo << *v[i] << endl;
    
    archivo << *v[tam-1];

    archivo.close();
}

int main(){
    vector<Registro*> vecRegistros;
    cargaRegistros(vecRegistros);

    int tam = vecRegistros.size();
    vector<Registro*> paso(tam);

    ordenaMerge(vecRegistros, paso, 0, tam-1);

    int diaI, diaF;
    string mesI, mesF, nombreArchivo;
    char opcion;

    cout << "Bienvenid@ a la Bitacora de Errores! Seleccione la acción que desea ejectuar:" << endl;
    cout << "1) Buscar un rango de datos basado en fechas" << endl;
    cout << "2) Transpasar datos ordenados a nuevo archivo" << endl;
    cout << "0) Salir" << endl;
    
    do{
        cin >> opcion;

        switch(opcion){
            case '1':
                cout << "Fecha inicial (ej. Aug 10, recuerde de teclear la primera letra del mes como mayúscula): ";
                cin >> mesI >> diaI;

                cout << endl << "Fecha Final: ";
                cin >> mesF >> diaF;

                busqueda(vecRegistros, mesI, mesF, diaI, diaF);
                break;
            
            case '2':
                cout << "Tecléa el nombre del archivo en el que deseas almacenar los registros ordenados: ";
                cin >> nombreArchivo;
                exportarRegistros(vecRegistros, nombreArchivo);
                break;
            
        }

    } while( opcion != '0');

    cout << endl << "¡Hasta la próxima!" << endl;

    return 0;
}