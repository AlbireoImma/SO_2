#include <stdio.h>
#include <stdlib.h>

/*
    Estructura tablero
        trampas_1 (int *)
            /-> Puntero hacia un arreglo que contenga las posiciones de las trampas de tipo ?.
        trampas_2 (int *)
            /-> Puntero hacia un arreglo que contenga las posiciones de las trampas de tipo ??.
        invertido (int)
            /-> Entero con valor 1 o 0 que indica si las trampas han sido invertidas, 0 en caso negativo.
            
*/
typedef struct table {
    int *trampas_1;
    int *trampas_2;
    int invertido;
}tablero;

/*
    Estructura status
        GAME_OVER (int)
            /-> Entero que indica el final de la partida, la partida sigue en marcha con valor 0.
        WINNER (int)
            /-> Entero que indica el jugador ganador de la partida en caso del termino de esta.
        turno (int)
            /-> Entero que indica el turno actual de la partida.
        next (int)
            /-> Entero que indica el jugador siguiente a tomar su turno.
        playing
            /-> Entero que indica al jugador que actualmente esta en juego.
        turnos (int [4])
            /-> Arreglo de 4 enteros que indica el orden de turnos de los jugadores.
        posiciones (int [4])
            /-> Arreglo de 4 enteros que indica las posiciones de los jugadores en el tablero.
        FLAG (int)
            /-> Entero que indica que un turno debe ser saltado, manejado por la funcion jugar().
*/

typedef struct juego {
    int GAME_OVER;
    int WINNER;
    int turno;
    int next;
    int playing;
    int turnos[4];
    int posiciones[4];
    int FLAG;
}status;

char *get_jug(int jugando){
    switch (jugando+1){
        case 1:
            return "[JUG]";
            break;
        case 2:
            return "[BT1]";
            break;
        case 3:
            return "[BT2]";
            break;
        case 4:
            return "[BT3]";
            break;
        default:
            break;
    }
    return "[JUG]";
}

/*
    Funcion: void pick_turnos(status *estado)
        Input: recibe un puntero status a modificar
        Funcionamiento: mediante entrada del usuario se determina el array turnos y los valores next y playing
        Output: -
        Notas: no contempla el error de ingresar otra cosa distinta de numeros
*/

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

/*
    Funcion: status *make_player()
        Input: -
        Funcionamiento: Aloja un status en memoria dinámica y lo setea a condiciones iniciales
        Output: puntero de status con valores iniciales
        Notas: hace uso de pick_turnos para iniciar el array turnos como los valores playing y next
*/

status *make_player(){
    status *estado = (status *)calloc(1,sizeof(status));
    estado->turno = 1;
    estado->WINNER = 0;
    estado->GAME_OVER = 0;
    estado->FLAG = 0;
    pick_turnos(estado);
    for(int i = 0; i < 4; i++)
    {
        estado->posiciones[i]=1;
    }
    return estado;
}

/*
    Funcion: void set_player(status *estado)
        Input: puntero de status
        Funcionamiento: Modifica un status en memoria dinámica y lo setea a condiciones iniciales
        Output: -
        Notas: similar a make_player pero no crea el arreglo solo lo modifica
*/

void set_player(status *estado){
    estado->turno = 1;
    estado->WINNER = 0;
    estado->GAME_OVER = 0;
    pick_turnos(estado);
    for(int i = 0; i < 4; i++){
        estado->posiciones[i]=1;
    }
    return;
}

/*
    Funcion: print_estado(status *estado)
        Input: puntero de status
        Funcionamiento: imprime en pantalla el estado actual de la estrutura status dada en el input
        Output: -
        Notas: Util para hacer tracking de las variables de la estructura en tiempo de ejecución
*/

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

/*
    Funcion: void print_jugadores(status *estado)
        Input: puntero de status
        Funcionamiento: imprime en pantalla los tableros de los jugadores y la posición en que se encuentran
        Output: -
        Notas: Usada recurrentemente con print_tablero() para dar una interfaz del juego
*/

