#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77

void gotoxy(int x,int y){  // Mueve el cursor de la ventana de texto a la posición según las coordenadas especificadas por los argumentos x e y.
    HANDLE hCon;//identificador de la ventana a manipular
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD  dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);  //Permite dar posición al cursor donde se impimira
}
void ocultarCursor(){
    HANDLE hCon;//identificador de la ventana a manipular
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 10; //El tamaño del cursor su intervalo es de 0-100
    cci.bVisible = FALSE; //Se mostrara o no

    SetConsoleCursorInfo(hCon, &cci);
}

class Nave{
    int x,y;
    //Aqui se creo el constructor
public:
    Nave(int _x, int _y): x(_x) , y(_y){}
    void pintar();
    void borrar();
    void mover();
};

void Nave::pintar(){
    gotoxy(x,y); printf("  %c"  ,30);
    gotoxy(x,y+1); printf(" %c%c%c ",40,207,41);
    gotoxy(x,y+2); printf("%c%c %c%c",30,190,190,30);

}
void Nave::borrar() {
    gotoxy(x,y); printf("     ");
    gotoxy(x,y+1); printf("     ");
    gotoxy(x,y+2); printf("      ");
}
void Nave::mover() {
    if (kbhit()){      //Detecta si se ha precionado una tecla
        char tecla = getch();//Guardar la letra que se preciona
        borrar();
        if (tecla == IZQUIERDA && x > 3) x--;
        if (tecla == DERECHA && x+6 < 77) x++;
        if (tecla == ARRIBA && y > 4) y--;
        if (tecla == ABAJO && y+3 < 33) y++;

        pintar();
    }
}


void pintarLimites(){
    for (int i = 2; i < 78; ++i) {
        gotoxy(i,3); printf("%c",205);    //Linea de arriba
        gotoxy(i,33); printf("%c",205);   //Linea de abajo
    }
    for (int j = 4; j < 33; ++j) {
        gotoxy(2,j); printf("%c",186);   //Linea izquierda
        gotoxy(77,j); printf("%c",186);  //Linea derecha
    }
}
int main(){
    ocultarCursor();
    Nave nave(5,5);
    pintarLimites();
    nave.pintar();

    boolean gameOver = FALSE;
    while (!gameOver){
        nave.mover();
        Sleep(50); // Lo detiene por 50milisegundos
    }



    return 0;
}
