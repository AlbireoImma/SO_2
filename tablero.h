#include <stdio.h>
#include <stdlib.h>

typedef struct table {
    int *trampas_1;
    int *trampas_2;
}tablero;

typedef struct juego {
    int GAME_OVER;
    int WINNER;
    int turno;
    int turnos[4];
    int posiciones[4];
}status;

void pick_turnos(status *estado){
    printf("Elija turno para el jugador [seleccione entre 1 y 4]: ");
    int result = scanf("%d",&estado->turnos[0]);
    while(result == 0 || (estado->turnos[0]>4 || estado->turnos[0]<1)){
        printf("Entrada invalida, intente nuevamente: ");
        result = scanf("%d",&estado->turnos[0]);
    }
    switch (estado->turnos[0])
    {
        case 1:
            estado->turnos[1] = 2;
            estado->turnos[2] = 3;
            estado->turnos[3] = 4;
            break;
        case 2:
            estado->turnos[1] = 1;
            estado->turnos[2] = 3;
            estado->turnos[3] = 4;
            break;
        case 3:
            estado->turnos[1] = 1;
            estado->turnos[2] = 2;
            estado->turnos[3] = 4;
            break;
        case 4:
            estado->turnos[1] = 1;
            estado->turnos[2] = 2;
            estado->turnos[3] = 3;
            break;
        default:
            break;
    }
    return;
}

status *make_player(){
    status *estado = (status *)calloc(1,sizeof(status));
    estado->turno = 1;
    estado->WINNER = 0;
    estado->GAME_OVER = 0;
    pick_turnos(estado);
    for(int i = 0; i < 4; i++)
    {
        estado->posiciones[i]=1;
    }
    return estado;
}

void print_estado(status *estado){
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    printf("Estado Juego:%d [1:Finalizado - 0:En juego]\n",estado->GAME_OVER);
    printf("Ganador:%d [0:Desconocido]\n",estado->WINNER);
    printf("Turno actual:%d\n",estado->turno);
    if ((estado->turno)%4 == estado->turnos[0]) {
        printf("Jugando: Jugador\n");
    } else if ((estado->turno)%4 == estado->turnos[1]) {
        printf("Jugando: Bot 1\n");
    } else if ((estado->turno)%4 == estado->turnos[2]) {
        printf("Jugando: Bot 2\n");
    } else if ((estado->turno)%4 == estado->turnos[3]) {
        printf("Jugando: Bot 3\n");
    }
    printf("Orden turnos\n");
    printf("\t[Jugador]:%d\n",estado->turnos[0]);
    printf("\t[Bot 1]:%d\n",estado->turnos[1]);
    printf("\t[Bot 2]:%d\n",estado->turnos[2]);
    printf("\t[Bot 3]:%d\n",estado->turnos[3]);
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    return;
}

void print_jugadores(status *estado){
    
    for(int i = 0; i < 4; i++)
    {
        if (i == 0) {
            printf("JUG: ");
        } else if (i == 1) {
            printf("BT1: ");
        } else if (i == 2) {
            printf("BT2: ");
        } else if (i == 3) {
            printf("BT3: ");
        }
        for(int j = 0; j < 29; j++){
            if (estado->posiciones[i]==j+1) {
                printf("| # ");
            } else {
                printf("|   ");
            }
        }
        printf("|\n");
    }
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
}

void set_tablero(tablero *mesa){
    int a[9] = {3,5,7,13,15,22,24,26,28};
    int b[4] = {17,23,25,27};
    // Seteando trampas simples por defecto
    for(int i = 0; i < 9; i++)
    {
        mesa->trampas_1[i]=a[i];
    }
    // Seteando trampas dobles por defecto
    for(int i = 0; i < 4; i++)
    {
        mesa->trampas_2[i] = b[i];
    }
    return;
}

void print_tablero(tablero *mesa){
    int aux_1 = 0, aux_2 =0;
    for(int i = 0; i < 29; i++)
    {
        
        if (i==0) {
            printf("TAB: |BGN");
            continue;
        } else if (i==28){
            printf("|");
            continue;
        } else {
            printf("|");
        }
        if (aux_1 < 9 && mesa->trampas_1[aux_1]==i+1) {
            printf(" ? ");
            aux_1++;
        } else if (aux_2 < 4 && mesa->trampas_2[aux_2]==i+1){
            printf(" * ");
            aux_2++;
        } else {
            printf("   ");
        }
        //printf(" |");
    }
    printf("END|\n");
    return;
}

void send_status(int **pipes, int jugador, status *estado, status buffer_estado){
    switch (jugador)
    {
        case 1:
            for(int i = 0; i < 3; i++)
            {
                close(pipes[i][0]);
                write()
            }
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        default:
            break;
    }
}