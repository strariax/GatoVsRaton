#include <iostream>
#include <stdlib.h>

using namespace std;

const int ANCHO = 20; // En mayúsculas para identificar que son constantes
const int ALTO = 20;
int fila_raton = 19, col_raton = 19; // Posición del ratón al inicio
int fila_gato = 0, col_gato = 19; // Posición del gato al inicio
int fila_queso = 0, col_queso = 0; // Posición del queso

void InicializarTablero(char tablero[ALTO][ANCHO]);
void ImprimirTablero(char tablero[ALTO][ANCHO]); // void(vacío) - No devuelve nada

int main(){

    char tablero[ALTO][ANCHO];

    InicializarTablero(tablero);
    ImprimirTablero(tablero);

    cout<<"Hola mundooo";
    return 0;
}

void InicializarTablero(char tablero[ALTO][ANCHO]){
    srand(42); //Semilla de la funcion random
    for(int fila=0; fila<ALTO; fila++){
        for(int cols=0; cols<ANCHO; cols++){
            if (rand()%10 >= 8){
                    tablero[fila][cols]='O';
            }
            else{
                tablero[fila][cols]=' ';
            }

        }
    }

    tablero[fila_gato][col_gato] = 'G';
    tablero[fila_raton][col_raton] = 'R';
    tablero[fila_queso][col_queso] = 'Q';
}

/*
void ImprimirTablero(char tablero[ALTO][ANCHO]){

    for(int fila=0; fila<ALTO; fila++){
        for(int cols=0; cols<ANCHO; cols++){

            cout<<tablero[fila][cols]<<"  ";

        }
        cout<<"\n";
    }

}*/

void ImprimirTablero(char tablero[ALTO][ANCHO]){
    for(int fila=0; fila<ALTO; fila++){
        cout << "+";
        for (int j = 0; j < ANCHO; ++j) {
            cout << "---+";
        }
        cout << "\n";
        for(int cols= 0; cols<ANCHO; cols++){
            if(cols == 0){
                cout<< "|";
            }
            cout <<" "<<tablero[fila][cols]<< " |";           
        }
        cout << "\n";
    }
    cout << "+";
    for (int j = 0; j < ANCHO; ++j) {
        cout << "---+";
    }
    cout << endl;
}


