#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h> 
#include <sys/mman.h>
#include <unistd.h>
#include "tablero.h"

int main(int argc, char const *argv[])
{
    srand(time(0));
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_ANONYMOUS |MAP_SHARED;
    tablero *mesa = (tablero *)mmap(NULL,sizeof(tablero),protection,visibility, 0, 0);
    mesa->trampas_1 = (int *)mmap(NULL,sizeof(int)*9,protection,visibility, 0, 0);
    mesa->trampas_2 = (int *)mmap(NULL,sizeof(int)*4,protection,visibility, 0, 0);
    set_tablero(mesa);
    status *estado = (status *)mmap(NULL,sizeof(status),protection,visibility, 0, 0);
    set_player(estado);
    // status aux;
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
    
    // for(int i = 0; i < 10; i++){
    //     for(int j = 0; j < 4; j++)
    //     {
    //         if (estado->turno%4 == estado->turnos[j]) {
    //             estado->posiciones[j] += rand()%6 + 1;
    //         }
    //     }
    //     estado->turno += 1;
    //     print_estado(estado);
    //     print_tablero(mesa);
    //     print_jugadores(estado);
    // }
    
    pid_t BT1,BT2,BT3,JUG;
    
    JUG = fork();
    if (JUG == 0) { // JUGADOR
        while(estado->GAME_OVER == 0){
            sleep(1);
            while(estado->playing == 1 && estado->GAME_OVER == 0){
                // printf("[JUG]: (PLAY) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                sleep(1);
                jugar(estado,pipes,mesa);
                // printf("[JUG]: (SENDING) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                // send_status(pipes,1,estado);
                print_tablero(mesa);
                print_jugadores(estado);
                sleep(1);
            }
            // printf("[JUG]: (WAITING) [T:%d] [P:%d]\n",estado->turno,estado->playing);
            sleep(3);
            // printf("[JUG]: (READING) [T:%d] [P:%d]\n",estado->turno,estado->playing);
            // receive_status(estado,pipes[0]);
        }
    } else {
        BT1 = fork();
        if (BT1 == 0) { // BOT 1
            while(estado->GAME_OVER == 0){
                sleep(1);
                while(estado->playing == 2 && estado->GAME_OVER == 0){
                    // printf("[BT1]: (PLAY) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                    sleep(1);
                    jugar(estado,pipes,mesa);
                    print_tablero(mesa);
                    print_jugadores(estado);
                    sleep(1);
                    // printf("[BT1]: (SENDING) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                    // send_status(pipes,2,estado);
                }
                // printf("[BT1]: (WAITING) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                sleep(3);
                // printf("[BT1]: (READING) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                // receive_status(estado,pipes[2]);
            }
        } else {
            BT2 = fork();
            if (BT2 == 0) { // BOT 2
                while(estado->GAME_OVER == 0){
                    sleep(1);
                    while(estado->playing == 3 && estado->GAME_OVER == 0){
                        // printf("[BT2]: (PLAY) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                        sleep(1);
                        jugar(estado,pipes,mesa);
                        print_tablero(mesa);
                        print_jugadores(estado);
                        sleep(1);
                        // printf("[BT2]: (SENDING) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                        // send_status(pipes,3,estado);
                    }
                    // printf("[BT2]: (WAITING) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                    sleep(3);
                    // printf("[BT2]: (READING) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                    // receive_status(estado,pipes[4]);
                }
            } else {
                BT3 = fork();
                if (BT3 == 0) { // BOT 3
                    while(estado->GAME_OVER == 0){
                        sleep(1);
                        while(estado->playing == 4 && estado->GAME_OVER == 0){
                            // printf("[BT3]: (PLAY) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                            sleep(1);
                            jugar(estado,pipes,mesa);
                            print_tablero(mesa);
                            print_jugadores(estado);
                            sleep(1);
                            // printf("[BT3]: (SENDING) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                            // send_status(pipes,4,estado);
                        }
                        // printf("[BT3]: (WAITING) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                        sleep(2);
                        // printf("[BT3]: (READING) [T:%d] [P:%d]\n",estado->turno,estado->playing);
                        // receive_status(estado,pipes[6]);
                    }
                } else { // PADRE
                    while(estado->GAME_OVER == 0){
                    //    printf("[PDR]: (WAITING)\n");
                       sleep(4);
                    //    printf("[PDR]: (READING) [GO:%d]\n",estado->GAME_OVER);
                    //    receive_status(estado,pipes[8]);
                    //    print_tablero(mesa);
                    //    print_jugadores(estado);
                    }
                    printf("[PDR]: GAME OVER\n");
                    print_tablero(mesa);
                    print_jugadores(estado);
                }
            }
        }
    }
    return 0;
}
