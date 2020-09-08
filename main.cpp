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

int busqeudaBinariaIni(vector<Registro*> v, int dato, bool inicio ){
    int ini = 0, fin = v.size() - 1,  mit;

    bool flag = true;

    while (ini <= fin){
        mit = (ini + fin) / 2;

        if (*v[mit] == dato){
            if(inicio && flag == true){
                while(*v[mit] == dato){
                    mit--;
                }
                flag = false;
            }
            else if(!inicio && flag == true){
                while(*v[mit] == dato){
                    mit++;
                }
                flag = false;
            }
            return mit;
        }
        else if(*v[mit] > dato){
            fin = mit - 1;
        }
        else{
            ini = mit + 1;
        }
    }
    return -1;

}

void busqueda(vector<Registro*> vec, string mesI, string mesF, int diaI, int diaF){
    int ini = clave(mesI, diaI), posInicial;
    int fin = clave(mesF, diaF), posFinal;

    posInicial = busqeudaBinariaIni(vec, ini, true);
    posFinal = busqeudaBinariaIni(vec, fin, false);

    for(int i = posInicial; i<posFinal; i++){
        cout <<  vec[i];
    }

}


int main(){
    vector<Registro*> vecRegistros;
    cargaRegistros(vecRegistros);


    int diaI, diaF;
    string mesI, mesF;

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
            cout << "Fecha inicial: (ej. aug 10)" << endl;
            cin >> mesI >> diaI;

            cout << endl << "Fecha Final: " << endl;
            cin >> mesF >> diaF;

            busqueda(vecRegistros, mesI, mesF, diaI, diaF);
            break;
        }
        case '3':{  //Almanecar datos ordenados en archivo nuevo

            break;
        }
    }

    } while( opcion != '0');



    return 0;
}