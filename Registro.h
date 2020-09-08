#ifndef Registro_h
#define Registro_h

class Registro{
private:
    string mes;
    int dia;
    string hora;
    string direccionIP;
    string razon;
    int claveOrden;
public:
    Registro(string, int, string, string, string);
    int crearClave(string, int);
    string getMes();
    int getDia();
    int getClaveOrden();
    void print();
    bool operator<(Registro);
    bool operator>(Registro);
};

Registro::Registro(string mes, int dia, string hora, string direccionIP, string razon){
    this->mes = mes;
    this->dia = dia;
    this->hora = hora;
    this->direccionIP = direccionIP;
    this->razon = razon;
    claveOrden = crearClave(mes, dia);
}

int Registro::crearClave(string mes, int dia){
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

string Registro::getMes(){
    return mes;
}

int Registro::getDia(){
    return dia;
}

int Registro::getClaveOrden(){
    return claveOrden;
}

void Registro::print(){
    cout << mes << ' ' << dia ' ' << hora << ' ' << direccionIP << ' ' << razon << endl;
}

bool Registro::operator<(Registro r){
    if(claveOrden < r.claveOrden)
        return true;

    return false;
}

bool Registro::operator>(Registro r){
    if(claveOrden > r.claveOrden)
        return true;

    return false;
}

#endif