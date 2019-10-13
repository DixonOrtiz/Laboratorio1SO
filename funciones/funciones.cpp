#include "funciones.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <queue>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#include "../proceso/proceso.h"

using namespace std;

int validarEntrada(int min = 1, int max = 50){
    while(true){
        string s;
        getline(cin,s);
        char *endp = 0;
        int ret = strtol(s.c_str(),&endp,10);
        if(endp!=s.c_str() && !*endp && ret >= min && ret <= max)
            return ret;
        cout << "\nEntrada inválida, pruebe otra vez: ";
    }
}

void ingresarProcesos(queue<Proceso> &cola){
    cout << "\nAsistente para ingresar procesos" << endl;
    
    cout << "\nIngrese la cantidad de procesos que desea ejecutar en esta iteración (entre 1 y 10): ";
    int numero_procesos = validarEntrada(1, 10);

    // Variables para la creación de procesos de forma dinámica
    Proceso *proceso_auxiliar = NULL;
    
    int id_proceso_auxiliar = 0;
    int tiempo_llegada_auxiliar = 0;
    int rafaga_auxiliar = 0;
    int prioridad_auxiliar = 0;

    //Variables para calcular el tiempo de llegada
    time_t llegada_primer_proceso;
    time_t llegada_proceso_posterior;
    time_t delta;

    for(int i = 1; i <= numero_procesos; i++){
        cout << "Proceso n°" << i << ": " <<endl;
        
        id_proceso_auxiliar = i;

        cout << "\tIngrese la ráfaga del proceso n°" << i << " (entre 1 y 50): ";
        rafaga_auxiliar = validarEntrada(1, 50);  

        cout << "\tIngrese la prioridad del proceso n°" << i << " (entre 0 y 10): ";
        prioridad_auxiliar = validarEntrada(0, 10);       

        //Si es el primer proceso el tiempo de llegada es 0
        if(i == 1){
            llegada_primer_proceso = time(NULL); 
            delta = llegada_primer_proceso - llegada_primer_proceso;
        }
        
        //Si no es el primer proceso el tiempo de llegada es la diferencia con el primero
        else{
            llegada_proceso_posterior = time(NULL);
            delta = llegada_proceso_posterior - llegada_primer_proceso;
            
        }               
        
        proceso_auxiliar = new Proceso(id_proceso_auxiliar, delta, rafaga_auxiliar, prioridad_auxiliar);
        cola.push(*proceso_auxiliar);
    
        //Limpieza de memoria y reinicio de variables    
        delete(proceso_auxiliar);
        proceso_auxiliar = NULL;

        id_proceso_auxiliar = 0;
        tiempo_llegada_auxiliar = 0;
        rafaga_auxiliar = 0;
        prioridad_auxiliar = 0;
    }
}

void imprimirCola(queue<Proceso> cola){
    queue<Proceso> cola_auxiliar = cola;
    
    cout << endl;

    while(!cola_auxiliar.empty()){
        cola_auxiliar.front().mostrarDatos();
        cola_auxiliar.pop();
    }
}

void llenarAdministrador(vector<queue<Proceso>> &administrador){
    queue<Proceso> primera_cola;
    queue<Proceso> segunda_cola;
    queue<Proceso> tercera_cola;
    queue<Proceso> cuarta_cola;

    ingresarProcesos(primera_cola);

    administrador.push_back(primera_cola);
    administrador.push_back(segunda_cola);
    administrador.push_back(tercera_cola);
    administrador.push_back(cuarta_cola);
}

bool existenProcesos(vector<queue<Proceso>> administrador){
    for(int i = 0; i < 4; i++){
        if(!administrador[i].empty())
            return true;
    }

    return false;
}

