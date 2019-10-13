#include <iostream>
#include "funciones/funciones.h"
#include "proceso/proceso.h"
#include <vector>
#include <queue>
#include <typeinfo>

using namespace std;

int main(){

    vector<queue<Proceso>> administrador;

    llenarAdministrador(administrador);

    // Mientras existan procesos en las colas ejecuta los algoritmos
    int numero_cola = 0;
    cout << "\nOriginal";
    imprimirCola(administrador[numero_cola]);
    
    while(existenProcesos(administrador)){

        //No es FCFS
        if(numero_cola < 3){
            // RR, q=2
            if(numero_cola == 0){
                roundRobin(administrador[numero_cola], 2);
                if(existenProcesos(administrador)){
                    colaACola(administrador[numero_cola], administrador[numero_cola + 1]);
                    numero_cola++;
                }
                else
                    break;
                cout << "\nTras Round Robin q=2";
                imprimirCola(administrador[numero_cola]);
            }

            // RR, q=4
            else if(numero_cola == 1){
                roundRobin(administrador[numero_cola], 4);
                if(existenProcesos(administrador)){
                    colaAColaPriority(administrador[numero_cola], administrador[numero_cola + 1]);
                    numero_cola++;
                }
                else
                    break;
                cout << "\nTras Round Robin q=4";
                imprimirCola(administrador[numero_cola]);
            } 

            // Priority 
            else{
                priority_fcfs(administrador[numero_cola]);
                 if(existenProcesos(administrador)){
                     colaAColaPriority(administrador[numero_cola], administrador[numero_cola + 1]);
                     numero_cola++;
                 }
                 else
                    break;
                cout << "\nTras Priority";
                imprimirCola(administrador[numero_cola]);
            }
        }
        
        //FCFS
        else{
            priority_fcfs(administrador[numero_cola]);
            if(existenProcesos(administrador)){
                colaAColaPriority(administrador[numero_cola], administrador[0]);
                numero_cola = 0;
            }
            else
                break;  

            cout << "\nTras FCFS";
            imprimirCola(administrador[numero_cola]);
        }
    }

    return 0;
}