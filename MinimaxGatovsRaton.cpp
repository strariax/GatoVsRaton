#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

const char GATO = 'G', RATON = 'R', VACIO = ' '; // Jugadores
const int FILAS = 10, COLUMNAS = 10; // Tamaño de nuestro tablero
int fila_raton = 9, col_raton = 0; //Casilla de partida del ratón, dentro del tablero
int fila_gato = 0, col_gato = 9; // Casilla de partida del gato, dentro del tablero
int duracionDelJuego=30; // Cantidad de turnos que va durar cada juego

struct posicion{
    int fila;
    int columna;
    char jugador;
    bool encontrado;

    posicion(char j) : fila(-1), columna(-1), jugador(j), encontrado(false) {}
    posicion(int f, int c, char j) : fila(f), columna(c), jugador(j), encontrado(true) {}
};

void inicializarTablero(vector<vector<char>>& matriz);
void imprimirTablero(const vector<vector<char>>& matriz); // Const para que la matriz sea solo lectura
bool comprobarMovimiento(const vector<vector<char>> matriz, char jugador, char movimiento);
posicion encontrarJugador(const vector<vector<char>> matriz, char jugador);
vector<vector<char>> jugarGato(vector<vector<char>> matriz, int profundidad, int turnosRestantes);
vector<vector<char>> jugarRaton(vector<vector<char>> matriz, int profundidad, int turnosRestantes);
vector<vector<char>> mover(vector<vector<char>> matriz, char jugador, char movimiento);
int distanciaManhattan(vector<vector<char>> matriz);
int minimax(vector<vector<char>> matriz, int profundidad, bool esTurnoRaton, int turnosRestantes);
bool juegoTerminado(const vector<vector<char>> matriz, int turnosRestantes);

int main(){

    vector<vector<char>> tablero(FILAS, vector<char>(COLUMNAS, ' '));

    inicializarTablero(tablero);
    imprimirTablero(tablero);

    while (!juegoTerminado(tablero, duracionDelJuego))
    {
       tablero = jugarRaton(tablero, 2, duracionDelJuego);
       tablero = jugarGato(tablero, 2, duracionDelJuego);
       imprimirTablero(tablero);
       duracionDelJuego--;
    }
    if (distanciaManhattan(tablero) == 0){
        cout<<"EL GATO ES EL GANADOR"<<endl;
    }
    else{
        cout<<"EL RATON ES EL GANADOR"<<endl;
    }
    return 0;
}

void inicializarTablero(vector<vector<char>>& matriz){
    // vector<vector<char>> matriz(FILAS, vector<char>(COLUMNAS, ' '));

    srand(42);
    for(int fila=0; fila<FILAS; fila++){
        for(int cols= 0; cols<COLUMNAS; cols++){
            if(rand()%10 >=8){
                matriz[fila][cols] = 'O';
            }
        }
    }
    matriz[fila_gato][col_gato] = GATO;
    matriz[fila_raton][col_raton] = RATON;
}

void imprimirTablero(const vector<vector<char>>& matriz) {
    cout<< "JUEGO DEL GATO Y DEL RATON"<<endl;
    cout<<"+";
    for (int i=0; i<COLUMNAS; i++){
        cout << "---+";
    }
    cout<<endl;
    for (const auto& fila : matriz) {
        cout << "|";
        for (char elemento : fila) {
            cout << " "<< elemento << " |";
        }
        cout<<endl;
        cout<<"+";
        for (int i=0; i<COLUMNAS; i++){
            cout << "---+";
        }
        cout << endl;
    }
}

posicion encontrarJugador(const vector<vector<char>> matriz, char jugador){
    for(int fila=0;fila<FILAS;fila++){
        for(int col=0;col<COLUMNAS;col++){
            if(matriz[fila][col] == jugador){
                return posicion(fila, col, jugador);
            }
        }
    }
    // cout<<"No encuentro a: "<<jugador<<endl;
    return posicion(jugador);
}

bool comprobarMovimiento(const vector<vector<char>> matriz, char jugador, char movimiento){
    posicion posJugador = encontrarJugador(matriz, jugador);

    if (posJugador.encontrado){
        switch (movimiento)
        {
        case 'A': // Arriba
            
            if (posJugador.fila - 1 >=0 && matriz[posJugador.fila - 1][posJugador.columna] != 'O' && matriz[posJugador.fila - 1][posJugador.columna] != 'G'){
                return true;
            }
            else{
                return false;
            }
            break;
        
        case 'D': // Derecha
            
            if (posJugador.columna + 1 < COLUMNAS && matriz[posJugador.fila][posJugador.columna + 1] != 'O' && matriz[posJugador.fila][posJugador.columna + 1] != 'G'){
                return true;
            }
            else{
                return false;
            }
            break;
        
        case 'B': // Abajo
            
            if (posJugador.fila + 1 < FILAS && matriz[posJugador.fila + 1][posJugador.columna] != 'O' && matriz[posJugador.fila + 1][posJugador.columna] != 'G'){
                return true;
            }
            else{
                return false;
            }
            break;
        
        case 'I': // Izquierda
            
            if (posJugador.columna - 1 >=0 && matriz[posJugador.fila][posJugador.columna - 1] != 'O' && matriz[posJugador.fila][posJugador.columna - 1] != 'G'){
                return true;
            }
            else{
                return false;
            }
            break;
        
        default:
            break;
        }
    }
    return false;
}

