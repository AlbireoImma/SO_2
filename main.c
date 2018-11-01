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
    int pipes[10][2];
    /* 
        Los pipes son los siguientes:
            pipes[0] -> JUG entrada
            pipes[1] -> JUG salida
            pipes[2] -> BT1 entrada
            pipes[3] -> BT1 salida
            pipes[4] -> BT2 entrada
            pipes[5] -> BT2 salida
            pipes[6] -> BT3 entrada
            pipes[7] -> BT3 salida
            pipes[8] -> PAD entrada
            pipes[9] -> PAD salida
        Funcionamiento de los pipes:
            pipe[i][0] -> Input side
            pipe[i][1] -> Output side
            *** WRITING ***
                close(pipes[i][0])
                write(pipes[i][1], objeto a enviar, size elemento)
            *** READING ***
                close(pipes[i][1])
                read(pipes[i][0], readbuffer, sizeof(readbuffer))

    */
    for(int i = 0; i < 10; i++){
        pipe(pipes[i]);
    }
    printf("Estado Inicial!!\n");
    print_tablero(mesa);
    print_jugadores(estado);
    
    for(int i = 0; i < 10; i++){
        estado->turno += 1;
        estado->posiciones[0] += rand()%6 + 1;
        estado->posiciones[1] += rand()%6 + 1;
        estado->posiciones[2] += rand()%6 + 1;
        estado->posiciones[3] += rand()%6 + 1;
        print_estado(estado);
        print_tablero(mesa);
        print_jugadores(estado);
    }
    
    pid_t BT1,BT2,BT3,JUG;
    
    JUG = fork();
    if (JUG == 0) { // JUGADOR
        /* code */
    } else {
        BT1 = fork();
        if (BT1 == 0) { // BOT 1
            /* code */
        } else {
            BT2 = fork();
            if (BT2 == 0) { // BOT 2
                /* code */
            } else {
                BT3 = fork();
                if (BT3 == 0) { // BOT 3
                    /* code */
                } else { // PADRE
                    /* code */
                }
            }
        }
    }
    return 0;
}
