#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cctype>

using namespace std;

const char GATO = 'G', RATON = 'R'; // Jugadores
const int FILAS = 10, COLUMNAS = 10; // Tamaño de nuestro tablero
int fila_raton = 9, col_raton = 0; //Casilla de partida del ratón, dentro del tablero
int fila_gato = 0, col_gato = 9; // Casilla de partida del gato, dentro del tablero
int duracionDelJuego=20; // Cantidad de turnos que va durar cada juego
void inicializarTablero(vector<vector<char>>& matriz);
void imprimirTablero(const vector<vector<char>>& matriz);
vector<vector<char>> moverArriba(vector<vector<char>> matriz, char jugador);
vector<vector<char>> moverAbajo(vector<vector<char>> matriz, char jugador);
vector<vector<char>> moverDerecha(vector<vector<char>> matriz, char jugador);
vector<vector<char>> moverIzquierda(vector<vector<char>> matriz, char jugador);
vector<vector<char>> jugarGato(vector<vector<char>> matriz, int profundidad, int turnosRestantes);
vector<vector<char>> jugarRaton(vector<vector<char>> matriz, int profundidad, int turnosRestantes);
int distanciaManhattan(vector<vector<char>> matriz);
int minimax(vector<vector<char>> matriz, int profundidad, bool esTurnoRaton, int turnosRestantes);
bool juegoTerminado(const vector<vector<char>> matriz, int turnosRestantes);
bool sonMatricesIguales(const vector<vector<char>>& matriz1, const vector<vector<char>>& matriz2);


int main(){

    vector<vector<char>> tablero(FILAS, vector<char>(COLUMNAS, ' '));
    vector<vector<char>> nuevoTablero;

    inicializarTablero(tablero);
    imprimirTablero(tablero);

    while (!juegoTerminado(tablero, duracionDelJuego))
    {
       tablero = jugarRaton(tablero, 3, duracionDelJuego);
       tablero = jugarGato(tablero, 4, duracionDelJuego);
       duracionDelJuego--;
       imprimirTablero(tablero);
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

vector<vector<char>> moverArriba(vector<vector<char>> matriz, char jugador){
    int fila_jugador, col_jugador;
    for (int fila=0; fila<FILAS; fila++){
        for (int col=0; col<COLUMNAS; col++){
            if(matriz[fila][col] == jugador){
                fila_jugador = fila;
                col_jugador = col;
            }
        }
    }
    if (fila_jugador-1 >= 0 && matriz[fila_jugador-1][col_jugador] != 'O'){
        matriz[fila_jugador][col_jugador] = ' ';
        fila_jugador--;
        matriz[fila_jugador][col_jugador] = jugador;
    }
    return matriz;
}

vector<vector<char>> moverAbajo(vector<vector<char>> matriz, char jugador){
    int fila_jugador, col_jugador;
    for (int fila=0; fila<FILAS; fila++){
        for (int col=0; col<COLUMNAS; col++){
            if(matriz[fila][col] == jugador){
                fila_jugador = fila;
                col_jugador = col;
            }
        }
    }
    if (fila_jugador + 1 < FILAS && matriz[fila_jugador+1][col_jugador] != 'O'){
        matriz[fila_jugador][col_jugador] = ' ';
        fila_jugador++;
        matriz[fila_jugador][col_jugador] = jugador;
    }
    return matriz;
}

vector<vector<char>> moverDerecha(vector<vector<char>> matriz, char jugador){
    int fila_jugador, col_jugador;
    for (int fila=0; fila<FILAS; fila++){
        for (int col=0; col<COLUMNAS; col++){
            if(matriz[fila][col] == jugador){
                fila_jugador = fila;
                col_jugador = col;
            }
        }
    }
    if (col_jugador + 1 < COLUMNAS && matriz[fila_jugador][col_jugador+1] != 'O'){
        matriz[fila_jugador][col_jugador] = ' ';
        col_jugador++;
        matriz[fila_jugador][col_jugador] = jugador;
    }
    return matriz;
}

vector<vector<char>> moverIzquierda(vector<vector<char>> matriz, char jugador){
    int fila_jugador, col_jugador;
    for (int fila=0; fila<FILAS; fila++){
        for (int col=0; col<COLUMNAS; col++){
            if(matriz[fila][col] == jugador){
                fila_jugador = fila;
                col_jugador = col;
            }
        }
    }
    if (col_jugador - 1 >= 0 && matriz[fila_jugador][col_jugador-1] != 'O'){
        matriz[fila_jugador][col_jugador] = ' ';
        col_jugador--;
        matriz[fila_jugador][col_jugador] = jugador;
    }
    return matriz;
}

int distanciaManhattan(vector<vector<char>> matriz) {
    int fr = -1, cr = -1, fg, cg;
    for (int fila=0; fila<FILAS; fila++){
        for (int col=0; col<COLUMNAS; col++){
            if(matriz[fila][col] == GATO){
                fg = fila;
                cg = col;
            }else if(matriz[fila][col] == RATON){
                fr = fila;
                cr = col;
            }
        }
    }
    if (fr == -1){
        return 0;
    }
    else{
        return abs(fg - fr) + abs(cg - cr);
    }
}

bool juegoTerminado(const vector<vector<char>> matriz, int turnosRestantes){
    if (distanciaManhattan(matriz) == 0 || turnosRestantes == 0){
        return true;
    }
    return false;
}

bool sonMatricesIguales(const vector<vector<char>>& matriz1, const vector<vector<char>>& matriz2) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            if (matriz1[i][j] != matriz2[i][j]) {
                return false; // Las matrices son diferentes
            }
        }
    }
    return true; // Las matrices son iguales
}