vector<vector<char>> mover(vector<vector<char>> matriz, char jugador, char movimiento){
    posicion posJugador = encontrarJugador(matriz, jugador);

    if (posJugador.encontrado){
        switch (movimiento)
        {
        case 'A': // Arriba
            
            if(comprobarMovimiento(matriz, jugador, movimiento)){

                matriz[posJugador.fila][posJugador.columna] = VACIO;
                matriz[posJugador.fila - 1][posJugador.columna] = jugador;

            }
            break;
        
        case 'D': // Derecha
            
            if(comprobarMovimiento(matriz, jugador, movimiento)){

                matriz[posJugador.fila][posJugador.columna] = VACIO;
                matriz[posJugador.fila][posJugador.columna + 1] = jugador;

            }
            break;
        
        case 'B': // Abajo
            
            if(comprobarMovimiento(matriz, jugador, movimiento)){

                matriz[posJugador.fila][posJugador.columna] = VACIO;
                matriz[posJugador.fila + 1][posJugador.columna] = jugador;

            } 
            break;
        
        case 'I': // Izquierda
            
            if(comprobarMovimiento(matriz, jugador, movimiento)){

                matriz[posJugador.fila][posJugador.columna] = VACIO;
                matriz[posJugador.fila][posJugador.columna - 1] = jugador;

            }
            break;
        
        default:
            break;
        }
    }
    return matriz;
}


int distanciaManhattan(vector<vector<char>> matriz) {

    posicion gato = encontrarJugador(matriz, GATO);
    posicion raton = encontrarJugador(matriz, RATON);

    if(gato.encontrado && raton.encontrado){
        return abs(gato.fila - raton.fila) + abs(gato.columna - raton.columna);
    }
    return 0;
}

bool juegoTerminado(const vector<vector<char>> matriz, int turnosRestantes){
    if (distanciaManhattan(matriz) == 0 || turnosRestantes == 0){
        return true;
    }
    return false;
}

int minimax(vector<vector<char>> matriz, int profundidad, bool esTurnoRaton, int turnosRestantes){
    if(profundidad == 0 || juegoTerminado(matriz, turnosRestantes)){
        return distanciaManhattan(matriz);
    }
    // Si es el turno del ratón debemos maximizar la evaluación (distancia Manhattan)
    if (esTurnoRaton){
        int maxEval = -1;
        vector<char> direcciones ={'A', 'D', 'B', 'I'};
        for(int d=0;d<4;d++){
            vector<vector<char>> tableroAux;
            if(comprobarMovimiento(matriz, RATON, direcciones[d])){
                tableroAux = mover(matriz, RATON, direcciones[d]);
                int eval = minimax(tableroAux, profundidad - 1, false, turnosRestantes);
                maxEval = max(maxEval, eval);
            }
        }
        return maxEval;
    }else{
        int minEval = FILAS + COLUMNAS;
        vector<char> direcciones ={'A', 'D', 'B', 'I'};
        for(int d=0;d<4;d++){
            vector<vector<char>> tableroAux;
            if(comprobarMovimiento(matriz, GATO, direcciones[d])){
                tableroAux = mover(matriz, GATO, direcciones[d]);
                int eval = minimax(tableroAux, profundidad - 1, true, turnosRestantes);
                minEval = min(minEval, eval);
            }
        }
        return minEval;
    }
}

vector<vector<char>> jugarGato(vector<vector<char>> matriz, int profundidad, int turnosRestantes){
    vector<vector<char>> mejorMovimiento;
    int menorEval = FILAS + COLUMNAS;
    vector<char> direcciones ={'A', 'D', 'B', 'I'};
    for(int d=0;d<4;d++){
        vector<vector<char>> tableroAux;
        if(comprobarMovimiento(matriz, GATO, direcciones[d]) && minimax(mover(matriz, GATO, direcciones[d]), profundidad, true, turnosRestantes) <= menorEval){
            mejorMovimiento = mover(matriz, GATO, direcciones[d]);
            menorEval = minimax(mover(matriz, GATO, direcciones[d]), profundidad, true, turnosRestantes);
        }
    }
    return(mejorMovimiento);
}

vector<vector<char>> jugarRaton(vector<vector<char>> matriz, int profundidad, int turnosRestantes){
    vector<vector<char>> mejorMovimiento;
    int mayorEval = -1;
    vector<char> direcciones ={'A', 'D', 'B', 'I'};
    for(int d=0;d<4;d++){
        vector<vector<char>> tableroAux;
        if(comprobarMovimiento(matriz, RATON, direcciones[d]) && minimax(mover(matriz, RATON, direcciones[d]), profundidad, true, turnosRestantes) >= mayorEval){
            mejorMovimiento = mover(matriz, RATON, direcciones[d]);
            mayorEval = minimax(mover(matriz, RATON, direcciones[d]), profundidad, false, turnosRestantes);
        }
    }
    return(mejorMovimiento);
}