void print_jugadores(status *estado){
    for(int i = 0; i < 4; i++){
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

/*
    Funcion: set_tablero(tablero *mesa)
        Input: puntero de tablero
        Funcionamiento: inicializa un tablero en memoria dinamica con valores iniciales
        Output: -
        Notas: Se considera el tablero no invertido como inicial
*/

void set_tablero(tablero *mesa){
    int a[9] = {3,5,7,13,15,22,24,26,28};
    int b[4] = {17,23,25,27};
    // Seteando trampas simples por defecto
    for(int i = 0; i < 9; i++){
        mesa->trampas_1[i]=a[i];
    }
    // Seteando trampas dobles por defecto
    for(int i = 0; i < 4; i++){
        mesa->trampas_2[i] = b[i];
    }
    mesa->invertido = 0;
    return;
}

/*
    Funcion: void print_tablero(tablero *mesa)
        Input: puntero de tablero
        Funcionamiento: imprime en pantalla un tablero con el inicio, trampas, cuadros blancos y final
        Output: -
        Notas: Usada recurrentemente con print_jugadores() para dar una interfaz del juego
*/

void print_tablero(tablero *mesa){
    int aux_1 = 0, aux_2 = 0;
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
        int FLAG = 0;
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
            for(int j = 0; j < 9; j++){
                if (aux_1 < 9 && (mesa->trampas_1[j])==i+1) {
                    printf(" * ");
                    aux_1++;
                    FLAG = 1;
                }   
            }
            for(int k = 0; k < 4; k++){
                if (aux_2 < 4 && (mesa->trampas_2[k])==i+1){
                    printf(" ? ");
                    aux_2++;
                    FLAG = 1;
                }
            }
            if (FLAG == 0) {
                printf("   ");
            } else {
                FLAG = 0;
            }
            
            //printf(" |");
        }
    }
    printf("END|\n");
    return;
}

/*
    Funcion: void send_status(int pipes[10][2], int jugador, status *estado)
        Input: array de pipes, entero indicando el jugador, puntero de estado con el estado actual
        Funcionamiento: envia informacion del estado de un jugador mediante el array de pipes
        Output: -
        Notas: -
*/

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

/*
    Funcion: copy_status(status *estado, status aux)
        Input: puntero a status y variable estatica de tipo status
        Funcionamiento: copia la informacion del tipo estatico al puntero
        Output: -
        Notas: -
*/

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

/*
    Funcion: void receive_status(status *estado, int *pipes)
        Input: puntero a status y un pipe
        Funcionamiento: copia la informacion del pipe al estado
        Output: -
        Notas: -
*/

void receive_status(status *estado, int *pipes){
    status aux;
    close(pipes[1]);
    read(pipes[0],&aux,sizeof(status));
    copy_status(estado,aux);
}

/*
    Funcion: void activate_tramp2(int pos, tablero *mesa, status *estado)
        Input: posicion del jugador, puntero a tablero y puntero a estado
        Funcionamiento: se encarga de resolver las trampas de tipo ?? modificando estado y mesa segun corresponda
        Output: -
        Notas: Uso de aleatoriedad via rand(time(0))
*/

void activate_tramp2(int pos, tablero *mesa, status *estado){
    int random = (rand()%10)+1;
    int jugando;
    for(int i = 0; i < 4; i++){
        if ((estado->turno - 1)%4 == estado->turnos[i]) {
            jugando = i;
        }   
    }
    if ((random >= 1) && (random <= 2)) { // Avanzar hacia la proxima cuadricula blanca 20%
        printf("[SYS]: %s avanza hasta la proxima cuadricula blanca\n",get_jug(jugando));
        int FLAG = 0;
        for(int i = 0; i < 29; i++){
            if (estado->posiciones[jugando] < i) {
                for(int j = 0; j < 9; j++){
                    if (mesa->trampas_1[j]==i) {
                        FLAG = 1;
                    }
                }
                for(int k = 0; k < 4; k++){
                    if (mesa->trampas_2[k]==i) {
                        FLAG = 1;
                    }
                }
                if (FLAG == 1) {
                    FLAG = 0;
                } else {
                    estado->posiciones[jugando] = i;
                    return;
                }
            }
        }
        return;
    } else if ((random > 2) && (random <= 5)) { // Los demás retroceden dos 30%
        printf("[SYS]: Todos retroceden dos cuadriculas\n");
        for(int i = 0; i < 4; i++){
            if (estado->posiciones[i]==1) {
                continue;
            } else {
                if(estado->posiciones[i]==2){
                    estado->posiciones[i] = 1;
                } else {
                    estado->posiciones[i] -= 2;
                }
            }
        }
        return;
    } else if ((random > 5) && (random <= 7)) { // Cambio de posición con el ultimo lugar
        printf("[SYS]: Cambio de posicion %s con el ultimo\n",get_jug(jugando));
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
        printf("[SYS]: Cambio de posicion %s con el primero\n",get_jug(jugando));
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
        int aux;
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
            aux = mesa->trampas_1[i];
            mesa->trampas_1[i] = 30 - aux;
        }
        for(int i = 0; i < 4; i++){
            aux = mesa->trampas_2[i];
            mesa->trampas_2[i] = 30 - aux;
        }
        return;
    }
}

/*
    Funcion: void activate_tramp(int pos, tablero *mesa, status *estado)
        Input: posicion del jugador, puntero a tablero y puntero a estado
        Funcionamiento: se encarga de resolver las trampas de tipo ? modificando estado y mesa segun corresponda
        Output: -
        Notas: Uso de aleatoriedad via rand(time(0))
*/