int minimax(vector<vector<char>> matriz, int profundidad, bool esTurnoRaton, int turnosRestantes){
    if(profundidad == 0 || juegoTerminado(matriz, turnosRestantes)){
        return distanciaManhattan(matriz);
    }
    // Si es el turno del ratón debemos maximizar la evaluación (distancia Manhattan)
    if (esTurnoRaton){
        int maxEval = -1;
        if(!sonMatricesIguales(matriz, moverArriba(matriz, RATON))){
            matriz = moverArriba(matriz, RATON);
            int eval = minimax(matriz, profundidad - 1, false, turnosRestantes);
            matriz = moverAbajo(matriz, RATON);
            maxEval = max(maxEval, eval);
        } if(!sonMatricesIguales(matriz, moverDerecha(matriz, RATON))){
            matriz = moverDerecha(matriz, RATON);
            int eval = minimax(matriz, profundidad - 1, false, turnosRestantes);
            matriz = moverIzquierda(matriz, RATON);
            maxEval = max(maxEval, eval);
        } if(!sonMatricesIguales(matriz, moverIzquierda(matriz, RATON))){
            matriz = moverIzquierda(matriz, RATON);
            int eval = minimax(matriz, profundidad - 1, false, turnosRestantes);
            matriz = moverDerecha(matriz, RATON);
            maxEval = max(maxEval, eval);
        } if(!sonMatricesIguales(matriz, moverAbajo(matriz, RATON))){
            matriz = moverAbajo(matriz, RATON);
            int eval = minimax(matriz, profundidad - 1, false, turnosRestantes);
            matriz = moverArriba(matriz, RATON);
            maxEval = max(maxEval, eval);
        }
        return maxEval;
    }else{
        int minEval = FILAS + COLUMNAS;
        if(!sonMatricesIguales(matriz, moverArriba(matriz, GATO))){
            matriz = moverArriba(matriz, GATO);
            int eval = minimax(matriz, profundidad - 1, true, turnosRestantes - 1);
            matriz = moverAbajo(matriz, GATO);
            minEval = min(minEval, eval);
        } if(!sonMatricesIguales(matriz, moverDerecha(matriz, GATO))){
            matriz = moverDerecha(matriz, GATO);
            int eval = minimax(matriz, profundidad - 1, true, turnosRestantes - 1);
            matriz = moverIzquierda(matriz, GATO);
            minEval = min(minEval, eval);
        } if(!sonMatricesIguales(matriz, moverIzquierda(matriz, GATO))){
            matriz = moverIzquierda(matriz, GATO);
            int eval = minimax(matriz, profundidad - 1, true, turnosRestantes - 1);
            matriz = moverDerecha(matriz, GATO);
            minEval = min(minEval, eval);
        } if(!sonMatricesIguales(matriz, moverAbajo(matriz, GATO))){
            matriz = moverAbajo(matriz, GATO);
            int eval = minimax(matriz, profundidad - 1, true, turnosRestantes - 1);
            matriz = moverArriba(matriz, GATO);
            minEval = min(minEval, eval);
        }
        return minEval;
    }
}

