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
            pipes[0] -> JUG a BT1
            pipes[1] -> JUG a BT2
            pipes[2] -> JUG a BT3
            pipes[3] -> BT1 a BT2
            pipes[4] -> BT1 a BT3
            pipes[5] -> BT2 a BT3
            pipes[6] -> FAT a JUG
            pipes[7] -> FAT a BT1
            pipes[8] -> FAT a BT2
            pipes[9] -> FAT a BT3
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
    for(int i = 0; i < 10; i++)
    {
        pipe(pipes[i]);
    }
    print_tablero(mesa);
    print_jugadores(estado);
    pid_t BT1,BT2,BT3,JUG;
    if ((BT1=fork()) == 0) {
        while(estado->GAME_OVER == 0){
            while(estado->turno%4 == estado->turnos[1]){
                jugar(estado,pipes);
                int jugando = estado->turnos[estado->turno%4];
                send_status(pipes,jugando,estado);
            }
        }
        
    } else if ((BT2=fork()) == 0){
        while(estado->GAME_OVER == 0){
            while(estado->turno%4 == estado->turnos[2]){
                /* code */
            }
        }
    } else if ((BT3=fork()) == 0){
        while(estado->GAME_OVER == 0){
            while(estado->turno%4 == estado->turnos[3]){
                /* code */
            }
        }
    } else if((JUG=fork()) == 0){
        while(estado->GAME_OVER == 0){
            while(estado->turno%4 == estado->turnos[0]){
                /* code */
            }
        }
    } else {
        while(estado->GAME_OVER == 0){
            printf("[PADRE] Juego no terminado...\n");
            sleep(1);
            close(pipes[6][1]);
            read(pipes[6][0],&estado->GAME_OVER,sizeof(int));
        }
        printf("[PADRE] Juego terminado\n");
    }
    return 0;
}
