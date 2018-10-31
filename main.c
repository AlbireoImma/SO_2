#include <stdio.h> 
#include <sys/types.h> 
#include <sys/mman.h>
#include <unistd.h>
#include "tablero.h"

int main(int argc, char const *argv[])
{
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_ANONYMOUS |MAP_SHARED;
    tablero *mesa = (tablero *)mmap(NULL,sizeof(tablero),protection,visibility, 0, 0);
    mesa->trampas_1 = (int *)mmap(NULL,sizeof(int)*9,protection,visibility, 0, 0);
    mesa->trampas_2 = (int *)mmap(NULL,sizeof(int)*4,protection,visibility, 0, 0);
    set_tablero(mesa);
    // int GAME_OVER = 0;
    // int posiciones[4] = {0,0,0,0};
    // int pos_propia = 0;
    // int turno = 1;
    int *turnos = pick_turnos();
    print_tablero(mesa);
    return 0;
}
