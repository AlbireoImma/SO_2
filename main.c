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
    status *estado = make_player();
    print_estado(estado);
    int pipes[4][2];
    for(int i = 0; i < 4; i++)
    {
        pipe(pipes[i]);
    }
    print_tablero(mesa);
    return 0;
}
