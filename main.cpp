#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Registro.h"

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

int busqeudaBinariaIni(vector<Registro> v, int dato, bool inicio ){
    int ini = 0, fin = v.size() - 1,  mit;

    bool flag;

    cantBB = 0;

    while (ini <= fin){
        mit = (ini + fin) / 2;
        cantBB++;
        if (v[mit] == dato){
            if(inicio && flag == true){
                while(v[mit].getClave() == dato){
                    mit--;
                }
                flag = false;
            }
            else if(!inicio flag == true){
                while(v[mit].getClave() == dato){
                    mit++;
                }
                flag = false;
            }
            return mit;
        }
        else if(v[mit] > dato){
            fin = mit - 1;
        }
        else{
            ini = mit + 1;
        }
    }
    return -1;

}

void imprime(Registro dato){
    cout << dato.getMes() << " " << dato.getDia() << " " << dato.getHora() << " " << dato.getIp() << " " dato.getRazon() << endl;
}

void busqueda(vector<Registro> vec, string mesI, string mesF, int diaI, int diaF){
    int ini = clave(mesI, diaI), posInicial;
    int fin = clave(mesF, diaF), posFinal;

    posInicial = busqeudaBinariaIni(vec, ini, true);
    posFinal = busqeudaBinariaIni(vec, fin, false);

    for(int i = posInicial; i<posFinal; i++){
        imprime(vec[i]);
    }

}


int main(){
    vector<Registro> listaFechas;
    int cantFechas;

    cargaDatosFechas(listaFechas, cantFechas);

    cout << "Fecha inicial: (ej. ago 10)" << endl;
    cin >> mesI >> diaI;

    cout << endl << "Fecha Final: " << endl;
    cin >> mesF >> diaF;

    busqueda(listaFechas, mesI, mesF, diaI, diaF);
}
