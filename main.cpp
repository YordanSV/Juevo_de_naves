#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

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
    int x,y,corazones,vidas;
public:
    Nave(int _x, int _y,int _corazones,int _vidas): x(_x) , y(_y), corazones(_corazones), vidas(_vidas){}     //Aqui se creo el constructor
    void pintarNave();
    void borrar();
    void mover();
    void pintarCorazones();
    void morir();
    int X(){return x;}
    int Y(){return y;}
    void quitarCorazones(){ corazones--;}
};

void Nave::pintarNave(){
    gotoxy(x,y); printf("  %c"  ,30);
    gotoxy(x,y+1); printf(" %c%c%c ",40,207,41);
    gotoxy(x,y+2); printf("%c%c %c%c",30,190,190,30);

}
void Nave::borrar() {
    gotoxy(x,y); printf("         ");
    gotoxy(x,y+1); printf("        ");
    gotoxy(x,y+2); printf("         ");
}
void Nave::mover() {
    if (kbhit()){      //Detecta si se ha precionado una tecla
        char tecla = getch();//Guardar la letra que se preciona
        borrar();
        if (tecla == 'b') corazones--;
        if (tecla == IZQUIERDA && x > 3) x--;
        if (tecla == DERECHA && x+6 < 77) x++;
        if (tecla == ARRIBA && y > 4) y--;
        if (tecla == ABAJO && y+3 < 33) y++;
        pintarNave();
        pintarCorazones();
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
    gotoxy(2,3); printf("c%",201);
    gotoxy(2,33); printf("c%",200); //Esquinas
    gotoxy(77,3); printf("c%",187);
    gotoxy(77,33); printf("c%",188);
}

void Nave::pintarCorazones(){
    gotoxy(50,2); printf("Vidas %i", vidas);   //Pintando las vidas
    gotoxy(64,2); printf("Salud");
    gotoxy(70,2); printf("      ");
    for (int i = 0; i < corazones; ++i) {
        gotoxy(70+i,2); printf("%c",3);
    }
}
void Nave::morir() {
    if (corazones == 0){
        borrar();
        gotoxy(x,y);      printf("    **     ");
        gotoxy(x,y+1); printf("   ****    ");
        gotoxy(x,y+2); printf("    **     ");
        Sleep(200);

        gotoxy(x,y);      printf(" *  **  *  ");
        gotoxy(x,y+1); printf("   ****    ");
        gotoxy(x,y+2); printf(" *  **  *  ");
        Sleep(200);
        borrar();
        vidas--;
        corazones = 3;
        pintarCorazones();
        pintarNave();
        Sleep(30);
    }
}








class Asteroide{
    int x,y;
public:
    Asteroide(int _x,int _y): x(_x),y(_y){};
    void mover();
    void pintar();
    void choque(struct Nave &N);
};


void Asteroide::pintar() {
    gotoxy(x,y); printf("%c",184);
}

void Asteroide::mover() {
    gotoxy(x,y); printf(" ");
    y++;
    if (y > 32){
        x = rand()%71 + 4;
        y = 4;
    }
    pintar();
    Sleep(20);
}
void Asteroide::choque(struct Nave &N) {
    if(x >= N.X() && x < N.X()+6 && y > N.Y() && y <= N.Y()+3) {
        N.quitarCorazones();
        N.pintarNave();
        N.pintarCorazones();
        x = rand() % 71 + 4;
        y = 4;
    }
}
int main(){
    ocultarCursor();
    Nave nave(40,30,3,3);
    pintarLimites();
    nave.pintarNave();
    nave.pintarCorazones();
    Asteroide asteroide1(10,4);
    Asteroide asteroide2(15,4);
    Asteroide asteroide3(20,4);

    boolean gameOver = FALSE;
    while (!gameOver){
        asteroide1.mover(); asteroide1.choque(nave);
        asteroide2.mover(); asteroide2.choque(nave);
        asteroide3.mover(); asteroide3.choque(nave);
        nave.morir();
        nave.mover();
        //Sleep(50); // Lo detiene por 50milisegundos
    }



    return 0;
}
