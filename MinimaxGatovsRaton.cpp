#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cctype>

using namespace std;

const char GATO = 'G', RATON = 'R', QUESO = 'Q'; // Jugadores
const int FILAS = 10, COLUMNAS = 10; // Tamaño de nuestro tablero
int fila_raton = 9, col_raton = 9; //Casilla de partida del ratón, dentro del tablero
int fila_gato = 0, col_gato = 9; // Casilla de partida del gato, dentro del tablero
int fila_queso = 0, col_queso = 0; // Casilla de llegada del ratón

void inicializarTablero(vector<vector<char>>& matriz);
void imprimirTablero(const vector<vector<char>>& matriz);
vector<vector<char>> moverArriba(vector<vector<char>> matriz, char jugador);
vector<vector<char>> moverAbajo(vector<vector<char>> matriz, char jugador);
vector<vector<char>> moverDerecha(vector<vector<char>> matriz, char jugador);
vector<vector<char>> moverIzquierda(vector<vector<char>> matriz, char jugador);
int distanciaManhattan(vector<vector<char>> matriz, char objetivo);

int main(){

    vector<vector<char>> tablero(FILAS, vector<char>(COLUMNAS, ' '));
    vector<vector<char>> nuevoTablero;

    inicializarTablero(tablero);
    imprimirTablero(tablero);
    cout << distanciaManhattan(tablero, GATO) << endl;
    for (int i=0; i<1; i++){
        nuevoTablero = moverArriba(tablero, RATON);
        nuevoTablero = moverAbajo(nuevoTablero, GATO);
        imprimirTablero(nuevoTablero);
        cout << distanciaManhattan(nuevoTablero, GATO) << endl;
    }
    imprimirTablero(tablero);
    cout << distanciaManhattan(tablero, QUESO) << endl;
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
    matriz[fila_queso][col_queso] = 'Q';
}

void imprimirTablero(const vector<vector<char>>& matriz) {
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
    if (col_jugador - 1 >= 0 && matriz[fila_jugador][col_jugador+1] != 'O'){
        matriz[fila_jugador][col_jugador] = ' ';
        col_jugador++;
        matriz[fila_jugador][col_jugador] = jugador;
    }
    return matriz;
}

int distanciaManhattan(vector<vector<char>> matriz, char objetivo) {
    int fr, cr, fo, co;
    for (int fila=0; fila<FILAS; fila++){
        for (int col=0; col<COLUMNAS; col++){
            if(matriz[fila][col] == objetivo){
                fo = fila;
                co = col;
            }else if(matriz[fila][col] == RATON){
                fr = fila;
                cr = col;
            }
        }
    }
    return abs(fo - fr) + abs(co - cr);
}