vector<vector<char>> jugarGato(vector<vector<char>> matriz, int profundidad, int turnosRestantes){
    vector<vector<char>> mejorMovimiento;
    int menorEval = FILAS + COLUMNAS;

    if(!sonMatricesIguales(matriz, moverArriba(matriz, GATO)) && minimax(moverArriba(matriz, GATO), profundidad, true, turnosRestantes)<menorEval){
        mejorMovimiento = moverArriba(matriz, GATO);
        menorEval = minimax(moverArriba(matriz, GATO), profundidad, true, turnosRestantes);
    }
    if(!sonMatricesIguales(matriz, moverDerecha(matriz, GATO)) && minimax(moverDerecha(matriz, GATO), profundidad, true, turnosRestantes)<menorEval){
        mejorMovimiento = moverDerecha(matriz, GATO);
        menorEval = minimax(moverDerecha(matriz, GATO), profundidad, true, turnosRestantes);
    }
    if(!sonMatricesIguales(matriz, moverIzquierda(matriz, GATO)) && minimax(moverIzquierda(matriz, GATO), profundidad, true, turnosRestantes)<menorEval){
        mejorMovimiento = moverIzquierda(matriz, GATO);
        menorEval = minimax(moverIzquierda(matriz, GATO), profundidad, true, turnosRestantes);
    }
    if(!sonMatricesIguales(matriz, moverAbajo(matriz, GATO)) && minimax(moverAbajo(matriz, GATO), profundidad, true, turnosRestantes)<menorEval){
        mejorMovimiento = moverAbajo(matriz, GATO);
        menorEval = minimax(moverAbajo(matriz, GATO), profundidad, true, turnosRestantes);
    }
    return(mejorMovimiento);

}

vector<vector<char>> jugarRaton(vector<vector<char>> matriz, int profundidad, int turnosRestantes){
    vector<vector<char>> mejorMovimiento;
    int mayorEval = -1;

    if(!sonMatricesIguales(matriz, moverArriba(matriz, RATON)) && minimax(moverArriba(matriz, RATON), profundidad, true, turnosRestantes)>mayorEval){
        mejorMovimiento = moverArriba(matriz, RATON);
        mayorEval = minimax(moverArriba(matriz, RATON), profundidad, true, turnosRestantes);
    }
    if(!sonMatricesIguales(matriz, moverDerecha(matriz, RATON)) && minimax(moverDerecha(matriz, RATON), profundidad, true, turnosRestantes)>mayorEval){
        mejorMovimiento = moverDerecha(matriz, RATON);
        mayorEval = minimax(moverDerecha(matriz, RATON), profundidad, true, turnosRestantes);
    }
    if(!sonMatricesIguales(matriz, moverIzquierda(matriz, RATON)) && minimax(moverIzquierda(matriz, RATON), profundidad, true, turnosRestantes)>mayorEval){
        mejorMovimiento = moverIzquierda(matriz, RATON);
        mayorEval = minimax(moverIzquierda(matriz, RATON), profundidad, true, turnosRestantes);
    }
    if(!sonMatricesIguales(matriz, moverAbajo(matriz, RATON)) && minimax(moverAbajo(matriz, RATON), profundidad, true, turnosRestantes)>mayorEval){
        mejorMovimiento = moverAbajo(matriz, RATON);
        mayorEval = minimax(moverAbajo(matriz, RATON), profundidad, true, turnosRestantes);
    }
    return(mejorMovimiento);

}



