#include <iostream>
#include <stdlib.h>
#include <cctype>

using namespace std;

const int ANCHO = 10; // En mayúsculas para identificar que son constantes
const int ALTO = 10;
int fila_raton = 9, col_raton = 9; // Posición del ratón al inicio
int fila_gato = 0, col_gato = 9; // Posición del gato al inicio
int fila_queso = 0, col_queso = 0; // Posición del queso

void InicializarTablero(char tablero[ALTO][ANCHO]);
void ImprimirTablero(char tablero[ALTO][ANCHO]); // void(vacío) - No devuelve nada
void MoverRaton(char tablero[ALTO][ANCHO]);

int main(){

    char tablero[ALTO][ANCHO];

    InicializarTablero(tablero);
    ImprimirTablero(tablero);
    cout<<"\n";
    for (int i=0; i<3; i++){
        
        MoverRaton(tablero);
        ImprimirTablero(tablero);
        
    }

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


void MoverRaton(char tablero[ALTO][ANCHO]){
    char tecla = ' ';
    while (tecla != 'W' && tecla != 'A' && tecla != 'S' && tecla != 'D'){
        cout<<"Mueva al raton con las teclas W/A/S/D"<<endl;
        cin>>tecla;
        tecla = toupper(tecla);
    }
    switch (tecla)
    {
    case 'W':
        
        if (fila_raton-1 >=0 && tablero[fila_raton-1][col_raton] == ' '){
            tablero[fila_raton][col_raton] = ' ';
            fila_raton--;
            tablero[fila_raton][col_raton] = 'R';

        }
        else{
            cout<<"No puedes moverte hacia arriba \n";
            MoverRaton(tablero);
        }

        break;

    case 'A':

        if (col_raton-1 >=0 && tablero[fila_raton][col_raton-1] == ' '){
                tablero[fila_raton][col_raton] = ' ';
                col_raton--;
                tablero[fila_raton][col_raton] = 'R';

        }
        else{
            cout<<"No puedes moverte hacia la izquierda \n";
            MoverRaton(tablero);
        }
        break;
    
    case 'S':

        if (fila_raton+1 <=ALTO-1 && tablero[fila_raton+1][col_raton] == ' '){
                tablero[fila_raton][col_raton] = ' ';
                fila_raton++;
                tablero[fila_raton][col_raton] = 'R';

        }
        else{
            cout<<"No puedes moverte hacia abajo \n";
            MoverRaton(tablero);
        }
        break;
    
    case 'D':

        if (col_raton+1 <=ANCHO-1 && tablero[fila_raton][col_raton+1] == ' '){
                tablero[fila_raton][col_raton] = ' ';
                col_raton++;
                tablero[fila_raton][col_raton] = 'R';

        }
        else{
            cout<<"No puedes moverte hacia la derecha \n";
            MoverRaton(tablero);
        }
        break;

    default:
        break;
    }


}