void roundRobin(queue<Proceso> &cola, int tiempo_ejecucion){

    Proceso *proceso_auxiliar = NULL;

    int id_proceso_auxiliar = 0;
    int tiempo_llegada_auxiliar = 0;
    int rafaga_auxiliar = 0;
    int prioridad_auxiliar = 0;

    int suma_ejecucion = 0;

    while(suma_ejecucion < 8 && !cola.empty()){
        if(0 < (cola.front().get_rafaga())){

            id_proceso_auxiliar = cola.front().get_id_proceso();
            tiempo_llegada_auxiliar = cola.front().get_tiempo_llegada();      
            rafaga_auxiliar = cola.front().get_rafaga();
            prioridad_auxiliar = cola.front().get_prioridad();

            if(rafaga_auxiliar < tiempo_ejecucion){
                suma_ejecucion += (tiempo_ejecucion-rafaga_auxiliar);
                rafaga_auxiliar = 0;
            }

            else{
                rafaga_auxiliar -= tiempo_ejecucion;
                suma_ejecucion += tiempo_ejecucion;
            }
            
            proceso_auxiliar = new Proceso(id_proceso_auxiliar, tiempo_llegada_auxiliar, rafaga_auxiliar, prioridad_auxiliar);


            if(rafaga_auxiliar <= 0)
                cola.pop();
            
            else{
                cola.pop();
                cola.push(*proceso_auxiliar);
            }
            

            //Limpieza de memoria y reinicio de variables    
            delete(proceso_auxiliar);
            proceso_auxiliar = NULL;

            id_proceso_auxiliar = 0;
            tiempo_llegada_auxiliar = 0;
            rafaga_auxiliar = 0;
            prioridad_auxiliar = 0;
        }
    }
}

void colaACola(queue<Proceso> &cola_entrada ,queue<Proceso> &cola_salida){
    while(!cola_entrada.empty()){
        cola_salida.push(cola_entrada.front());
        cola_entrada.pop();
    }
}

bool existePrioridad(queue<Proceso> cola, int prioridad){
    bool existe_prioridad = false;

    while(!cola.empty()){
        if(cola.front().get_prioridad() == prioridad){
            existe_prioridad = true;            
        }
        cola.pop();
    }

    return existe_prioridad;
}

void colaAColaPriority(queue<Proceso> &cola_entrada ,queue<Proceso> &cola_salida){
    int prioridad_actual = 0;

    while(!cola_entrada.empty()){
        if(existePrioridad(cola_entrada, prioridad_actual)){
            if(cola_entrada.front().get_prioridad() == prioridad_actual){
                cola_salida.push(cola_entrada.front());
                cola_entrada.pop(); 
            }

            else{
                cola_entrada.push(cola_entrada.front());
                cola_entrada.pop();
            }
        }

        else{
            prioridad_actual++;
        }
    }
}

//La única diferencia es que para que sea priority necesita recibir la cola ordenada por prioridad
//en caso contrario se comporta como fcfs
void priority_fcfs(queue<Proceso> &cola){

    Proceso *proceso_auxiliar = NULL;

    int id_proceso_auxiliar = 0;
    int tiempo_llegada_auxiliar = 0;
    int rafaga_auxiliar = 0;
    int prioridad_auxiliar = 0;

    int disponibilidad_asignacion = 8;

    while(disponibilidad_asignacion > 0 && !cola.empty()){
        if(0 < (cola.front().get_rafaga())){

            id_proceso_auxiliar = cola.front().get_id_proceso();
            tiempo_llegada_auxiliar = cola.front().get_tiempo_llegada();      
            rafaga_auxiliar = cola.front().get_rafaga();
            prioridad_auxiliar = cola.front().get_prioridad();

            if(rafaga_auxiliar <= disponibilidad_asignacion){
                disponibilidad_asignacion -= rafaga_auxiliar;
                
                rafaga_auxiliar = 0;
            }

            else{
                rafaga_auxiliar -= disponibilidad_asignacion;
                disponibilidad_asignacion = 0;
            }
            
            proceso_auxiliar = new Proceso(id_proceso_auxiliar, tiempo_llegada_auxiliar, rafaga_auxiliar, prioridad_auxiliar);


            if(rafaga_auxiliar <= 0)
                cola.pop();
            
            else{
                cola.pop();
                cola.push(*proceso_auxiliar);
            }
            

            //Limpieza de memoria y reinicio de variables    
            delete(proceso_auxiliar);
            proceso_auxiliar = NULL;

            id_proceso_auxiliar = 0;
            tiempo_llegada_auxiliar = 0;
            rafaga_auxiliar = 0;
            prioridad_auxiliar = 0;
        }
    }
}