void activate_tramp(int pos, tablero *mesa, status *estado){
    int random = (rand()%5)+1;
    int jugando;
    for(int i = 0; i < 4; i++){
        if ((estado->turno - 1)%4 == estado->turnos[i]) {
            jugando = i;
        }   
    }
    // printf("[SYS]: Trampa {%d} activada por {%d}\n",random, jugando);
    if (random == 1) { // ? #1
        printf("[SYS]: Jugador %s retrocede una cuadricula\n",get_jug(jugando));
        if (estado->posiciones[jugando]==1) {
            return;
        }
        estado->posiciones[jugando] -= 1;
        return;
    } else if (random == 2){ // ? #2
        printf("[SYS]: Todos excepto jugador %s retroceden una cuadricula\n",get_jug(jugando));
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
    } else if (random == 3){ // ? #3
        printf("[SYS]: Jugador %s avanza una cuadricula\n",get_jug(jugando));
        if (estado->posiciones[jugando]==28) {
            estado->posiciones[jugando]=29;
            estado->WINNER = jugando;
            estado->GAME_OVER = 1;
            return;
        } else {
            estado->posiciones[jugando] += 1;
            return;
        }
    } else if (random == 4) { // ? #4
        printf("[SYS]: Siguinete jugador pierde el turno\n");
        estado->FLAG = 1;
        return;
    } else { // ? #5
        printf("[SYS]: Cambio sentido de turnos\n");
        int j=3, aux;
        for(int i = 0; i < 2; i++){
            aux = estado->turnos[i];
            estado->turnos[i] = estado->turnos[j];
            estado->turnos[j] = aux;
            j--;
        }
        estado->turno -= 1;
        return;
    }
}

/*
    Funcion: void jugar(status *estado, int pipes[10][2],tablero *mesa)
        Input: puntero a estado, array de pipes y puntero a tablero
        Funcionamiento: motor del juego se encarga de mover las piezas y derivar hacia las trampas segun corresponda
        Output: -
        Notas:
*/

void jugar(status *estado, int pipes[10][2],tablero *mesa){
    srand(time(0));
    int jugando;
    for(int i = 0; i < 4; i++){
        if (estado->turno%4 == estado->turnos[i]) {
            jugando = i;
        }   
    }
    if (estado->posiciones[jugando]>=29) { // Ganó
        estado->posiciones[jugando]=29;
        estado->WINNER = jugando;
        estado->GAME_OVER = 1;
        return;
    }
    switch (jugando+1){
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
                    printf("[SYS]: Trampa ? activada por %s\n",get_jug(jugando));
                    activate_tramp(estado->posiciones[jugando],mesa,estado);
                    if(estado->FLAG == 1){
                        estado->FLAG = 0;
                        estado->turno += 1;
                        if (jugando + 2 == 5) {
                            estado->playing = 1;
                        } else {
                            estado->playing = jugando + 2;
                        }
                    } else {
                        estado->playing = jugando+1;
                    }
                    // send_status(pipes, jugando, estado);
                    return;
                }
            }  
            for(i = 0; i < 4; i++){
                if (mesa->trampas_2[i]==estado->posiciones[jugando]) { // Trampa ??
                    printf("[SYS]: Trampa ?? activada por %s\n",get_jug(jugando));
                    activate_tramp2(estado->posiciones[jugando],mesa,estado);
                    estado->playing = jugando+1;
                    // send_status(pipes, jugando, estado);
                    return;
                }
            }
        } else { // Tablero invertido
            for(i = 0; i < 9; i++){
                if (mesa->trampas_1[i]==estado->posiciones[jugando]) { // Trampa ?? invertida
                    printf("[SYS]: Trampa ?? activada por %s\n",get_jug(jugando));
                    activate_tramp2(estado->posiciones[jugando],mesa,estado);
                    estado->playing = jugando+1;
                    // send_status(pipes, jugando, estado);
                    return;
                }
            }  
            for(i = 0; i < 4; i++){
                if (mesa->trampas_2[i]==estado->posiciones[jugando]) { // Trampa ? invertida
                    printf("[SYS]: Trampa ? activada por %s\n",get_jug(jugando));
                    activate_tramp(estado->posiciones[jugando],mesa,estado);
                    if(estado->FLAG == 1){
                        estado->FLAG = 0;
                        estado->turno += 1;
                        if (jugando + 2 >= 5) {
                            estado->playing = 1;
                        } else {
                            estado->playing = jugando + 2;
                        }
                    } else {
                        estado->playing = jugando+1;
                    }
                    // send_status(pipes, jugando, estado);
                    return;
                }
            }
        }
    }
    estado->playing = jugando + 1;
}