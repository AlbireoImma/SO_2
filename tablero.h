#include <stdio.h>
#include <stdlib.h>

typedef struct table {
    int *trampas_1;
    int *trampas_2;
    int invertido;
}tablero;

typedef struct juego {
    int GAME_OVER;
    int WINNER;
    int turno;
    int next;
    int playing;
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
            estado->turnos[3] = 0;
            estado->next = 2;
            estado->playing = 1;
            break;
        case 2:
            estado->turnos[0] = 2;
            estado->turnos[1] = 1;
            estado->turnos[2] = 3;
            estado->turnos[3] = 0;
            estado->next = 1;
            estado->playing = 2;
            break;
        case 3:
            estado->turnos[0] = 3;
            estado->turnos[1] = 1;
            estado->turnos[2] = 2;
            estado->turnos[3] = 0;
            estado->next = 3;
            estado->playing = 2;
            break;
        case 4:
            estado->turnos[0] = 0;
            estado->turnos[1] = 1;
            estado->turnos[2] = 2;
            estado->turnos[3] = 3;
            estado->next = 3;
            estado->playing = 2;
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

void set_player(status *estado){
    estado->turno = 1;
    estado->WINNER = 0;
    estado->GAME_OVER = 0;
    pick_turnos(estado);
    for(int i = 0; i < 4; i++)
    {
        estado->posiciones[i]=1;
    }
    return;
}

void print_estado(status *estado){
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    printf("Estado Juego:%d [1:Finalizado - 0:En juego]\n",estado->GAME_OVER);
    printf("Ganador:%d [0:Desconocido]\n",estado->WINNER);
    printf("Turno actual:%d\n",estado->turno);
    if (estado->turnos[0]==estado->turno%4) {
        printf("Jugando: Jugador\n");
    } else if (estado->turnos[1]==estado->turno%4) {
        printf("Jugando: Bot 1\n");
    } else if (estado->turnos[2]==estado->turno%4) {
        printf("Jugando: Bot 2\n");
    } else if (estado->turnos[3]==estado->turno%4) {
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
    mesa->invertido = 0;
    return;
}

void print_tablero(tablero *mesa){
    int aux_1 = 0, aux_2 =0;
    if(mesa->invertido == 0){
        for(int i = 0; i < 29; i++){
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
    } else {
        for(int i = 0; i < 29; i++){
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
                printf(" * ");
                aux_1++;
            } else if (aux_2 < 4 && mesa->trampas_2[aux_2]==i+1){
                printf(" ? ");
                aux_2++;
            } else {
                printf("   ");
            }
            //printf(" |");
        }
    }
    printf("END|\n");
    return;
}

void send_status(int pipes[10][2], int jugador, status *estado){
    // status aux;
    // aux.GAME_OVER = estado->GAME_OVER;
    // for(int i = 0; i < 4; i++){
    //     aux.posiciones[i] = estado->posiciones[i];
    // }
    // for(int i = 0; i < 4; i++){
    //     aux.turnos[i] = estado->turnos[i];
    // }
    // aux.turno = estado->turno;
    // aux.WINNER = estado->WINNER;
    // aux.playing = estado->playing;
    // aux.next = estado->next;
    // aux.turno = estado->turno;
    switch (jugador)
    {
        case 1:
            close(pipes[2][0]);
            write(pipes[2][1],estado,sizeof(status));
            close(pipes[4][0]);
            write(pipes[4][1],estado,sizeof(status));
            close(pipes[6][0]);
            write(pipes[6][1],estado,sizeof(status));
            close(pipes[8][0]);
            write(pipes[8][1],estado,sizeof(status));
            break;
        case 2:
            close(pipes[0][0]);
            write(pipes[0][1],estado,sizeof(status));
            close(pipes[4][0]);
            write(pipes[4][1],estado,sizeof(status));
            close(pipes[6][0]);
            write(pipes[6][1],estado,sizeof(status));
            close(pipes[8][0]);
            write(pipes[8][1],estado,sizeof(status));
            break;
        case 3:
            close(pipes[0][0]);
            write(pipes[0][1],estado,sizeof(status));
            close(pipes[2][0]);
            write(pipes[2][1],estado,sizeof(status));
            close(pipes[6][0]);
            write(pipes[6][1],estado,sizeof(status));
            close(pipes[8][0]);
            write(pipes[8][1],estado,sizeof(status));
            break;
        case 4:
            close(pipes[0][0]);
            write(pipes[0][1],estado,sizeof(status));
            close(pipes[2][0]);
            write(pipes[2][1],estado,sizeof(status));
            close(pipes[4][0]);
            write(pipes[4][1],estado,sizeof(status));
            close(pipes[8][0]);
            write(pipes[8][1],estado,sizeof(status));
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
    for(int i = 0; i < 4; i++){
        estado->turnos[i] = aux.turnos[i];
    }
    estado->turno = aux.turno;
    estado->WINNER = aux.WINNER;
    estado->turno = aux.turno;
}

void receive_status(status *estado, int *pipes){
    status aux;
    close(pipes[1]);
    read(pipes[0],&aux,sizeof(status));
    copy_status(estado,aux);
}

void activate_tramp(int pos, tablero *mesa, status *estado){
    int random = (rand()%10)+1;
    int jugando;
    for(int i = 0; i < 4; i++){
        if ((estado->turno - 1)%4 == estado->turnos[i]) {
            jugando = i;
        }   
    }
    printf("[SYS]: Trampa {%d} activada por {%d}\n",random,jugando);
    if ((random >= 1) && (random <= 3)) { // Retrocede una cuadricula
        printf("[SYS]: Jugador {%d} retrocede una cuadricula\n",jugando);
        if (pos == 1) {
            return;
        } else {
            estado->posiciones[jugando] -= 1;
            return;
        }
    } else if ((random > 3) && (random <= 5)) { // Los demás retroceden una
        printf("[SYS]: Todos excepto Jugador {%d} retroceden una cuadricula\n",jugando);
        for(int i = 0; i < 4; i++){
            if (estado->posiciones[i]==1) {
                continue;
            } else {
                if (i == jugando) {
                    continue;
                } else {
                    estado->posiciones[i] -= 1;
                }
            }
        }
        return;
    } else if ((random > 5) && (random <= 7)) { // Cambio de posición con el ultimo lugar
        printf("[SYS]: Cambio de posicion {%d} con el ultimo\n",jugando);
        int menor = 30;
        int j_menor;
        for(int i = 0; i < 4; i++){
            if(menor > estado->posiciones[i]){
                menor = estado->posiciones[i];
                j_menor = i;
            }
        }
        if (jugando == j_menor) {
            return;
        } else {
            int aux = estado->posiciones[jugando];
            estado->posiciones[jugando]=estado->posiciones[j_menor];
            estado->posiciones[j_menor]=aux;
            return;
        }
    } else if ((random > 7) && (random <= 9)) { // Cambio de posición con el primero
        printf("[SYS]: Cambio de posicion {%d} con el primero\n",jugando);
        int mayor = 0;
        int j_mayor;
        for(int i = 0; i < 4; i++){
            if(mayor < estado->posiciones[i]){
                mayor = estado->posiciones[i];
                j_mayor = i;
            }
        }
        if (jugando == j_mayor) {
            return;
        } else {
            int aux = estado->posiciones[jugando];
            estado->posiciones[jugando]=estado->posiciones[j_mayor];
            estado->posiciones[j_mayor]=aux;
            return;
        }
    } else { // Cambio sentido tablero y cambio de las trampas
        printf("[SYS]: Cambio sentido tablero y trampas\n");
        for(int i = 0; i < 4; i++){
            estado->posiciones[i] = 30 - estado->posiciones[i];
        }
        if (mesa->invertido == 0) {
            mesa->invertido = 1;
        } else {
            mesa->invertido = 0;
        }
        for(int i = 0; i < 9; i++){
            mesa->trampas_1[i] = 30 - mesa->trampas_1[i];
        }
        for(int i = 0; i < 4; i++){
            mesa->trampas_2[i] = 30 - mesa->trampas_2[i];
        }
        return;
    }
}
void activate_tramp2(int pos, tablero *mesa, status *estado){
    return; 
}

void jugar(status *estado, int pipes[10][2],tablero *mesa){
    srand(time(0));
    int jugando;
    for(int i = 0; i < 4; i++){
        if (estado->turno%4 == estado->turnos[i]) {
            jugando = i;
        }   
    }
    
    switch (jugando+1)
    {
        case 1:
            printf("[JUG]: ");
            break;
        case 2:
            printf("[BT1]: ");
            break;
        case 3:
            printf("[BT2]: ");
            break;
        case 4:
            printf("[BT3]: ");
            break;
        default:
            break;
    }
    
    int dado = (rand()%6)+1;
    printf("movio {%d} espacios\n",dado);
    estado->turno += 1;
    estado->posiciones[jugando] += dado;
    estado->next = estado->turnos[(estado->turno%4)+1];
    if (estado->posiciones[jugando]>=29) { // Ganó
        // printf("!!!!!!!!!! WINNER [%d] !!!!!!!!!!!",jugando+1);
        estado->posiciones[jugando]=29;
        estado->WINNER = jugando;
        estado->GAME_OVER = 1;
    } else {
        int i;
        if (mesa->invertido == 0) { // Tablero no invertido
            for(i = 0; i < 9; i++){
                if (mesa->trampas_1[i]==estado->posiciones[jugando]) { // Trampa ?
                    printf("[SYS]: Trampa ? activada por %d\n",jugando);
                    activate_tramp(estado->posiciones[jugando],mesa,estado);
                    estado->playing = jugando+1;
                    // send_status(pipes, jugando, estado);
                    return;
                }
            }  
            for(i = 0; i < 4; i++){
                if (mesa->trampas_2[i]==estado->posiciones[jugando]) { // Trampa ??
                    printf("[SYS]: Trampa ?? activada por %d\n",jugando);
                    activate_tramp2(estado->posiciones[jugando],mesa,estado);
                    estado->playing = jugando+1;
                    // send_status(pipes, jugando, estado);
                    return;
                }
            }
        } else { // Tablero invertido
            for(i = 0; i < 9; i++){
                if (mesa->trampas_1[i]==estado->posiciones[jugando]) { // Trampa ?? invertida
                    printf("[SYS]: Trampa ?? activada por %d\n",jugando);
                    activate_tramp2(estado->posiciones[jugando],mesa,estado);
                    estado->playing = jugando+1;
                    // send_status(pipes, jugando, estado);
                    return;
                }
            }  
            for(i = 0; i < 4; i++){
                if (mesa->trampas_2[i]==estado->posiciones[jugando]) { // Trampa ? invertida
                    printf("[SYS]: Trampa ?? activada por %d\n",jugando);
                    activate_tramp(estado->posiciones[jugando],mesa,estado);
                    estado->playing = jugando+1;
                    // send_status(pipes, jugando, estado);
                    return;
                }
            }
        }
    }
    estado->playing = jugando+1;
}