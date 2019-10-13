#pragma once

class Proceso{
    private:
        int id_proceso;
        int tiempo_llegada;
        int rafaga;
        int prioridad;
    
    public:
        Proceso(int, int, int, int);
        
        int get_id_proceso();
        int get_tiempo_llegada();
        int get_rafaga();
        int get_prioridad();
        void mostrarDatos();
};