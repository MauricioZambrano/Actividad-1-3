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
    bool operator<=(Registro);
    bool operator>=(Registro);
    bool operator>(int);
    bool operator==(int);
    bool operator!=(int);
    friend ostream& operator<<(ostream&, Registro);
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
    if(mes == "Oct")
        return 1000 + dia;

    return -1;
}

bool Registro::operator<=(Registro r){
    if(claveOrden <= r.claveOrden)
        return true;
    
    return false;
}

bool Registro::operator>=(Registro r){
    if(claveOrden >= r.claveOrden)
        return true;
    
    return false;
}

bool Registro::operator>(int n){
    if(claveOrden > n)
        return true;

    return false;
}

bool Registro::operator==(int n){
    if(claveOrden == n)
        return true;

    return false;
}

bool Registro::operator!=(int n){
    if(claveOrden != n)
        return true;

    return false;
}

ostream& operator<<(ostream& os, Registro r){
    os  << r.mes << ' ' << r.dia << ' ' << r.hora << ' ' << r.direccionIP << r.razon;

    return os;
}

#endif