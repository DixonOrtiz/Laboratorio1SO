#pragma once

#include <queue>
#include "../proceso/proceso.h"

using namespace std;

int validarEntrada(int, int);
void ingresarProcesos(queue<Proceso> &);
void imprimirCola(queue<Proceso>);
void llenarAdministrador(vector<queue<Proceso>> &);
bool existenProcesos(vector<queue<Proceso>>);
void roundRobin(queue<Proceso> &, int);
void colaACola(queue<Proceso> &, queue<Proceso> &);
bool existePrioridad(queue<Proceso>, int);
void colaAColaPriority(queue<Proceso> &, queue<Proceso> &);
void priority_fcfs(queue<Proceso> &);
