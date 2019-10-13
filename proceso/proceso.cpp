#include "proceso.h"
#include <iostream>

using namespace std;

Proceso::Proceso(int id_proceso, int tiempo_llegada, int rafaga, int prioridad){
    this->id_proceso = id_proceso;
    this->tiempo_llegada = tiempo_llegada;
    this->rafaga = rafaga;
    this->prioridad = prioridad;
}

int Proceso::get_id_proceso(){
    return this->id_proceso;
}

int Proceso::get_tiempo_llegada(){
    return this->tiempo_llegada;
}

int Proceso::get_rafaga(){
    return this->rafaga;
}

int Proceso::get_prioridad(){
    return this->prioridad;
}

void Proceso::mostrarDatos(){
    cout << "Proceso: " << this->id_proceso << endl;
    cout << "\tTiempo llegada: " << this->tiempo_llegada << endl;
    cout << "\tRáfaga: " << this->rafaga << endl;
    cout << "\tPrioridad: " << this->prioridad << endl;
}


