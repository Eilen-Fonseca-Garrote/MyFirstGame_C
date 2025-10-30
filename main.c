#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

#define FILA 10
#define COLUMNA 10

int array[FILA][COLUMNA] = {};
char arrayJ1[50];
char arrayJ2[50];

void llenarNombre(char nombre[], int value);
bool comprobarWin(int pos1, int pos2, int value);
void mostrarControles(char nombre[], int value);
void movimientoJ2(int *y, int *z, char nombre[]);
void movimientoJ1(int *a, int *b, char nombre[]);
void mostrarMapa(int a, int b, int y, int z);

int main(void)
{
    bool win = false;

    //Jugador 1
    int a = 0, *ptr_a = &a;  //Movimiento Vertical
    int b = 0, *ptr_b = &b;  //Movimiento Horizontal

    //Jugador 2
    int y = FILA - 1, *ptr_y = &y; //Movimiento Vertical
    int z = COLUMNA - 1, *ptr_z = &z; //Movimento Horizontal

    array[a][b] = 1;
    array[y][z] = 1;

    llenarNombre(arrayJ1, 1);
    llenarNombre(arrayJ2, 2);

    system("cls");

    mostrarControles(arrayJ1, 1);
    mostrarControles(arrayJ2, 2);

    system("pause");
    system("cls");

    while(win == false)
    {
        mostrarMapa(a, b, y, z);
        win = comprobarWin(a, b, 2);

        if(win == false)
        {
            movimientoJ1(ptr_a, ptr_b, arrayJ1);
            system("cls");
            mostrarMapa(a, b, y, z);
            win = comprobarWin(y, z, 1);
        }

        if(win == false)
        {
            movimientoJ2(ptr_y, ptr_z, arrayJ2);
            system("cls");
        }
    }

    return 0;
}

void llenarNombre(char nombre[], int value)
{
    printf("Ingrese el nombre del Jugador %d: \n", value);
    gets(nombre);
}

void mostrarMapa(int a, int b, int y, int z)
{
    int i, j;

    printf("\n\n\n");

    for(i = 0; i < FILA; i++)
    {
        printf("\t\t\t");

        for(j = 0; j < COLUMNA; j++)
        {
            if(a == i && b == j)
                printf("[%c]", 1);
            else if(y == i && z == j)
                printf("[%c]", 2);
            else if(array[i][j] == 0)
                printf("[ ]");
            else
                printf("[X]");
        }

        printf("\n");
    }

}

void movimientoJ1(int *a, int *b, char nombre[])
{
    printf("(Turno de: %s)\n", nombre);

    char mov;
    bool mal;

    do
    {
        mal = false;
        fflush(stdin);

        mov = getch();

        switch(mov)
        {
        case 'w':   if(*a > 0 && array[*a-1][*b] != 1)
                        (*a)--;
                    else
                        mal = true;
                break;

        case 's':   if(*a < FILA - 1 && array[*a+1][*b] != 1)
                        (*a)++;
                    else
                        mal = true;
                break;

        case 'a':   if(*b > 0 && array[*a][*b-1] != 1)
                        (*b)--;
                    else
                        mal = true;
            break;

        case 'd':   if(*b < COLUMNA - 1 && array[*a][*b+1] != 1)
                        (*b)++;
                    else
                        mal = true;
            break;

        default: mal = true;
        }

    }while(mal == true);

    array[*a][*b] = 1;
}

void movimientoJ2(int *y, int *z, char nombre[])
{
    printf("(Turno de %s)\n", nombre);

    char mov;
    bool mal;

    do
    {
        mal = false;
        fflush(stdin);

        mov = getch();

        switch(mov)
        {
        case 'u':   if(*y > 0 && array[*y-1][*z] != 1)
                        (*y)--;
                    else
                        mal = true;
            break;

        case 'j':   if(*y < FILA - 1 && array[*y+1][*z] != 1)
                        (*y)++;
                    else
                        mal = true;
                break;

        case 'h':   if(*z > 0 && array[*y][*z-1] != 1)
                        (*z)--;
                    else
                        mal = true;
            break;

        case 'k':   if(*z < COLUMNA - 1 && array[*y][*z+1] != 1)
                        (*z)++;
                    else
                        mal = true;
            break;

        default: mal = true;
        }

    }while(mal == true);

    array[*y][*z] = 1;
}

bool comprobarWin(int pos1, int pos2, int value)
{
    bool win = false;

    if((pos1 == 0 || array[pos1 - 1][pos2] == 1) && (pos1 == FILA - 1 || array[pos1+1][pos2] == 1) && (pos2 == 0 || array[pos1][pos2-1] == 1) && (pos2 == COLUMNA - 1 || array[pos1][pos2+1] == 1))
    {
        printf("\n\n%cFELICIDADES%c HA GANADO %s %c\n----------------------------\n\n\n", 3, 3, value == 1? arrayJ1 : arrayJ2, value == 1? 1 : 2);
        win = true;
    }

    return win;
}

void mostrarControles(char nombre[], int value)
{
    if(value == 1)
    {
        printf("Mostrar Controles:\n-----------------\n");
        printf("%s:\n\t\n", nombre);
        printf("\t(w): %c\n", 24);
        printf("(a): <-\t\t(d): %c \n", 26);
        printf("\t(s): %c\n\t\n", 25);

    }

    if(value == 2)
    {
        printf("Mostrar Controles:\n-----------------\n");
        printf("%s:\n\t\n", nombre);
        printf("\t(u): %c\n", 24);
        printf("(h): <-\t\t(k): %c \n", 26);
        printf("\t(j): %c\n\t\n", 25);

    }

}
