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
    int *turnos;
    int *posiciones;
}status;

int *pick_turnos(){
    int *a = (int *)calloc(4,sizeof(int));
    printf("Elija turno para el jugador [seleccione entre 1 y 4]: ");
    int result = scanf("%d",&a[0]);
    while(result == 0 || (a[0]>4 || a[0]<1)){
        printf("Entrada invalida, intente nuevamente: ");
        result = scanf("%d",&a[0]);
    }
    switch (a[0])
    {
        case 1:
            a[1] = 2;
            a[2] = 3;
            a[3] = 4;
            break;
        case 2:
            a[1] = 1;
            a[2] = 3;
            a[3] = 4;
            break;
        case 3:
            a[1] = 1;
            a[2] = 2;
            a[3] = 4;
            break;
        case 4:
            a[1] = 1;
            a[2] = 2;
            a[3] = 3;
            break;
        default:
            break;
    }
    return a;
}

status *make_player(){
    int *aux = pick_turnos();
    status *estado = (status *)calloc(1,sizeof(status));
    estado->turno = 1;
    estado->WINNER = 0;
    estado->GAME_OVER = 0;
    estado->turnos  = aux;
    estado->posiciones  = (int *)calloc(4,sizeof(int));
    for(int i = 0; i < 3; i++)
    {
        estado->posiciones[i]=0;
    }
    return estado;
}

void print_estado(status *estado){
    printf("Estado Juego:%d [1:Finalizado - 0:En juego]\n",estado->GAME_OVER);
    printf("Ganador:%d [0:Desconocido]\n",estado->WINNER);
    printf("Turno actual:%d\n",estado->turno);
    printf("Orden turnos\n");
    printf("\t[Jugador]:%d\n",estado->turnos[0]);
    printf("\t[Bot 1]:%d\n",estado->turnos[1]);
    printf("\t[Bot 2]:%d\n",estado->turnos[2]);
    printf("\t[Bot 3]:%d\n",estado->turnos[3]);
    printf("Posiciones\n");
    printf("\t[Jugador]:%d\n",estado->posiciones[0]);
    printf("\t[Bot 1]:%d\n",estado->posiciones[1]);
    printf("\t[Bot 2]:%d\n",estado->posiciones[2]);
    printf("\t[Bot 3]:%d\n",estado->posiciones[3]);
    return;
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
            printf("|BGN");
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