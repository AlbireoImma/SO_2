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
    int last_played;
    int turnos[4];
    int posiciones[4];
}status;

void pick_turnos(status *estado){
    int aux;
    printf("Elija turno para el jugador [seleccione entre 1 y 4]: ");
    int result = scanf("%d",&aux);
    while(result == 0 || (aux > 4 || aux < 1)){
        printf("Entrada invalida, intente nuevamente: ");
        result = scanf("%d",&aux);
    }
    switch (aux)
    {
        case 1:
            estado->turnos[0] = 1;
            estado->turnos[1] = 2;
            estado->turnos[2] = 3;
            estado->turnos[3] = 4;
            estado->last_played = 1;
            break;
        case 2:
            estado->turnos[0] = 2;
            estado->turnos[1] = 1;
            estado->turnos[2] = 3;
            estado->turnos[3] = 4;
            estado->last_played = 2;
            break;
        case 3:
            estado->turnos[0] = 2;
            estado->turnos[1] = 3;
            estado->turnos[2] = 1;
            estado->turnos[3] = 4;
            estado->last_played = 2;
            break;
        case 4:
            estado->turnos[0] = 2;
            estado->turnos[1] = 3;
            estado->turnos[2] = 4;
            estado->turnos[3] = 1;
            estado->last_played = 2;
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

void send_status(int pipes[10][2], int jugador, status *estado){
    status aux;
    aux.GAME_OVER = estado->GAME_OVER;
    for(int i = 0; i < 4; i++){
        aux.posiciones[i] = estado->posiciones[i];
    }
    for(size_t i = 0; i < 4; i++){
        aux.turnos[i] = estado->turnos[i];
    }
    aux.turno = estado->turno;
    aux.WINNER = estado->WINNER;
    aux.last_played = estado->last_played;
    aux.turno = estado->turno;
    switch (jugador)
    {
        case 1:
            for(int i = 0; i < 3; i++)
            {
                close(pipes[i][0]);
                write(pipes[i][1],&aux,sizeof(estado));
            }
            break;
        case 2:
            close(pipes[0][0]);
            write(pipes[0][1],&aux,sizeof(estado));
            close(pipes[3][0]);
            write(pipes[3][1],&aux,sizeof(estado));
            close(pipes[4][0]);
            write(pipes[4][1],&aux,sizeof(estado));
            break;
        case 3:
            close(pipes[1][0]);
            write(pipes[1][1],&aux,sizeof(estado));
            close(pipes[3][0]);
            write(pipes[3][1],&aux,sizeof(estado));
            close(pipes[5][0]);
            write(pipes[5][1],&aux,sizeof(estado));
            break;
        case 4:
            close(pipes[2][0]);
            write(pipes[2][1],&aux,sizeof(estado));
            close(pipes[4][0]);
            write(pipes[4][1],&aux,sizeof(estado));
            close(pipes[5][0]);
            write(pipes[5][1],&aux,sizeof(estado));
            break;
        default:
            break;
    }
}

void copy_status(status *estado, status aux){
    estado->GAME_OVER = aux.GAME_OVER;
    for(int i = 0; i < 4; i++){
        estado->posiciones[i] = aux.posiciones[i];
    }
    for(size_t i = 0; i < 4; i++){
        estado->turnos[i] = aux.turnos[i];
    }
    estado->turno = aux.turno;
    estado->WINNER = aux.WINNER;
    estado->last_played = aux.last_played;
    estado->turno = aux.turno;
}

void receive_status(status *estado, int **pipes, int sender, int receiver){
    status aux;
    switch (receiver){
        case 1:
            switch (sender){
                case 2:
                    close(pipes[0][1]);
                    read(pipes[0][0],&aux,sizeof(aux));
                    copy_status(estado,aux);
                    break;
                case 3:
                    close(pipes[1][1]);
                    read(pipes[1][0],&aux,sizeof(aux));
                    copy_status(estado,aux);
                    break;
                case 4:
                    close(pipes[2][1]);
                    read(pipes[2][0],&aux,sizeof(aux));
                    copy_status(estado,aux);
                    break;
                default:
                    break;
            }
            break;
        case 2:
            switch (sender){
                case 1:
                    close(pipes[0][1]);
                    read(pipes[0][0],&aux,sizeof(aux));
                    copy_status(estado,aux);
                    break;
                case 3:
                    close(pipes[3][1]);
                    read(pipes[3][0],&aux,sizeof(aux));
                    copy_status(estado,aux);
                    break;
                case 4:
                    close(pipes[4][1]);
                    read(pipes[4][0],&aux,sizeof(aux));
                    copy_status(estado,aux);
                    break;
                default:
                    break;
            }
            break;
        case 3:
            switch (sender){
                case 1:
                    close(pipes[1][1]);
                    read(pipes[1][0],&aux,sizeof(aux));
                    copy_status(estado,aux);
                    break;
                case 2:
                    close(pipes[3][1]);
                    read(pipes[3][0],&aux,sizeof(aux));
                    copy_status(estado,aux);
                    break;
                case 4:
                    close(pipes[5][1]);
                    read(pipes[5][0],&aux,sizeof(aux));
                    copy_status(estado,aux);
                    break;
                default:
                    break;
            }
            break;
        case 4:
            switch (sender){
                case 1:
                    close(pipes[2][1]);
                    read(pipes[2][0],&aux,sizeof(aux));
                    copy_status(estado,aux);
                    break;
                case 2:
                    close(pipes[4][1]);
                    read(pipes[4][0],&aux,sizeof(aux));
                    copy_status(estado,aux);
                    break;
                case 3:
                    close(pipes[5][1]);
                    read(pipes[5][0],&aux,sizeof(aux));
                    copy_status(estado,aux);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void activate_tramp(int pos, tablero *mesa, status *estado){
    return;
}
void activate_tramp2(int pos, tablero *mesa, status *estado){
    return; 
}

void jugar(status *estado, int pipes[10][2],tablero *mesa){
    int jugando = estado->turnos[estado->turno%4];
    int dado = (rand()%6)+1;
    int pos_mov = estado->posiciones[jugando-1]+dado;
    estado->posiciones[jugando-1]=estado->posiciones[jugando-1]+dado;
    
    if (estado->posiciones[jugando-1]>=29) {
        estado->WINNER = jugando;
        estado->GAME_OVER = 1;
        estado->last_played = jugando;
        estado->turno = estado->turno+1;
        send_status(pipes, jugando, estado);
    } else {
        int i;
        for(i = 0; i < 9; i++){
            if (mesa->trampas_1[i]==pos_mov) {
                activate_tramp(pos_mov,mesa,estado);
                send_status(pipes, jugando, estado);
                return;
            }
        }
        for(i = 0; i < 4; i++){
            if (mesa->trampas_2[i]==pos_mov) {
                activate_tramp2(pos_mov,mesa,estado);
                send_status(pipes, jugando, estado);
                return;
            }
        }
    }
}